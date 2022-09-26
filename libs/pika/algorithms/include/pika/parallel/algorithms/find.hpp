//  Copyright (c) 2014 Grant Mercer
//  Copyright (c) 2017-2018 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/algorithms/find.hpp

#pragma once

#if defined(DOXYGEN)
namespace pika {
    // clang-format off

    /// Returns the first element in the range [first, last) that is equal
    /// to value
    ///
    /// \note   Complexity: At most last - first
    ///         applications of the operator==().
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter     The type of the source iterators used for the
    ///                     first range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam T           The type of the value to find (deduced).
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param val          the value to compare the elements to
    ///
    /// The comparison operations in the parallel \a find algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a find algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a find algorithm returns a \a pika::future<FwdIter> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter otherwise.
    ///           The \a find algorithm returns the first element in the range
    ///           [first,last) that is equal to \a val.
    ///           If no such element in the range of [first,last) is equal to
    ///           \a val, then the algorithm returns \a last.
    ///
    template <typename ExPolicy, typename FwdIter, typename T>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter>::type
    find(ExPolicy&& policy, FwdIter first, FwdIter last, T const& val);

    /// Returns the first element in the range [first, last) for which
    /// predicate \a f returns true
    ///
    /// \note   Complexity: At most last - first
    ///         applications of the predicate.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter     The type of the source iterators used for the
    ///                     first range (deduced).
    ///                     This iterator type must meet the requirements of a
    ///                     forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param f            The unary predicate which returns true for the
    ///                     required element. The signature of the predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     bool pred(const Type &a);
    ///                     \endcode \n
    ///                     The signature does not need to have const &, but
    ///                     the function must not modify the objects passed to
    ///                     it. The type \a Type must be such
    ///                     that objects of type \a FwdIter can
    ///                     be dereferenced and then implicitly converted to
    ///                     \a Type.
    ///
    /// The comparison operations in the parallel \a find_if algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a find_if algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a find_if algorithm returns a \a pika::future<FwdIter> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter otherwise.
    ///           The \a find_if algorithm returns the first element in the range
    ///           [first,last) that satisfies the predicate \a f.
    ///           If no such element exists that satisfies the predicate f, the
    ///           algorithm returns \a last.
    ///
    template <typename ExPolicy, typename FwdIter, typename F>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter>::type
    find_if(ExPolicy&& policy, FwdIter first, FwdIter last, F&& f);

    /// Returns the first element in the range [first, last) for which
    /// predicate \a f returns false
    ///
    /// \note   Complexity: At most last - first
    ///         applications of the predicate.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter     The type of the source iterators used for the
    ///                     first range (deduced).
    ///                     This iterator type must meet the requirements of a
    ///                     forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param f            The unary predicate which returns false for the
    ///                     required element. The signature of the predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     bool pred(const Type &a);
    ///                     \endcode \n
    ///                     The signature does not need to have const &, but
    ///                     the function must not modify the objects passed to
    ///                     it. The type \a Type must be such
    ///                     that objects of type \a FwdIter can
    ///                     be dereferenced and then implicitly converted to
    ///                     \a Type.
    ///
    /// The comparison operations in the parallel \a find_if_not algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a find_if_not algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a find_if_not algorithm returns a \a pika::future<FwdIter> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter otherwise.
    ///           The \a find_if_not algorithm returns the first element in the range
    ///           [first, last) that does \b not satisfy the predicate \a f.
    ///           If no such element exists that does not satisfy the predicate f, the
    ///           algorithm returns \a last.
    ///
    template <typename ExPolicy, typename FwdIter, typename F>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter>::type
    find_if_not(ExPolicy&& policy, FwdIter first, FwdIter last, F&& f);

