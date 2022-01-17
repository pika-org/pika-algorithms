//  Copyright (c) 2015 Daniel Bourgeois
//  Copyright (c) 2020 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/init.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "transform_reduce_binary_tests_range.hpp"

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag>
void test_transform_reduce_binary()
{
    using namespace pika::execution;

    test_transform_reduce_binary(IteratorTag());

    test_transform_reduce_binary(seq, IteratorTag());
    test_transform_reduce_binary(par, IteratorTag());
    test_transform_reduce_binary(par_unseq, IteratorTag());

    test_transform_reduce_binary_async(seq(task), IteratorTag());
    test_transform_reduce_binary_async(par(task), IteratorTag());
}

void transform_reduce_binary_test()
{
    test_transform_reduce_binary<std::random_access_iterator_tag>();
    test_transform_reduce_binary<std::forward_iterator_tag>();
}

///////////////////////////////////////////////////////////////////////////////
int pika_main(pika::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int) std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    transform_reduce_binary_test();

    return pika::local::finalize();
}

int main(int argc, char* argv[])
{
    // add command line option which controls the random number generator seed
    using namespace pika::program_options;
    options_description desc_commandline(
        "Usage: " PIKA_APPLICATION_STRING " [options]");

    desc_commandline.add_options()("seed,s", value<unsigned int>(),
        "the random number generator seed to use for this run");

    // By default this test should run on all available cores
    std::vector<std::string> const cfg = {"pika.os_threads=all"};

    // Initialize and run pika
    pika::local::init_params init_args;
    init_args.desc_cmdline = desc_commandline;
    init_args.cfg = cfg;

    PIKA_TEST_EQ_MSG(pika::local::init(pika_main, argc, argv, init_args), 0,
        "pika main exited with non-zero status");

    return pika::util::report_errors();
}
