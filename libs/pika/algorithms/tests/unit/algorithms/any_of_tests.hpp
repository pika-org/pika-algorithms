//  Copyright (c) 2014-2020 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/init.hpp>
#include <pika/modules/testing.hpp>
#include <pika/parallel/algorithms/all_any_none.hpp>
#include <pika/parallel/container_algorithms/all_any_none.hpp>
#include <pika/parallel/util/projection_identity.hpp>

#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "test_utils.hpp"

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag>
void test_any_of(IteratorTag)
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool result = pika::any_of(iterator(std::begin(c)),
            iterator(std::end(c)), [](auto v) { return v != 0; });

        // verify values
        bool expected = std::any_of(
            std::begin(c), std::end(c), [](auto v) { return v != 0; });

        PIKA_TEST_EQ(result, expected);
    }
}

template <typename ExPolicy, typename IteratorTag>
void test_any_of(ExPolicy&& policy, IteratorTag)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool result = pika::any_of(policy, iterator(std::begin(c)),
            iterator(std::end(c)), [](auto v) { return v != 0; });

        // verify values
        bool expected = std::any_of(
            std::begin(c), std::end(c), [](auto v) { return v != 0; });

        PIKA_TEST_EQ(result, expected);
    }
}

template <typename IteratorTag,
    typename Proj = pika::parallel::util::projection_identity>
void test_any_of_ranges_seq(IteratorTag, Proj proj = Proj())
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool result = pika::ranges::any_of(
            iterator(std::begin(c)), iterator(std::end(c)),
            [](auto v) { return v != 0; }, proj);

        // verify values
        bool expected = std::any_of(std::begin(c), std::end(c),
            [proj](auto v) { return proj(v) != 0; });

        PIKA_TEST_EQ(result, expected);
    }
}

template <typename ExPolicy, typename IteratorTag,
    typename Proj = pika::parallel::util::projection_identity>
void test_any_of_ranges(ExPolicy&& policy, IteratorTag, Proj proj = Proj())
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool result = pika::ranges::any_of(
            policy, iterator(std::begin(c)), iterator(std::end(c)),
            [](auto v) { return v != 0; }, proj);

        // verify values
        bool expected = std::any_of(std::begin(c), std::end(c),
            [proj](auto v) { return proj(v) != 0; });

        PIKA_TEST_EQ(result, expected);
    }
}

template <typename ExPolicy, typename IteratorTag>
void test_any_of_async(ExPolicy&& p, IteratorTag)
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        pika::future<bool> f = pika::any_of(p, iterator(std::begin(c)),
            iterator(std::end(c)), [](auto v) { return v != 0; });
        f.wait();

        // verify values
        bool expected = std::any_of(
            std::begin(c), std::end(c), [](auto v) { return v != 0; });

        PIKA_TEST_EQ(expected, f.get());
    }
}

template <typename ExPolicy, typename IteratorTag,
    typename Proj = pika::parallel::util::projection_identity>
void test_any_of_ranges_async(ExPolicy&& p, IteratorTag, Proj proj = Proj())
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        pika::future<bool> f = pika::ranges::any_of(
            p, iterator(std::begin(c)), iterator(std::end(c)),
            [](auto v) { return v != 0; }, proj);
        f.wait();

        // verify values
        bool expected = std::any_of(std::begin(c), std::end(c),
            [proj](auto v) { return proj(v) != 0; });

        PIKA_TEST_EQ(expected, f.get());
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag>
void test_any_of_exception(IteratorTag)
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool caught_exception = false;
        try
        {
            pika::any_of(
                iterator(std::begin(c)), iterator(std::end(c)), [](auto v) {
                    return throw std::runtime_error("test"), v != 0;
                });

            PIKA_TEST(false);
        }
        catch (pika::exception_list const& e)
        {
            caught_exception = true;
            test::test_num_exceptions<pika::execution::sequenced_policy,
                IteratorTag>::call(pika::execution::seq, e);
        }
        catch (...)
        {
            PIKA_TEST(false);
        }

        PIKA_TEST(caught_exception);
    }
}

template <typename ExPolicy, typename IteratorTag>
void test_any_of_exception(ExPolicy&& policy, IteratorTag)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool caught_exception = false;
        try
        {
            pika::any_of(policy, iterator(std::begin(c)), iterator(std::end(c)),
                [](auto v) {
                    return throw std::runtime_error("test"), v != 0;
                });

            PIKA_TEST(false);
        }
        catch (pika::exception_list const& e)
        {
            caught_exception = true;
            test::test_num_exceptions<ExPolicy, IteratorTag>::call(policy, e);
        }
        catch (...)
        {
            PIKA_TEST(false);
        }

        PIKA_TEST(caught_exception);
    }
}

template <typename ExPolicy, typename IteratorTag>
void test_any_of_exception_async(ExPolicy&& p, IteratorTag)
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool caught_exception = false;
        bool returned_from_algorithm = false;
        try
        {
            pika::future<void> f = pika::any_of(
                p, iterator(std::begin(c)), iterator(std::end(c)), [](auto v) {
                    return throw std::runtime_error("test"), v != 0;
                });
            returned_from_algorithm = true;
            f.get();

            PIKA_TEST(false);
        }
        catch (pika::exception_list const& e)
        {
            caught_exception = true;
            test::test_num_exceptions<ExPolicy, IteratorTag>::call(p, e);
        }
        catch (...)
        {
            PIKA_TEST(false);
        }

        PIKA_TEST(caught_exception);
        PIKA_TEST(returned_from_algorithm);
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename IteratorTag>
void test_any_of_bad_alloc(ExPolicy&& policy, IteratorTag)
{
    static_assert(pika::is_execution_policy<ExPolicy>::value,
        "pika::is_execution_policy<ExPolicy>::value");

    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool caught_exception = false;
        try
        {
            pika::any_of(policy, iterator(std::begin(c)), iterator(std::end(c)),
                [](auto v) { return throw std::bad_alloc(), v != 0; });

            PIKA_TEST(false);
        }
        catch (std::bad_alloc const&)
        {
            caught_exception = true;
        }
        catch (...)
        {
            PIKA_TEST(false);
        }

        PIKA_TEST(caught_exception);
    }
}

template <typename ExPolicy, typename IteratorTag>
void test_any_of_bad_alloc_async(ExPolicy&& p, IteratorTag)
{
    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    int iseq[] = {0, 23, 10007};
    for (int i : iseq)
    {
        std::vector<int> c = test::fill_all_any_none<int>(10007, i);    //-V106

        bool caught_exception = false;
        bool returned_from_algorithm = false;
        try
        {
            pika::future<void> f =
                pika::any_of(p, iterator(std::begin(c)), iterator(std::end(c)),
                    [](auto v) { return throw std::bad_alloc(), v != 0; });
            returned_from_algorithm = true;
            f.get();

            PIKA_TEST(false);
        }
        catch (std::bad_alloc const&)
        {
            caught_exception = true;
        }
        catch (...)
        {
            PIKA_TEST(false);
        }

        PIKA_TEST(caught_exception);
        PIKA_TEST(returned_from_algorithm);
    }
}
