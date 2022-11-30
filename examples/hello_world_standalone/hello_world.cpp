//  Copyright (c) 2022 ETH Zurich
//  Copyright (c) 2012 Bryce Lelbach
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/algorithm.hpp>
#include <pika/init.hpp>
#include <pika/thread.hpp>

#include <fmt/printf.h>

#include <iostream>

int pika_main()
{
    pika::for_loop(pika::execution::par, 0, 42, [](int i) {
        fmt::print(std::cout, "Hello from pika-thread with id {} and i {}\n",
            pika::this_thread::get_id(), i);
    });

    return pika::finalize();
}

int main(int argc, char* argv[])
{
    return pika::init(pika_main, argc, argv);
}
