//  Copyright (c) 2016 Thomas Heller
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>
#include <pika/parallel/util/detail/void_guard.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

///////////////////////////////////////////////////////////////////////////////
namespace pika::parallel::detail {
    // Hand-crafted function object allowing to replace a more complex
    // bind(std::apply, f1, _1)
    template <typename Result, typename F>
    struct partitioner_iteration
    {
        std::decay_t<F> f_;

        template <typename T>
        PIKA_HOST_DEVICE PIKA_FORCEINLINE Result operator()(T&& t)
        {
            return void_guard<Result>(), std::apply(f_, PIKA_FORWARD(T, t));
        }
    };
}    // namespace pika::parallel::detail

#if defined(PIKA_HAVE_THREAD_DESCRIPTION)
#include <pika/functional/traits/get_function_address.hpp>
#include <pika/functional/traits/get_function_annotation.hpp>

namespace pika::detail {
    template <typename Result, typename F>
    struct get_function_address<
        parallel::detail::partitioner_iteration<Result, F>>
    {
        static constexpr std::size_t call(
            parallel::detail::partitioner_iteration<Result, F> const&
                f) noexcept
        {
            return get_function_address<std::decay_t<F>>::call(f.f_);
        }
    };

    template <typename Result, typename F>
    struct get_function_annotation<
        parallel::detail::partitioner_iteration<Result, F>>
    {
        static constexpr char const* call(
            parallel::detail::partitioner_iteration<Result, F> const&
                f) noexcept
        {
            return get_function_annotation<std::decay_t<F>>::call(f.f_);
        }
    };

#if PIKA_HAVE_ITTNOTIFY != 0 && !defined(PIKA_HAVE_APEX)
    template <typename Result, typename F>
    struct get_function_annotation_itt<
        parallel::detail::partitioner_iteration<Result, F>>
    {
        static util::itt::string_handle call(
            parallel::detail::partitioner_iteration<Result, F> const&
                f) noexcept
        {
            return get_function_annotation_itt<std::decay_t<F>>::call(f.f_);
        }
    };
#endif
}    // namespace pika::detail
#endif
