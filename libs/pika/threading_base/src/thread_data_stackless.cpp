//  Copyright (c) 2019 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/config.hpp>
#include <pika/allocator_support/internal_allocator.hpp>
#include <pika/modules/logging.hpp>
#include <pika/threading_base/thread_data.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace pika { namespace threads {

    util::internal_allocator<thread_data_stackless>
        thread_data_stackless::thread_alloc_;

    thread_data_stackless::~thread_data_stackless()
    {
        LTM_(debug).format(
            "~thread_data_stackless({}), description({}), phase({})", this,
            this->get_description(), this->get_thread_phase());
    }

}}    // namespace pika::threads
