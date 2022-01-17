//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2009 Steven Watanabe
//  Copyright (c) 2011-2013 Hartmut Kaiser
//  Copyright (c) 2013-2016 Agustin Berge
//
//  SPDX-License-Identifier: BSL-1.0
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>
#include <pika/functional/traits/is_bind_expression.hpp>

#include <type_traits>
#include <utility>

namespace pika { namespace util {
    namespace detail {
        template <typename F>
        class protected_bind : public F
        {
        public:
            explicit protected_bind(F const& f)
              : F(f)
            {
            }

            explicit protected_bind(F&& f)
              : F(PIKA_MOVE(f))
            {
            }

#if !defined(__NVCC__) && !defined(__CUDACC__)
            protected_bind(protected_bind const&) = default;
            protected_bind(protected_bind&&) = default;
#else
            PIKA_HOST_DEVICE protected_bind(protected_bind const& other)
              : F(other)
            {
            }

            PIKA_HOST_DEVICE protected_bind(protected_bind&& other)
              : F(PIKA_MOVE(other))
            {
            }
#endif

            protected_bind& operator=(protected_bind const&) = delete;
        };
    }    // namespace detail

    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    PIKA_HOST_DEVICE typename std::enable_if<
        traits::is_bind_expression<typename std::decay<T>::type>::value,
        detail::protected_bind<typename std::decay<T>::type>>::type
    protect(T&& f)
    {
        return detail::protected_bind<typename std::decay<T>::type>(
            PIKA_FORWARD(T, f));
    }

    // leave everything that is not a bind expression as is
    template <typename T>
    PIKA_HOST_DEVICE typename std::enable_if<
        !traits::is_bind_expression<typename std::decay<T>::type>::value,
        T>::type
    protect(T&& v)    //-V659
    {
        return PIKA_FORWARD(T, v);
    }
}}    // namespace pika::util
