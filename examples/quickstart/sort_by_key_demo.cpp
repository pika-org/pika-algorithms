//  Copyright (c) 2016 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/execution.hpp>
#include <pika/init.hpp>
#include <pika/parallel/algorithms/sort_by_key.hpp>

#include <cstddef>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
void print_sequence(
    std::vector<int> const& keys, std::vector<char> const& values)
{
    for (std::size_t i = 0; i != keys.size(); ++i)
    {
        std::cout << "[" << keys[i] << ", " << values[i] << "]";
        if (i != keys.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

int pika_main()
{
    {
        std::vector<int> keys = {1, 4, 2, 8, 5, 7, 1, 4, 2, 8, 5, 7, 1, 4, 2, 8,
            5, 7, 1, 4, 2, 8, 5, 7, 1, 4, 2, 8, 5, 7, 1, 4, 2, 8, 5, 7};
        std::vector<char> values = {'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
            'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd',
            'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e',
            'f'};

        std::cout << "unsorted sequence: {";
        print_sequence(keys, values);

        pika::parallel::sort_by_key(
            pika::execution::par, keys.begin(), keys.end(), values.begin());

        std::cout << "sorted sequence:   {";
        print_sequence(keys, values);
    }

    return pika::finalize();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    return pika::init(pika_main, argc, argv);    // Initialize and run pika
}
