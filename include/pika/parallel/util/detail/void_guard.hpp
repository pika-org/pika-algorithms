//  Copyright (c) 2013 Agustin Berge
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>

namespace pika::parallel::detail {
    ///////////////////////////////////////////////////////////////////////////
    // This utility simplifies templates returning compatible types
    //
    // Usage: return void_guard<Result>(), expr;
    // - Result != void -> return expr;
    // - Result == void -> return (void)expr;
    template <typename Result>
    struct void_guard
    {
    };

    template <>
    struct void_guard<void>
    {
        template <typename T>
        constexpr void operator,(T const&) const noexcept
        {
        }
    };
}    // namespace pika::parallel::detail