    /// Returns the last subsequence of elements [first2, last2) found in the range
    /// [first, last) using the given predicate \a f to compare elements.
    ///
    /// \note   Complexity: at most S*(N-S+1) comparisons where
    ///         \a S = distance(first2, last2) and
    ///         \a N = distance(first1, last1).
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter1    The type of the source iterators used for the
    ///                     first range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam FwdIter2    The type of the source iterators used for the
    ///                     second range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Pred        The type of an optional function/function object to use.
    ///                     Unlike its sequential form, the parallel
    ///                     overload of \a replace requires \a Pred to meet the
    ///                     requirements of \a CopyConstructible. This defaults
    ///                     to std::equal_to<>
    /// \tparam Proj        The type of an optional projection function. This
    ///                     defaults to \a pika::parallel::detail::projection_identity and is applied
    ///                     to the elements of type dereferenced \a FwdIter1
    ///                     and dereferenced \a FwdIter2.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first1       Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last1        Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param first2       Refers to the beginning of the sequence of elements
    ///                     the algorithm will be searching for.
    /// \param last2        Refers to the end of the sequence of elements of
    ///                     the algorithm will be searching for.
    /// \param op           The binary predicate which returns \a true
    ///                     if the elements should be treated as equal. The signature
    ///                     should be equivalent to the following:
    ///                     \code
    ///                     bool pred(const Type1 &a, const Type2 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const &, but
    ///                     the function must not modify the objects passed to
    ///                     it. The types \a Type1 and \a Type2 must be such
    ///                     that objects of types \a FwdIter1 and \a FwdIter2
    ///                     can be dereferenced and then implicitly converted
    ///                     to \a Type1 and \a Type2 respectively.
    /// \param proj         Specifies the function (or function object) which
    ///                     will be invoked for each of the elements of type
    ///                     dereferenced \a FwdIter1 and dereferenced \a FwdIter2
    ///                     as a projection operation before the function \a f
    ///                     is invoked.
    ///
    /// The comparison operations in the parallel \a find_end algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a find_end algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a find_end algorithm returns a \a pika::future<FwdIter> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter otherwise.
    ///           The \a find_end algorithm returns an iterator to the beginning of
    ///           the last subsequence [first2, last2) in range [first, last).
    ///           If the length of the subsequence [first2, last2) is greater
    ///           than the length of the range [first1, last1), \a last1 is returned.
    ///           Additionally if the size of the subsequence is empty or no subsequence
    ///           is found, \a last1 is also returned.
    ///
    /// This overload of \a find_end is available if the user decides to provide the
    /// algorithm their own predicate \a f.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
        typename Pred = detail::equal_to>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter1>::type
    find_end(ExPolicy&& policy, FwdIter1 first1, FwdIter1 last1,
        FwdIter2 first2, FwdIter2 last2, Pred&& op = Pred());

    /// Searches the range [first, last) for any elements in the range [s_first, s_last).
    /// Uses binary predicate p to compare elements
    ///
    /// \note   Complexity: at most (S*N) comparisons where
    ///         \a S = distance(s_first, s_last) and
    ///         \a N = distance(first, last).
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter1    The type of the source iterators used for the
    ///                     first range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward  iterator.
    /// \tparam FwdIter2    The type of the source iterators used for the
    ///                     second range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Pred        The type of an optional function/function object to use.
    ///                     Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a Pred to meet the
    ///                     requirements of \a CopyConstructible. This defaults
    ///                     to std::equal_to<>
    /// \tparam Proj1       The type of an optional projection function. This
    ///                     defaults to \a pika::parallel::detail::projection_identity and is applied
    ///                     to the elements of type dereferenced \a FwdIter1.
    /// \tparam Proj2       The type of an optional projection function. This
    ///                     defaults to \a pika::parallel::detail::projection_identity and is applied
    ///                     to the elements of type dereferenced \a FwdIter2.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param s_first      Refers to the beginning of the sequence of elements
    ///                     the algorithm will be searching for.
    /// \param s_last       Refers to the end of the sequence of elements of
    ///                     the algorithm will be searching for.
    /// \param op           The binary predicate which returns \a true
    ///                     if the elements should be treated as equal. The signature
    ///                     should be equivalent to the following:
    ///                     \code
    ///                     bool pred(const Type1 &a, const Type2 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const &, but
    ///                     the function must not modify the objects passed to
    ///                     it. The types \a Type1 and \a Type2 must be such
    ///                     that objects of types \a FwdIter1 and \a FwdIter2
    ///                     can be dereferenced and then implicitly converted
    ///                     to \a Type1 and \a Type2 respectively.
    /// \param proj1        Specifies the function (or function object) which
    ///                     will be invoked for each of the elements of type
    ///                     dereferenced \a FwdIter1 as a projection operation
    ///                     before the function \a op is invoked.
    /// \param proj2        Specifies the function (or function object) which
    ///                     will be invoked for each of the elements of type
    ///                     dereferenced \a FwdIter2 as a projection operation
    ///                     before the function \a op is invoked.
    ///
    /// The comparison operations in the parallel \a find_first_of algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a find_first_of algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a find_first_of algorithm returns a \a pika::future<FwdIter1> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter1 otherwise.
    ///           The \a find_first_of algorithm returns an iterator to the first element
    ///           in the range [first, last) that is equal to an element from the range
    ///           [s_first, s_last).
    ///           If the length of the subsequence [s_first, s_last) is
    ///           greater than the length of the range [first, last),
    ///           \a last is returned.
    ///           Additionally if the size of the subsequence is empty or no subsequence
    ///           is found, \a last is also returned.
    ///           This overload of \a find_end is available if
    ///           the user decides to provide the
    ///           algorithm their own predicate \a f.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
        typename Pred = detail::equal_to>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter1>::type
    find_first_of(ExPolicy&& policy, FwdIter1 first, FwdIter1 last,
        FwdIter2 s_first, FwdIter2 s_last, Pred&& op = Pred());

