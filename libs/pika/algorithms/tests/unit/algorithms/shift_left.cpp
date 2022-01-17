//  Copyright (c) 2014 Hartmut Kaiser
//  Copyright (c) 2021 Akhil J Nair
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/init.hpp>
#include <pika/modules/testing.hpp>
#include <pika/parallel/algorithms/shift_left.hpp>

#include <atomic>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "test_utils.hpp"

#define ARR_SIZE 100007

////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag>
void test_shift_left_nonbidir(IteratorTag)
{
    std::forward_list<std::size_t> c(ARR_SIZE);
    std::iota(std::begin(c), std::end(c), std::rand());
    std::vector<std::size_t> d;

    for (auto elem : c)
    {
        d.push_back(elem);
    }

    // shift by zero should have no effect
    pika::shift_left(std::begin(c), std::end(c), 0);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    // shift by a negative number should have no effect
    pika::shift_left(std::begin(c), std::end(c), -4);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    std::size_t n = (std::rand() % (std::size_t) ARR_SIZE) + 1;
    pika::shift_left(std::begin(c), std::end(c), n);

    std::move(std::begin(d) + n, std::end(d), std::begin(d));

    // verify values
    PIKA_TEST(std::equal(std::begin(c),
        std::next(std::begin(c), ((std::size_t) ARR_SIZE - n)), std::begin(d)));

    // ensure shift by more than n does not crash
    pika::shift_left(std::begin(c), std::end(c), (std::size_t)(ARR_SIZE + 1));
}

template <typename IteratorTag>
void test_shift_left(IteratorTag)
{
    std::vector<std::size_t> c(ARR_SIZE);
    std::iota(std::begin(c), std::end(c), std::rand());
    std::vector<std::size_t> d = c;

    // shift by zero should have no effect
    pika::shift_left(std::begin(c), std::end(c), 0);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    // shift by a negative number should have no effect
    pika::shift_left(std::begin(c), std::end(c), -4);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    std::size_t n = (std::rand() % (std::size_t) ARR_SIZE) + 1;
    pika::shift_left(std::begin(c), std::end(c), n);

    std::move(std::begin(d) + n, std::end(d), std::begin(d));

    // verify values
    PIKA_TEST(std::equal(std::begin(c),
        std::begin(c) + ((std::size_t) ARR_SIZE - n), std::begin(d)));

    // ensure shift by more than n does not crash
    pika::shift_left(std::begin(c), std::end(c), (std::size_t)(ARR_SIZE + 1));
}

template <typename ExPolicy, typename IteratorTag>
void test_shift_left(ExPolicy policy, IteratorTag)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    std::vector<std::size_t> c(ARR_SIZE);
    std::iota(std::begin(c), std::end(c), std::rand());
    std::vector<std::size_t> d = c;

    // shift by zero should have no effect
    pika::shift_left(policy, std::begin(c), std::end(c), 0);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    // shift by a negative number should have no effect
    pika::shift_left(policy, std::begin(c), std::end(c), -4);
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    std::size_t n = (std::rand() % (std::size_t) ARR_SIZE) + 1;
    pika::shift_left(policy, std::begin(c), std::end(c), n);

    std::move(std::begin(d) + n, std::end(d), std::begin(d));

    // verify values
    PIKA_TEST(std::equal(std::begin(c),
        std::begin(c) + ((std::size_t) ARR_SIZE - n), std::begin(d)));

    // ensure shift by more than n does not crash
    pika::shift_left(
        policy, std::begin(c), std::end(c), (std::size_t)(ARR_SIZE + 1));
}

template <typename ExPolicy, typename IteratorTag>
void test_shift_left_async(ExPolicy p, IteratorTag)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    std::vector<std::size_t> c(ARR_SIZE);
    std::iota(std::begin(c), std::end(c), std::rand());
    std::vector<std::size_t> d = c;

    // shift by zero should have no effect
    auto f = pika::shift_left(p, std::begin(c), std::end(c), 0);
    f.wait();
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    // shift by a negative number should have no effect
    auto f1 = pika::shift_left(p, std::begin(c), std::end(c), -4);
    f1.wait();
    PIKA_TEST(std::equal(std::begin(c), std::end(c), std::begin(d)));

    std::size_t n = (std::rand() % (std::size_t) ARR_SIZE) + 1;
    auto f2 = pika::shift_left(p, std::begin(c), std::end(c), n);
    f2.wait();

    std::move(std::begin(d) + n, std::end(d), std::begin(d));

    // verify values
    PIKA_TEST(std::equal(std::begin(c),
        std::begin(c) + ((std::size_t) ARR_SIZE - n), std::begin(d)));

    // ensure shift by more than n does not crash
    auto f3 = pika::shift_left(
        p, std::begin(c), std::end(c), (std::size_t)(ARR_SIZE + 1));
    f3.wait();
}

template <typename IteratorTag>
void test_shift_left()
{
    using namespace pika::execution;
    test_shift_left_nonbidir(IteratorTag());
    test_shift_left(IteratorTag());
    test_shift_left(seq, IteratorTag());
    test_shift_left(par, IteratorTag());
    test_shift_left(par_unseq, IteratorTag());

    test_shift_left_async(seq(task), IteratorTag());
    test_shift_left_async(par(task), IteratorTag());
}

void shift_left_test()
{
    test_shift_left<std::random_access_iterator_tag>();
    test_shift_left<std::forward_iterator_tag>();
}

int pika_main(pika::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int) std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    shift_left_test();
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
