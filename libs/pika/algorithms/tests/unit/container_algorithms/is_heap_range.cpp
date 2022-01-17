//  Copyright (c) 2017 Taeguk Kwon
//  Copyright (c) 2020 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/init.hpp>
#include <pika/modules/testing.hpp>
#include <pika/parallel/container_algorithms/is_heap.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "test_utils.hpp"

////////////////////////////////////////////////////////////////////////////
struct user_defined_type
{
    user_defined_type() = default;
    user_defined_type(int rand_no)
      : val(rand_no)
    {
    }

    bool operator<(user_defined_type const& t) const
    {
        if (this->name < t.name)
            return true;
        else if (this->name > t.name)
            return false;
        else
            return this->val < t.val;
    }

    const user_defined_type& operator++()
    {
        static const std::vector<std::string> name_list = {
            "ABB", "ABC", "ACB", "BCA", "CAA", "CAAA", "CAAB"};
        name = name_list[std::rand() % name_list.size()];
        ++val;
        return *this;
    }

    std::string name;
    int val;
};

////////////////////////////////////////////////////////////////////////////
template <typename DataType>
void test_is_heap(DataType)
{
    std::size_t const size = 10007;
    std::vector<DataType> c(size);
    std::iota(std::begin(c), std::end(c), DataType(std::rand()));

    auto heap_end_iter = std::next(std::begin(c), std::rand() % c.size());
    std::make_heap(std::begin(c), heap_end_iter);

    bool result = pika::ranges::is_heap(c);
    bool solution = std::is_heap(std::begin(c), std::end(c));

    PIKA_TEST_EQ(result, solution);
}

template <typename ExPolicy, typename DataType>
void test_is_heap(ExPolicy&& policy, DataType)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    std::size_t const size = 10007;
    std::vector<DataType> c(size);
    std::iota(std::begin(c), std::end(c), DataType(std::rand()));

    auto heap_end_iter = std::next(std::begin(c), std::rand() % c.size());
    std::make_heap(std::begin(c), heap_end_iter);

    bool result = pika::ranges::is_heap(policy, c);
    bool solution = std::is_heap(std::begin(c), std::end(c));

    PIKA_TEST_EQ(result, solution);
}

template <typename ExPolicy, typename DataType>
void test_is_heap_async(ExPolicy&& policy, DataType)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    std::size_t const size = 10007;
    std::vector<DataType> c(size);
    std::iota(std::begin(c), std::end(c), DataType(std::rand()));

    auto heap_end_iter = std::next(std::begin(c), std::rand() % c.size());
    std::make_heap(std::begin(c), heap_end_iter);

    auto f = pika::ranges::is_heap(policy, c);
    bool result = f.get();
    bool solution = std::is_heap(std::begin(c), std::end(c));

    PIKA_TEST_EQ(result, solution);
}

template <typename DataType>
void test_is_heap()
{
    using namespace pika::execution;

    test_is_heap(DataType());

    test_is_heap(seq, DataType());
    test_is_heap(par, DataType());
    test_is_heap(par_unseq, DataType());

    test_is_heap_async(seq(task), DataType());
    test_is_heap_async(par(task), DataType());
}

void test_is_heap()
{
    test_is_heap<int>();
    test_is_heap<user_defined_type>();
}

int pika_main(pika::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int) std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    test_is_heap();
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
