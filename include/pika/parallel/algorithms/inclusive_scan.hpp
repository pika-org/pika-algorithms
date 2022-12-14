//  Copyright (c) 2014-2020 Hartmut Kaiser
//  Copyright (c) 2016 Minh-Khanh Do
//  Copyright (c) 2021 Akhil J Nair
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/algorithms/inclusive_scan.hpp

#pragma once

#if defined(DOXYGEN)
namespace pika {
    // clang-format off

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(+, *first, ...,
    /// *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam InIter      The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm
    /// invoked without an execution policy object will execute in sequential
    /// order in the calling thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns \a OutIter.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aK)
    ///           + GENERALIZED_NONCOMMUTATIVE_SUM(+, aM, ..., aN)
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum.
    ///
    template <typename InIter, typename OutIter>
    OutIter inclusive_scan(InIter first, InIter last, OutIter dest);

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(+, *first, ...,
    /// *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter1    The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam FwdIter2    The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns a
    ///           \a pika::future<FwdIter2> if
    ///           the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter2 otherwise.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aK)
    ///           + GENERALIZED_NONCOMMUTATIVE_SUM(+, aM, ..., aN)
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter2>::type
    inclusive_scan(ExPolicy&& policy, FwdIter1 first, FwdIter1 last,
        FwdIter2 dest);

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(op, *first, ...,
    ///  *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam InIter      The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    /// \tparam Op          The type of the binary function object used for
    ///                     the reduction operation.
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param op           Specifies the function (or function object) which
    ///                     will be invoked for each of the values of the input
    ///                     sequence. This is a
    ///                     binary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type1 &a, const Type1 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const&, but
    ///                     the function must not modify the objects passed to
    ///                     it.
    ///                     The types \a Type1 and \a Ret must be
    ///                     such that an object of a type as given by the input
    ///                     sequence can be implicitly converted to any
    ///                     of those types.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm
    /// invoked without an execution policy object will execute in sequential
    /// order in the calling thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns \a OutIter.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aK)
    ///           + GENERALIZED_NONCOMMUTATIVE_SUM(+, aM, ..., aN)
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum.
    ///
    template <typename InIter, typename OutIter, typename Op>
    OutIter inclusive_scan(InIter first, InIter last, OutIter dest, Op&& op);

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(op, *first, ...,
    /// *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter1    The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam FwdIter2    The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Op          The type of the binary function object used for
    ///                     the reduction operation.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param op           Specifies the function (or function object) which
    ///                     will be invoked for each of the values of the input
    ///                     sequence. This is a
    ///                     binary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type1 &a, const Type1 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const&, but
    ///                     the function must not modify the objects passed to
    ///                     it.
    ///                     The types \a Type1 and \a Ret must be
    ///                     such that an object of a type as given by the input
    ///                     sequence can be implicitly converted to any
    ///                     of those types.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns a
    ///           \a pika::future<FwdIter2> if
    ///           the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter2 otherwise.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(+, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * GENERALIZED_NONCOMMUTATIVE_SUM(op, a1, ..., aK)
    ///           + GENERALIZED_NONCOMMUTATIVE_SUM(+, aM, ..., aN)
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
        typename Op>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter2>::type
    inclusive_scan(ExPolicy&& policy, FwdIter1 first, FwdIter1 last,
        FwdIter2 dest, Op&& op);

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(op, init, *first, ...,
    /// *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam InIter      The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    /// \tparam Op          The type of the binary function object used for
    ///                     the reduction operation.
    /// \tparam T           The type of the value to be used as initial (and
    ///                     intermediate) values (deduced).
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param op           Specifies the function (or function object) which
    ///                     will be invoked for each of the values of the input
    ///                     sequence. This is a
    ///                     binary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type1 &a, const Type1 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const&, but
    ///                     the function must not modify the objects passed to
    ///                     it.
    ///                     The types \a Type1 and \a Ret must be
    ///                     such that an object of a type as given by the input
    ///                     sequence can be implicitly converted to any
    ///                     of those types.
    /// \param init         The initial value for the generalized sum.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm
    /// invoked without an execution policy object will execute in sequential
    /// order in the calling thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns \a OutIter.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(op, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * op(GENERALIZED_NONCOMMUTATIVE_SUM(op, a1, ..., aK),
    ///           GENERALIZED_NONCOMMUTATIVE_SUM(op, aM, ..., aN))
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum. If
    /// \a op is not mathematically associative, the behavior of
    /// \a inclusive_scan may be non-deterministic.
    ///
    template <typename InIter, typename OutIter,typename T, typename Op>
    OutIter inclusive_scan(InIter first, InIter last, OutIter dest,
        Op&& op, T init);

    ///////////////////////////////////////////////////////////////////////////
    /// Assigns through each iterator \a i in [result, result + (last - first))
    /// the value of
    /// GENERALIZED_NONCOMMUTATIVE_SUM(op, init, *first, ...,
    /// *(first + (i - result))).
    ///
    /// \note   Complexity: O(\a last - \a first) applications of the
    ///         predicate \a op.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter1    The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam FwdIter2    The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam T           The type of the value to be used as initial (and
    ///                     intermediate) values (deduced).
    /// \tparam Op          The type of the binary function object used for
    ///                     the reduction operation.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param init         The initial value for the generalized sum.
    /// \param op           Specifies the function (or function object) which
    ///                     will be invoked for each of the values of the input
    ///                     sequence. This is a
    ///                     binary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type1 &a, const Type1 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const&, but
    ///                     the function must not modify the objects passed to
    ///                     it.
    ///                     The types \a Type1 and \a Ret must be
    ///                     such that an object of a type as given by the input
    ///                     sequence can be implicitly converted to any
    ///                     of those types.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The reduce operations in the parallel \a inclusive_scan algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a inclusive_scan algorithm returns a
    ///           \a pika::future<FwdIter2> if
    ///           the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a FwdIter2 otherwise.
    ///           The \a inclusive_scan algorithm returns the output iterator
    ///           to the element in the destination range, one past the last
    ///           element copied.
    ///
    /// \note   GENERALIZED_NONCOMMUTATIVE_SUM(op, a1, ..., aN) is defined as:
    ///         * a1 when N is 1
    ///         * op(GENERALIZED_NONCOMMUTATIVE_SUM(op, a1, ..., aK),
    ///           GENERALIZED_NONCOMMUTATIVE_SUM(op, aM, ..., aN))
    ///           where 1 < K+1 = M <= N.
    ///
    /// The difference between \a exclusive_scan and \a inclusive_scan is that
    /// \a inclusive_scan includes the ith input element in the ith sum. If
    /// \a op is not mathematically associative, the behavior of
    /// \a inclusive_scan may be non-deterministic.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
        typename T, typename Op>
    typename pika::parallel::detail::algorithm_result<ExPolicy, FwdIter2>::type
    inclusive_scan(ExPolicy&& policy, FwdIter1 first, FwdIter1 last,
        FwdIter2 dest, T init, Op&& op);
    // clang-format on
}    // namespace pika

#else    // DOXYGEN

#include <pika/config.hpp>
#include <pika/concepts/concepts.hpp>
#include <pika/functional/detail/tag_fallback_invoke.hpp>
#include <pika/functional/invoke.hpp>
#include <pika/iterator_support/traits/is_iterator.hpp>
#include <pika/iterator_support/zip_iterator.hpp>
#include <pika/pack_traversal/unwrap.hpp>

#include <pika/executors/execution_policy.hpp>
#include <pika/parallel/algorithms/detail/advance_and_get_distance.hpp>
#include <pika/parallel/algorithms/detail/dispatch.hpp>
#include <pika/parallel/algorithms/detail/distance.hpp>
#include <pika/parallel/util/detail/algorithm_result.hpp>
#include <pika/parallel/util/detail/sender_util.hpp>
#include <pika/parallel/util/loop.hpp>
#include <pika/parallel/util/partitioner.hpp>
#include <pika/parallel/util/projection_identity.hpp>
#include <pika/parallel/util/result_types.hpp>
#include <pika/parallel/util/scan_partitioner.hpp>
#include <pika/parallel/util/zip_iterator.hpp>
#include <pika/type_support/unused.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

namespace pika::parallel::detail {
    ///////////////////////////////////////////////////////////////////////////
    // inclusive_scan
    /// \cond NOINTERNAL

    ///////////////////////////////////////////////////////////////////////
    // Our own version of the sequential inclusive_scan.
    template <typename InIter, typename Sent, typename OutIter, typename T,
        typename Op>
    static constexpr in_out_result<InIter, OutIter> sequential_inclusive_scan(
        InIter first, Sent last, OutIter dest, T init, Op&& op)
    {
        for (/* */; first != last; (void) ++first, ++dest)
        {
            init = PIKA_INVOKE(op, init, *first);
            *dest = init;
        }
        return in_out_result<InIter, OutIter>{first, dest};
    }

    template <typename InIter, typename Sent, typename OutIter, typename Op>
    static constexpr in_out_result<InIter, OutIter>
    sequential_inclusive_scan_noinit(
        InIter first, Sent last, OutIter dest, Op&& op)
    {
        if (first != last)
        {
            auto init = *first;
            *dest++ = init;
            return sequential_inclusive_scan(
                ++first, last, dest, PIKA_MOVE(init), PIKA_FORWARD(Op, op));
        }
        return in_out_result<InIter, OutIter>{first, dest};
    }

    template <typename InIter, typename OutIter, typename T, typename Op>
    static constexpr T sequential_inclusive_scan_n(
        InIter first, std::size_t count, OutIter dest, T init, Op&& op)
    {
        for (/* */; count-- != 0; (void) ++first, ++dest)
        {
            init = PIKA_INVOKE(op, init, *first);
            *dest = init;
        }
        return init;
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename IterPair>
    struct inclusive_scan : public algorithm<inclusive_scan<IterPair>, IterPair>
    {
        inclusive_scan()
          : inclusive_scan::algorithm("inclusive_scan")
        {
        }

        template <typename ExPolicy, typename InIter, typename Sent,
            typename OutIter, typename T, typename Op>
        static constexpr in_out_result<InIter, OutIter> sequential(ExPolicy,
            InIter first, Sent last, OutIter dest, T const& init, Op&& op)
        {
            return sequential_inclusive_scan(
                first, last, dest, init, PIKA_FORWARD(Op, op));
        }

        template <typename ExPolicy, typename InIter, typename Sent,
            typename OutIter, typename Op>
        static constexpr in_out_result<InIter, OutIter>
        sequential(ExPolicy, InIter first, Sent last, OutIter dest, Op&& op)
        {
            return sequential_inclusive_scan_noinit(
                first, last, dest, PIKA_FORWARD(Op, op));
        }

        template <typename ExPolicy, typename FwdIter1, typename Sent,
            typename FwdIter2, typename T, typename Op>
        static typename algorithm_result<ExPolicy,
            in_out_result<FwdIter1, FwdIter2>>::type
        parallel(ExPolicy&& policy, FwdIter1 first, Sent last, FwdIter2 dest,
            T init, Op&& op)
        {
            using result =
                algorithm_result<ExPolicy, in_out_result<FwdIter1, FwdIter2>>;
            using zip_iterator = pika::util::zip_iterator<FwdIter1, FwdIter2>;
            using difference_type =
                typename std::iterator_traits<FwdIter1>::difference_type;

            if (first == last)
                return result::get(
                    in_out_result<FwdIter1, FwdIter2>{first, dest});

            FwdIter1 last_iter = first;
            difference_type count =
                detail::advance_and_get_distance(last_iter, last);

            FwdIter2 final_dest = dest;
            std::advance(final_dest, count);

            // The overall scan algorithm is performed by executing 3
            // steps. The first calculates the scan results for each
            // partition. The second accumulates the result from left to
            // right to be used by the third step--which operates on the
            // same partitions the first step operated on.

            using pika::util::make_zip_iterator;
            using std::get;

            auto f3 = [op](zip_iterator part_begin, std::size_t part_size,
                          T val) mutable -> void {
                FwdIter2 dst = get<1>(part_begin.get_iterator_tuple());

                // MSVC 2015 fails if op is captured by reference
                loop_n<std::decay_t<ExPolicy>>(
                    dst, part_size, [=, &val](FwdIter2 it) mutable -> void {
                        *it = PIKA_INVOKE(op, val, *it);
                    });
            };

            return scan_partitioner<ExPolicy, in_out_result<FwdIter1, FwdIter2>,
                T>::
                call(
                    PIKA_FORWARD(ExPolicy, policy),
                    make_zip_iterator(first, dest), count, init,
                    // step 1 performs first part of scan algorithm
                    [op, last](
                        zip_iterator part_begin, std::size_t part_size) -> T {
                        T part_init = get<0>(*part_begin);
                        get<1>(*part_begin++) = part_init;

                        auto iters = part_begin.get_iterator_tuple();
                        if (get<0>(iters) != last)
                        {
                            return sequential_inclusive_scan_n(get<0>(iters),
                                part_size - 1, get<1>(iters), part_init, op);
                        }
                        return part_init;
                    },
                    // step 2 propagates the partition results from left
                    // to right
                    op,
                    // step 3 runs final accumulation on each partition
                    PIKA_MOVE(f3),
                    // step 4 use this return value
                    [last_iter, final_dest](std::vector<T>&&,
                        std::vector<pika::future<void>>&& data) {
                        // make sure iterators embedded in function object that is
                        // attached to futures are invalidated
                        data.clear();
                        return in_out_result<FwdIter1, FwdIter2>{
                            last_iter, final_dest};
                    });
        }

        template <typename ExPolicy, typename FwdIter1, typename Sent,
            typename FwdIter2, typename Op>
        static typename algorithm_result<ExPolicy,
            in_out_result<FwdIter1, FwdIter2>>::type
        parallel(ExPolicy&& policy, FwdIter1 first, Sent last, FwdIter2 dest,
            Op&& op)
        {
            if (first != last)
            {
                auto init = *first;
                *dest++ = init;
                return parallel(PIKA_FORWARD(ExPolicy, policy), ++first, last,
                    dest, PIKA_MOVE(init), PIKA_FORWARD(Op, op));
            }

            using result =
                algorithm_result<ExPolicy, in_out_result<FwdIter1, FwdIter2>>;
            return result::get(in_out_result<FwdIter1, FwdIter2>{first, dest});
        }
    };
    /// \endcond
}    // namespace pika::parallel::detail

namespace pika {
    ///////////////////////////////////////////////////////////////////////////
    // CPO for pika::inclusive_scan
    inline constexpr struct inclusive_scan_t final
      : pika::detail::tag_parallel_algorithm<inclusive_scan_t>
    {
        // clang-format off
        template <typename InIter, typename OutIter,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator_v<InIter> &&
                pika::traits::is_iterator_v<OutIter>
            )>
        // clang-format on
        friend OutIter tag_fallback_invoke(
            pika::inclusive_scan_t, InIter first, InIter last, OutIter dest)
        {
            static_assert((pika::traits::is_input_iterator_v<InIter>),
                "Requires at least input iterator.");
            static_assert((pika::traits::is_output_iterator_v<OutIter>),
                "Requires at least output iterator.");

            using result_type =
                parallel::detail::in_out_result<InIter, OutIter>;
            using value_type =
                typename std::iterator_traits<InIter>::value_type;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    pika::execution::seq, first, last, dest,
                    std::plus<value_type>()));
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator_v<FwdIter1> &&
                pika::traits::is_iterator_v<FwdIter2>
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter2>::type
        tag_fallback_invoke(pika::inclusive_scan_t, ExPolicy&& policy,
            FwdIter1 first, FwdIter1 last, FwdIter2 dest)
        {
            static_assert(pika::traits::is_forward_iterator_v<FwdIter1>,
                "Requires at least forward iterator.");
            static_assert(pika::traits::is_forward_iterator_v<FwdIter2>,
                "Requires at least forward iterator.");

            using value_type =
                typename std::iterator_traits<FwdIter1>::value_type;
            using result_type =
                parallel::detail::in_out_result<FwdIter1, FwdIter2>;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    PIKA_FORWARD(ExPolicy, policy), first, last, dest,
                    std::plus<value_type>()));
        }

        // clang-format off
        template <typename InIter, typename OutIter, typename Op,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator_v<InIter> &&
                pika::traits::is_iterator_v<OutIter> &&
                std::is_invocable_v<Op,
                    typename std::iterator_traits<InIter>::value_type,
                    typename std::iterator_traits<InIter>::value_type
                >
            )>
        // clang-format on
        friend OutIter tag_fallback_invoke(pika::inclusive_scan_t, InIter first,
            InIter last, OutIter dest, Op&& op)
        {
            static_assert((pika::traits::is_input_iterator_v<InIter>),
                "Requires at least input iterator.");
            static_assert((pika::traits::is_output_iterator_v<OutIter>),
                "Requires at least output iterator.");

            using result_type =
                parallel::detail::in_out_result<InIter, OutIter>;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    pika::execution::seq, first, last, dest,
                    PIKA_FORWARD(Op, op)));
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename Op,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator_v<FwdIter1> &&
                pika::traits::is_iterator_v<FwdIter2> &&
                std::is_invocable_v<Op,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter1>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter2>::type
        tag_fallback_invoke(pika::inclusive_scan_t, ExPolicy&& policy,
            FwdIter1 first, FwdIter1 last, FwdIter2 dest, Op&& op)
        {
            static_assert(pika::traits::is_forward_iterator_v<FwdIter1>,
                "Requires at least forward iterator.");
            static_assert(pika::traits::is_forward_iterator_v<FwdIter2>,
                "Requires at least forward iterator.");

            using result_type =
                parallel::detail::in_out_result<FwdIter1, FwdIter2>;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    PIKA_FORWARD(ExPolicy, policy), first, last, dest,
                    PIKA_FORWARD(Op, op)));
        }

        // clang-format off
        template <typename InIter, typename OutIter, typename Op,
            typename T = typename std::iterator_traits<InIter>::value_type,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator_v<InIter> &&
                pika::traits::is_iterator_v<OutIter> &&
                std::is_invocable_v<Op,
                    typename std::iterator_traits<InIter>::value_type,
                    typename std::iterator_traits<InIter>::value_type
                >
            )>
        // clang-format on
        friend OutIter tag_fallback_invoke(pika::inclusive_scan_t, InIter first,
            InIter last, OutIter dest, Op&& op, T init)
        {
            static_assert((pika::traits::is_input_iterator_v<InIter>),
                "Requires at least input iterator.");
            static_assert((pika::traits::is_output_iterator_v<OutIter>),
                "Requires at least output iterator.");

            using result_type =
                parallel::detail::in_out_result<InIter, OutIter>;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    pika::execution::seq, first, last, dest, PIKA_MOVE(init),
                    PIKA_FORWARD(Op, op)));
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename Op,
            typename T = typename std::iterator_traits<FwdIter1>::value_type,
            PIKA_CONCEPT_REQUIRES_(
                pika::is_execution_policy<ExPolicy>::value &&
                pika::traits::is_iterator_v<FwdIter1> &&
                pika::traits::is_iterator_v<FwdIter2> &&
                std::is_invocable_v<Op,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter1>::value_type
                >
            )>
        // clang-format on
        friend typename pika::parallel::detail::algorithm_result<ExPolicy,
            FwdIter2>::type
        tag_fallback_invoke(pika::inclusive_scan_t, ExPolicy&& policy,
            FwdIter1 first, FwdIter1 last, FwdIter2 dest, Op&& op, T init)
        {
            static_assert(pika::traits::is_forward_iterator_v<FwdIter1>,
                "Requires at least forward iterator.");
            static_assert(pika::traits::is_forward_iterator_v<FwdIter2>,
                "Requires at least forward iterator.");

            using result_type =
                parallel::detail::in_out_result<FwdIter1, FwdIter2>;

            return pika::parallel::detail::get_second_element(
                parallel::detail::inclusive_scan<result_type>().call(
                    PIKA_FORWARD(ExPolicy, policy), first, last, dest,
                    PIKA_MOVE(init), PIKA_FORWARD(Op, op)));
        }

    } inclusive_scan{};
}    // namespace pika

#endif    // DOXYGEN
