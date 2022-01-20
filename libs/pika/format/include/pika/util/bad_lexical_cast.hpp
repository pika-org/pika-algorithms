//  Copyright (c) 2019 Agustin Berge
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>

#include <typeinfo>

#include <pika/config/warnings_prefix.hpp>

namespace pika { namespace util {

    class PIKA_EXPORT bad_lexical_cast : public std::bad_cast
    {
    public:
        bad_lexical_cast() noexcept
          : source(&typeid(void))
          , target(&typeid(void))
        {
        }

        const char* what() const noexcept override;

        virtual ~bad_lexical_cast() noexcept;

        bad_lexical_cast(std::type_info const& source_type_arg,
            std::type_info const& target_type_arg) noexcept
          : source(&source_type_arg)
          , target(&target_type_arg)
        {
        }

        std::type_info const& source_type() const noexcept
        {
            return *source;
        }

        std::type_info const& target_type() const noexcept
        {
            return *target;
        }

    private:
        std::type_info const* source;
        std::type_info const* target;
    };

    namespace detail {

        PIKA_NORETURN PIKA_EXPORT void throw_bad_lexical_cast(
            std::type_info const& source_type,
            std::type_info const& target_type);

        template <typename Source, typename Target>
        PIKA_NORETURN inline Target throw_bad_lexical_cast()
        {
            detail::throw_bad_lexical_cast(typeid(Source), typeid(Target));
        }
    }    // namespace detail

}}    // namespace pika::util

#include <pika/config/warnings_suffix.hpp>