    // clang-format on
}    // namespace pika

#else    // DOXYGEN

#include <pika/config.hpp>
#include <pika/concepts/concepts.hpp>
#include <pika/functional/invoke.hpp>
#include <pika/iterator_support/traits/is_iterator.hpp>
#include <pika/parallel/util/detail/sender_util.hpp>

#include <pika/algorithms/traits/projected.hpp>
#include <pika/execution/algorithms/detail/predicates.hpp>
#include <pika/executors/execution_policy.hpp>
#include <pika/parallel/algorithms/detail/advance_to_sentinel.hpp>
#include <pika/parallel/algorithms/detail/dispatch.hpp>
#include <pika/parallel/algorithms/detail/distance.hpp>
#include <pika/parallel/algorithms/detail/find.hpp>
#include <pika/parallel/util/compare_projected.hpp>
#include <pika/parallel/util/detail/algorithm_result.hpp>
#include <pika/parallel/util/invoke_projected.hpp>
#include <pika/parallel/util/loop.hpp>
#include <pika/parallel/util/partitioner.hpp>
#include <pika/parallel/util/projection_identity.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace pika::parallel::detail {
    ///////////////////////////////////////////////////////////////////////////
    // find
    template <typename FwdIter>
    struct find : public algorithm<find<FwdIter>, FwdIter>
    {
        find()
          : find::algorithm("find")
        {
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename T,
            typename Proj = projection_identity>
        static constexpr Iter sequential(
            ExPolicy, Iter first, Sent last, T const& val, Proj&& proj = Proj())
        {
            return sequential_find<ExPolicy>(
                first, last, val, PIKA_FORWARD(Proj, proj));
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename T,
            typename Proj = projection_identity>
        static typename algorithm_result<ExPolicy, Iter>::type parallel(
            ExPolicy&& policy, Iter first, Sent last, T const& val,
            Proj&& proj = Proj())
        {
            using result = algorithm_result<ExPolicy, Iter>;
            using type = typename std::iterator_traits<Iter>::value_type;
            using difference_type =
                typename std::iterator_traits<Iter>::difference_type;

            difference_type count = detail::distance(first, last);
            if (count <= 0)
                return result::get(PIKA_MOVE(last));

            util::cancellation_token<std::size_t> tok(count);

            // Note: replacing the invoke() with PIKA_INVOKE()
            // below makes gcc generate errors
            auto f1 = [val, proj = PIKA_FORWARD(Proj, proj), tok](Iter it,
                          std::size_t part_size,
                          std::size_t base_idx) mutable -> void {
                loop_idx_n<std::decay_t<ExPolicy>>(base_idx, it, part_size, tok,
                    [&val, &proj, &tok](
                        type& v, std::size_t i) mutable -> void {
                        if (pika::util::detail::invoke(proj, v) == val)
                        {
                            tok.cancel(i);
                        }
                    });
            };

            auto f2 =
                [tok, count, first, last](
                    std::vector<pika::future<void>>&& data) mutable -> Iter {
                // make sure iterators embedded in function object that is
                // attached to futures are invalidated
                data.clear();

                difference_type find_res =
                    static_cast<difference_type>(tok.get_data());

                if (find_res != count)
                {
                    std::advance(first, find_res);
                }
                else
                {
                    first = detail::advance_to_sentinel(first, last);
                }
                return PIKA_MOVE(first);
            };

            return partitioner<ExPolicy, Iter, void>::call_with_index(
                PIKA_FORWARD(ExPolicy, policy), first, count, 1, PIKA_MOVE(f1),
                PIKA_MOVE(f2));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // find_if
    template <typename FwdIter>
    struct find_if : public algorithm<find_if<FwdIter>, FwdIter>
    {
        find_if()
          : find_if::algorithm("find_if")
        {
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename F,
            typename Proj = projection_identity>
        static constexpr Iter sequential(
            ExPolicy, Iter first, Sent last, F&& f, Proj&& proj = Proj())
        {
            return sequential_find_if<ExPolicy>(
                first, last, PIKA_FORWARD(F, f), PIKA_FORWARD(Proj, proj));
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename F,
            typename Proj = projection_identity>
        static typename algorithm_result<ExPolicy, Iter>::type parallel(
            ExPolicy&& policy, Iter first, Sent last, F&& f,
            Proj&& proj = Proj())
        {
            using result = algorithm_result<ExPolicy, Iter>;
            using type = typename std::iterator_traits<Iter>::value_type;
            using difference_type =
                typename std::iterator_traits<Iter>::difference_type;

            difference_type count = detail::distance(first, last);
            if (count <= 0)
                return result::get(PIKA_MOVE(last));

            util::cancellation_token<std::size_t> tok(count);

            // Note: replacing the invoke() with PIKA_INVOKE()
            // below makes gcc generate errors
            auto f1 = [f = PIKA_FORWARD(F, f), proj = PIKA_FORWARD(Proj, proj),
                          tok](Iter it, std::size_t part_size,
                          std::size_t base_idx) mutable -> void {
                loop_idx_n<std::decay_t<ExPolicy>>(base_idx, it, part_size, tok,
                    [&f, &proj, &tok](type& v, std::size_t i) mutable -> void {
                        if (pika::util::detail::invoke(
                                f, pika::util::detail::invoke(proj, v)))
                        {
                            tok.cancel(i);
                        }
                    });
            };

            auto f2 =
                [tok, count, first, last](
                    std::vector<pika::future<void>>&& data) mutable -> Iter {
                // make sure iterators embedded in function object that is
                // attached to futures are invalidated
                data.clear();

                difference_type find_res =
                    static_cast<difference_type>(tok.get_data());

                if (find_res != count)
                {
                    std::advance(first, find_res);
                }
                else
                {
                    first = detail::advance_to_sentinel(first, last);
                }
                return PIKA_MOVE(first);
            };

            return partitioner<ExPolicy, Iter, void>::call_with_index(
                PIKA_FORWARD(ExPolicy, policy), first, count, 1, PIKA_MOVE(f1),
                PIKA_MOVE(f2));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // find_if_not
    template <typename FwdIter>
    struct find_if_not : public algorithm<find_if_not<FwdIter>, FwdIter>
    {
        find_if_not()
          : find_if_not::algorithm("find_if_not")
        {
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename F,
            typename Proj = projection_identity>
        static constexpr Iter sequential(
            ExPolicy, Iter first, Sent last, F&& f, Proj&& proj = Proj())
        {
            return sequential_find_if_not<ExPolicy>(
                first, last, PIKA_FORWARD(F, f), PIKA_FORWARD(Proj, proj));
        }

        template <typename ExPolicy, typename Iter, typename Sent, typename F,
            typename Proj = projection_identity>
        static typename algorithm_result<ExPolicy, Iter>::type parallel(
            ExPolicy&& policy, Iter first, Sent last, F&& f,
            Proj&& proj = Proj())
        {
            using result = algorithm_result<ExPolicy, Iter>;
            using type = typename std::iterator_traits<Iter>::value_type;
            using difference_type =
                typename std::iterator_traits<Iter>::difference_type;

            difference_type count = detail::distance(first, last);
            if (count <= 0)
                return result::get(PIKA_MOVE(last));

            util::cancellation_token<std::size_t> tok(count);

            // Note: replacing the invoke() with PIKA_INVOKE()
            // below makes gcc generate errors
            auto f1 = [f = PIKA_FORWARD(F, f), proj = PIKA_FORWARD(Proj, proj),
                          tok](Iter it, std::size_t part_size,
                          std::size_t base_idx) mutable -> void {
                loop_idx_n<std::decay_t<ExPolicy>>(base_idx, it, part_size, tok,
                    [&f, &proj, &tok](type& v, std::size_t i) mutable -> void {
                        if (!pika::util::detail::invoke(
                                f, pika::util::detail::invoke(proj, v)))
                        {
                            tok.cancel(i);
                        }
                    });
            };

            auto f2 =
                [tok, count, first, last](
                    std::vector<pika::future<void>>&& data) mutable -> Iter {
                // make sure iterators embedded in function object that is
                // attached to futures are invalidated
                data.clear();

                difference_type find_res =
                    static_cast<difference_type>(tok.get_data());

                if (find_res != count)
                {
                    std::advance(first, find_res);
                }
                else
                {
                    first = detail::advance_to_sentinel(first, last);
                }
                return PIKA_MOVE(first);
            };

            return partitioner<ExPolicy, Iter, void>::call_with_index(
                PIKA_FORWARD(ExPolicy, policy), first, count, 1, PIKA_MOVE(f1),
                PIKA_MOVE(f2));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // find_end
    template <typename Iter1, typename Sent1, typename Iter2, typename Sent2,
        typename Pred, typename Proj1, typename Proj2>
    constexpr Iter1 sequential_search(Iter1 first1, Sent1 last1, Iter2 first2,
        Sent2 last2, Pred&& op, Proj1&& proj1, Proj2&& proj2)
    {
        for (/**/; /**/; ++first1)
        {
            Iter1 it1 = first1;
            for (Iter2 it2 = first2; /**/; (void) ++it1, ++it2)
            {
                if (it2 == last2)
                {
                    return first1;
                }
                if (it1 == last1)
                {
                    return last1;
                }
                if (!PIKA_INVOKE(
                        op, PIKA_INVOKE(proj1, *it1), PIKA_INVOKE(proj2, *it2)))
                {
                    break;
                }
            }
        }
    }

    template <typename Iter1, typename Sent1, typename Iter2, typename Sent2,
        typename Pred, typename Proj1, typename Proj2>
    constexpr Iter1 sequential_find_end(Iter1 first1, Sent1 last1, Iter2 first2,
        Sent2 last2, Pred&& op, Proj1&& proj1, Proj2&& proj2)
    {
        if (first2 == last2)
        {
            return detail::advance_to_sentinel(first1, last1);
        }

        Iter1 result = last1;
        while (true)
        {
            Iter1 new_result = sequential_search(
                first1, last1, first2, last2, op, proj1, proj2);

            if (new_result == last1)
            {
                break;
            }
            else
            {
                result = new_result;
                first1 = result;
                ++first1;
            }
        }
        return result;
    }

    template <typename FwdIter>
    struct find_end : public algorithm<find_end<FwdIter>, FwdIter>
    {
        find_end()
          : find_end::algorithm("find_end")
        {
        }

        template <typename ExPolicy, typename Iter1, typename Sent1,
            typename Iter2, typename Sent2, typename Pred, typename Proj1,
            typename Proj2>
        static constexpr Iter1 sequential(ExPolicy, Iter1 first1, Sent1 last1,
            Iter2 first2, Sent2 last2, Pred&& op, Proj1&& proj1, Proj2&& proj2)
        {
            return sequential_find_end(first1, last1, first2, last2,
                PIKA_FORWARD(Pred, op), PIKA_FORWARD(Proj1, proj1),
                PIKA_FORWARD(Proj2, proj2));
        }

        template <typename ExPolicy, typename Iter1, typename Sent1,
            typename Iter2, typename Sent2, typename Pred, typename Proj1,
            typename Proj2>
        static typename algorithm_result<ExPolicy, Iter1>::type parallel(
            ExPolicy&& policy, Iter1 first1, Sent1 last1, Iter2 first2,
            Sent2 last2, Pred&& op, Proj1&& proj1, Proj2&& proj2)
        {
            using result_type = algorithm_result<ExPolicy, Iter1>;

            using difference_type =
                typename std::iterator_traits<Iter1>::difference_type;

            difference_type diff = detail::distance(first2, last2);
            if (diff <= 0)
            {
                return result_type::get(PIKA_MOVE(last1));
            }

            difference_type count = detail::distance(first1, last1);
            if (diff > count)
            {
                return result_type::get(PIKA_MOVE(last1));
            }

            util::cancellation_token<difference_type,
                std::greater<difference_type>>
                tok(-1);

            auto f1 = [diff, tok, first2, op = PIKA_FORWARD(Pred, op),
                          proj1 = PIKA_FORWARD(Proj1, proj1),
                          proj2 = PIKA_FORWARD(Proj2, proj2)](Iter1 it,
                          std::size_t part_size,
                          std::size_t base_idx) mutable -> void {
                loop_idx_n<std::decay_t<ExPolicy>>(base_idx, it, part_size, tok,
                    [=, &tok, &op, &proj1, &proj2](
                        auto t, std::size_t i) mutable -> void {
                        // Note: replacing the invoke() with PIKA_INVOKE()
                        // below makes gcc generate errors
                        if (PIKA_INVOKE(op, PIKA_INVOKE(proj1, t),
                                pika::util::detail::invoke(proj2, *first2)))
                        {
                            difference_type local_count = 1;
                            auto mid = t;
                            auto mid2 = first2;
                            ++mid;
                            ++mid2;

                            for (; local_count != diff;
                                 (void) ++local_count, ++mid, ++mid2)
                            {
                                if (!PIKA_INVOKE(op, PIKA_INVOKE(proj1, mid),
                                        pika::util::detail::invoke(
                                            proj2, *mid2)))
                                {
                                    break;
                                }
                            }

                            if (local_count == diff)
                            {
                                tok.cancel(i);
                            }
                        }
                    });
            };

            auto f2 =
                [tok, count, first1, last1](
                    std::vector<pika::future<void>>&& data) mutable -> Iter1 {
                // make sure iterators embedded in function object that is
                // attached to futures are invalidated
                data.clear();

                difference_type find_end_res = tok.get_data();

                if (find_end_res >= 0 && find_end_res != count)
                {
                    std::advance(first1, find_end_res);
                }
                else
                {
                    first1 = last1;
                }
                return PIKA_MOVE(first1);
            };

            return partitioner<ExPolicy, Iter1, void>::call_with_index(
                PIKA_FORWARD(ExPolicy, policy), first1, count - diff + 1, 1,
                PIKA_MOVE(f1), PIKA_MOVE(f2));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // find_first_of
    template <typename FwdIter>
    struct find_first_of : public algorithm<find_first_of<FwdIter>, FwdIter>
    {
        find_first_of()
          : find_first_of::algorithm("find_first_of")
        {
        }

        template <typename ExPolicy, typename InIter1, typename InIter2,
            typename Pred, typename Proj1, typename Proj2>
        static InIter1 sequential(ExPolicy, InIter1 first, InIter1 last,
            InIter2 s_first, InIter2 s_last, Pred&& op, Proj1&& proj1,
            Proj2&& proj2)
        {
            if (first == last)
                return last;

            compare_projected<Pred&, Proj1&, Proj2&> f(op, proj1, proj2);
            for (/* */; first != last; ++first)
            {
                for (InIter2 iter = s_first; iter != s_last; ++iter)
                {
                    if (PIKA_INVOKE(f, *first, *iter))
                    {
                        return first;
                    }
                }
            }
            return last;
        }

        template <typename ExPolicy, typename FwdIter2, typename Pred,
            typename Proj1, typename Proj2>
        static typename algorithm_result<ExPolicy, FwdIter>::type parallel(
            ExPolicy&& policy, FwdIter first, FwdIter last, FwdIter2 s_first,
            FwdIter2 s_last, Pred&& op, Proj1&& proj1, Proj2&& proj2)
        {
            using result = algorithm_result<ExPolicy, FwdIter>;
            using reference = typename std::iterator_traits<FwdIter>::reference;
            using difference_type =
                typename std::iterator_traits<FwdIter>::difference_type;
            using s_difference_type =
                typename std::iterator_traits<FwdIter2>::difference_type;

            s_difference_type diff = std::distance(s_first, s_last);
            if (diff <= 0)
                return result::get(PIKA_MOVE(last));

            difference_type count = std::distance(first, last);
            if (diff > count)
                return result::get(PIKA_MOVE(last));

            util::cancellation_token<difference_type> tok(count);

            auto f1 = [s_first, s_last, tok, op = PIKA_FORWARD(Pred, op),
                          proj1 = PIKA_FORWARD(Proj1, proj1),
                          proj2 = PIKA_FORWARD(Proj2, proj2)](FwdIter it,
                          std::size_t part_size,
                          std::size_t base_idx) mutable -> void {
                loop_idx_n<std::decay_t<ExPolicy>>(base_idx, it, part_size, tok,
                    [&tok, &s_first, &s_last, &op, &proj1, &proj2](
                        reference v, std::size_t i) mutable -> void {
                        compare_projected<Pred&, Proj1&, Proj2&> f(
                            op, proj1, proj2);
                        for (FwdIter2 iter = s_first; iter != s_last; ++iter)
                        {
                            if (PIKA_INVOKE(f, v, *iter))
                            {
                                tok.cancel(i);
                            }
                        }
                    });
            };

            auto f2 =
                [tok, count, first, last](
                    std::vector<pika::future<void>>&& data) mutable -> FwdIter {
                // make sure iterators embedded in function object that is
                // attached to futures are invalidated
                data.clear();

                difference_type find_first_of_res = tok.get_data();

                if (find_first_of_res != count)
                {
                    std::advance(first, find_first_of_res);
                }
                else
                {
                    first = last;
                }

                return PIKA_MOVE(first);
            };

            return partitioner<ExPolicy, FwdIter, void>::call_with_index(
                PIKA_FORWARD(ExPolicy, policy), first, count, 1, PIKA_MOVE(f1),
                PIKA_MOVE(f2));
        }
    };
}    // namespace pika::parallel::detail

namespace pika {
    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::find
    inline constexpr struct find_t final
      : pika::detail::tag_parallel_algorithm<find_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter,
            typename T = typename std::iterator_traits<FwdIter>::value_type,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter>::value
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter>::type
        tag_fallback_invoke(find_t, ExPolicy&& policy, FwdIter first,
            FwdIter last, T const& val)
        {
            static_assert(pika::traits::is_forward_iterator<FwdIter>::value,
                "Requires at least forward iterator.");

            return pika::parallel::detail::find<FwdIter>().call(
                PIKA_FORWARD(ExPolicy, policy), first, last, val,
                pika::parallel::detail::projection_identity{});
        }

        // clang-format off
        template <typename InIter,
            typename T = typename std::iterator_traits<InIter>::value_type,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<InIter>::value
            )>
        // clang-format on
        friend InIter tag_fallback_invoke(
            find_t, InIter first, InIter last, T const& val)
        {
            static_assert(pika::traits::is_input_iterator<InIter>::value,
                "Requires at least input iterator.");

            return pika::parallel::detail::find<InIter>().call(
                pika::execution::seq, first, last, val,
                pika::parallel::detail::projection_identity{});
        }

    } find{};

    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::find_if
    inline constexpr struct find_if_t final
      : pika::detail::tag_parallel_algorithm<find_if_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter, typename F,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter>::value &&
                pika::detail::is_invocable_v<F,
                    typename std::iterator_traits<FwdIter>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter>::type
        tag_fallback_invoke(
            find_if_t, ExPolicy&& policy, FwdIter first, FwdIter last, F&& f)
        {
            static_assert(pika::traits::is_forward_iterator<FwdIter>::value,
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_if<FwdIter>().call(
                PIKA_FORWARD(ExPolicy, policy), first, last, PIKA_FORWARD(F, f),
                pika::parallel::detail::projection_identity{});
        }

        // clang-format off
        template <typename InIter, typename F,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<InIter>::value &&
                pika::detail::is_invocable_v<F,
                    typename std::iterator_traits<InIter>::value_type
                >
            )>
        // clang-format on
        friend InIter tag_fallback_invoke(
            find_if_t, InIter first, InIter last, F&& f)
        {
            static_assert(pika::traits::is_input_iterator<InIter>::value,
                "Requires at least input iterator.");

            return pika::parallel::detail::find_if<InIter>().call(
                pika::execution::seq, first, last, PIKA_FORWARD(F, f),
                pika::parallel::detail::projection_identity{});
        }

    } find_if{};

    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::find_if_not
    inline constexpr struct find_if_not_t final
      : pika::detail::tag_parallel_algorithm<find_if_not_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter, typename F,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter>::value &&
                pika::detail::is_invocable_v<F,
                    typename std::iterator_traits<FwdIter>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter>::type
        tag_fallback_invoke(find_if_not_t, ExPolicy&& policy, FwdIter first,
            FwdIter last, F&& f)
        {
            static_assert(pika::traits::is_forward_iterator<FwdIter>::value,
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_if_not<FwdIter>().call(
                PIKA_FORWARD(ExPolicy, policy), first, last, PIKA_FORWARD(F, f),
                pika::parallel::detail::projection_identity{});
        }

        // clang-format off
        template <typename FwdIter, typename F,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter>::value &&
                pika::detail::is_invocable_v<F,
                    typename std::iterator_traits<FwdIter>::value_type
                >
            )>
        // clang-format on
        friend FwdIter tag_fallback_invoke(
            find_if_not_t, FwdIter first, FwdIter last, F&& f)
        {
            static_assert(pika::traits::is_input_iterator<FwdIter>::value,
                "Requires at least input iterator.");

            return pika::parallel::detail::find_if_not<FwdIter>().call(
                pika::execution::seq, first, last, PIKA_FORWARD(F, f),
                pika::parallel::detail::projection_identity{});
        }

    } find_if_not{};

    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::find_end
    inline constexpr struct find_end_t final
      : pika::detail::tag_parallel_algorithm<find_end_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename Pred,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value &&
                pika::detail::is_invocable_v<Pred,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter2>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter1>::type
        tag_fallback_invoke(find_end_t, ExPolicy&& policy, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2, Pred&& op)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_end<FwdIter1>().call(
                PIKA_FORWARD(ExPolicy, policy), first1, last1, first2, last2,
                PIKA_FORWARD(Pred, op),
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter1>::type
        tag_fallback_invoke(find_end_t, ExPolicy&& policy, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_end<FwdIter1>().call(
                PIKA_FORWARD(ExPolicy, policy), first1, last1, first2, last2,
                pika::parallel::detail::equal_to{},
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename FwdIter1, typename FwdIter2,
            typename Pred,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value &&
                pika::detail::is_invocable_v<Pred,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter2>::value_type
                >
            )>
        // clang-format on
        friend FwdIter1 tag_fallback_invoke(find_end_t, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2, Pred&& op)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_end<FwdIter1>().call(
                pika::execution::seq, first1, last1, first2, last2,
                PIKA_FORWARD(Pred, op),
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename FwdIter1, typename FwdIter2,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value
            )>
        // clang-format on
        friend FwdIter1 tag_fallback_invoke(find_end_t, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::find_end<FwdIter1>().call(
                pika::execution::seq, first1, last1, first2, last2,
                pika::parallel::detail::equal_to{},
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }
    } find_end{};

    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::find_first_of
    inline constexpr struct find_first_of_t final
      : pika::detail::tag_parallel_algorithm<find_first_of_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename Pred,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value &&
                pika::detail::is_invocable_v<Pred,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter2>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter1>::type
        tag_fallback_invoke(find_first_of_t, ExPolicy&& policy, FwdIter1 first,
            FwdIter1 last, FwdIter2 s_first, FwdIter2 s_last, Pred&& op)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Subsequence requires at least forward iterator.");

            return pika::parallel::detail::find_first_of<FwdIter1>().call(
                PIKA_FORWARD(ExPolicy, policy), first, last, s_first, s_last,
                PIKA_FORWARD(Pred, op),
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter1>::type
        tag_fallback_invoke(find_first_of_t, ExPolicy&& policy, FwdIter1 first,
            FwdIter1 last, FwdIter2 s_first, FwdIter2 s_last)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Subsequence requires at least forward iterator.");

            return pika::parallel::detail::find_first_of<FwdIter1>().call(
                PIKA_FORWARD(ExPolicy, policy), first, last, s_first, s_last,
                pika::parallel::detail::equal_to{},
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename FwdIter1, typename FwdIter2, typename Pred,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value &&
                pika::detail::is_invocable_v<Pred,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter2>::value_type
                >
            )>
        // clang-format on
        friend FwdIter1 tag_fallback_invoke(find_first_of_t, FwdIter1 first,
            FwdIter1 last, FwdIter2 s_first, FwdIter2 s_last, Pred&& op)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Subsequence requires at least forward iterator.");

            return pika::parallel::detail::find_first_of<FwdIter1>().call(
                pika::execution::seq, first, last, s_first, s_last,
                PIKA_FORWARD(Pred, op),
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }

        // clang-format off
        template <typename FwdIter1, typename FwdIter2,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value
            )>
        // clang-format on
        friend FwdIter1 tag_fallback_invoke(find_first_of_t, FwdIter1 first,
            FwdIter1 last, FwdIter2 s_first, FwdIter2 s_last)
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Subsequence requires at least forward iterator.");

            return pika::parallel::detail::find_first_of<FwdIter1>().call(
                pika::execution::seq, first, last, s_first, s_last,
                pika::parallel::detail::equal_to{},
                pika::parallel::detail::projection_identity(),
                pika::parallel::detail::projection_identity());
        }
    } find_first_of{};
}    // namespace pika

#endif    // DOXYGEN
