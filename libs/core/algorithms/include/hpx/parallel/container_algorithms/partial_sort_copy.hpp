//  Copyright (c) 2020 Hartmut Kaiser
//  Copyright (c) 2021 Akhil J Nair
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/container_algorithms/partial_sort_copy.hpp

#pragma once

#if defined(DOXYGEN)

namespace hpx { namespace ranges {
    // clang-format off

    ///////////////////////////////////////////////////////////////////////////
    /// Sorts the elements in the range [first, last) in ascending order. The
    /// relative order of equal elements is preserved. The function
    /// uses the given comparison function object comp (defaults to using
    /// operator<()).
    ///
    /// \note   Complexity: O(Nlog(N)), where N = std::distance(first, last)
    ///                     comparisons.
    ///
    /// A sequence is sorted with respect to a comparator \a comp and a
    /// projection \a proj if for every iterator i pointing to the sequence and
    /// every non-negative integer n such that i + n is a valid iterator
    /// pointing to an element of the sequence, and
    /// INVOKE(comp, INVOKE(proj, *(i + n)), INVOKE(proj, *i)) == false.
    ///
    /// \tparam RandomIt    The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     random iterator.
    /// \tparam Sent        The type of the source sentinel (deduced). This
    ///                     sentinel type must be a sentinel for RandomIt.
    /// \tparam Comp        The type of the function/function object to use
    ///                     (deduced).
    /// \tparam Proj        The type of an optional projection function. This
    ///                     defaults to \a util::projection_identity
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to sentinel value denoting the end of the
    ///                     sequence of elements the algorithm will be applied.
    /// \param comp         comp is a callable object. The return value of the
    ///                     INVOKE operation applied to an object of type Comp,
    ///                     when contextually converted to bool, yields true if
    ///                     the first argument of the call is less than the
    ///                     second, and false otherwise. It is assumed that comp
    ///                     will not apply any non-constant function through the
    ///                     dereferenced iterator.
    /// \param proj         Specifies the function (or function object) which
    ///                     will be invoked for each pair of elements as a
    ///                     projection operation before the actual predicate
    ///                     \a comp is invoked.
    ///
    /// \a comp has to induce a strict weak ordering on the values.
    ///
    /// The assignments in the parallel \a partial_sort_copy algorithm invoked without
    /// an execution policy object execute in sequential order in the
    /// calling thread.
    ///
    /// \returns  The \a partial_sort_copy algorithm returns \a RandomIt.
    ///           The algorithm returns an iterator pointing to the first
    ///           element after the last element in the input sequence.
    ///
    template <typename RandomIt, typename Sent, typename Comp, typename Proj>
    RandomIt partial_sort_copy(RandomIt first, Sent last, Comp&& comp, Proj&& proj);

    ///////////////////////////////////////////////////////////////////////////
    /// Sorts the elements in the range [first, last) in ascending order. The
    /// relative order of equal elements is preserved. The function
    /// uses the given comparison function object comp (defaults to using
    /// operator<()).
    ///
    /// \note   Complexity: O(Nlog(N)), where N = std::distance(first, last)
    ///                     comparisons.
    ///
    /// A sequence is sorted with respect to a comparator \a comp and a
    /// projection \a proj if for every iterator i pointing to the sequence and
    /// every non-negative integer n such that i + n is a valid iterator
    /// pointing to an element of the sequence, and
    /// INVOKE(comp, INVOKE(proj, *(i + n)), INVOKE(proj, *i)) == false.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam RandomIt    The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     random iterator.
    /// \tparam Sent        The type of the source sentinel (deduced). This
    ///                     sentinel type must be a sentinel for RandomIt.
    /// \tparam Comp        The type of the function/function object to use
    ///                     (deduced).
    /// \tparam Proj        The type of an optional projection function. This
    ///                     defaults to \a util::projection_identity
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to sentinel value denoting the end of the
    ///                     sequence of elements the algorithm will be applied.
    /// \param comp         comp is a callable object. The return value of the
    ///                     INVOKE operation applied to an object of type Comp,
    ///                     when contextually converted to bool, yields true if
    ///                     the first argument of the call is less than the
    ///                     second, and false otherwise. It is assumed that comp
    ///                     will not apply any non-constant function through the
    ///                     dereferenced iterator.
    /// \param proj         Specifies the function (or function object) which
    ///                     will be invoked for each pair of elements as a
    ///                     projection operation before the actual predicate
    ///                     \a comp is invoked.
    ///
    /// \a comp has to induce a strict weak ordering on the values.
    ///
    /// The application of function objects in parallel algorithm
    /// invoked with an execution policy object of type
    /// \a sequenced_policy execute in sequential order in the
    /// calling thread.
    ///
    /// The application of function objects in parallel algorithm
    /// invoked with an execution policy object of type
    /// \a parallel_policy or \a parallel_task_policy are
    /// permitted to execute in an unordered fashion in unspecified
    /// threads, and indeterminately sequenced within each thread.
    ///
    /// \returns  The \a partial_sort_copy algorithm returns a
    ///           \a hpx::future<RandomIt> if the execution policy is of
    ///           type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and returns \a RandomIt
    ///           otherwise.
    ///           The algorithm returns an iterator pointing to the first
    ///           element after the last element in the input sequence.
    ///
    template <typename ExPolicy, typename RandomIt, typename Sent,
        typename Comp, typename Proj>
    typename parallel::util::detail::algorithm_result<ExPolicy,
        RandomIt>::type
    partial_sort_copy(ExPolicy&& policy, RandomIt first, Sent last, Comp&& comp,
        Proj&& proj);

    ///////////////////////////////////////////////////////////////////////////
    /// Sorts the elements in the range [first, last) in ascending order. The
    /// relative order of equal elements is preserved. The function
    /// uses the given comparison function object comp (defaults to using
    /// operator<()).
    ///
    /// \note   Complexity: O(Nlog(N)), where N = std::distance(first, last)
    ///                     comparisons.
    ///
    /// A sequence is sorted with respect to a comparator \a comp and a
    /// projection \a proj if for every iterator i pointing to the sequence and
    /// every non-negative integer n such that i + n is a valid iterator
    /// pointing to an element of the sequence, and
    /// INVOKE(comp, INVOKE(proj, *(i + n)), INVOKE(proj, *i)) == false.
    ///
    /// \tparam Rng         The type of the source range used (deduced).
    ///                     The iterators extracted from this range type must
    ///                     meet the requirements of an input iterator.
    /// \tparam Comp        The type of the function/function object to use
    ///                     (deduced).
    /// \tparam Proj        The type of an optional projection function. This
    ///                     defaults to \a util::projection_identity
    ///
    /// \param rng          Refers to the sequence of elements the algorithm
    ///                     will be applied to.
    /// \param comp         comp is a callable object. The return value of the
    ///                     INVOKE operation applied to an object of type Comp,
    ///                     when contextually converted to bool, yields true if
    ///                     the first argument of the call is less than the
    ///                     second, and false otherwise. It is assumed that comp
    ///                     will not apply any non-constant function through the
    ///                     dereferenced iterator.
    /// \param proj         Specifies the function (or function object) which
    ///                     will be invoked for each pair of elements as a
    ///                     projection operation before the actual predicate
    ///                     \a comp is invoked.
    ///
    /// \a comp has to induce a strict weak ordering on the values.
    ///
    /// The assignments in the parallel \a partial_sort_copy algorithm invoked without
    /// an execution policy object execute in sequential order in the
    /// calling thread.
    ///
    /// \returns  The \a partial_sort_copy algorithm returns \a
    ///           typename hpx::traits::range_iterator<Rng>::type.
    ///           It returns \a last.
    template <typename Rng, typename Comp, typename Proj>
    typename hpx::traits::range_iterator<Rng>::type
    partial_sort_copy(Rng&& rng, Compare&& comp, Proj&& proj);

    ///////////////////////////////////////////////////////////////////////////
    /// Sorts the elements in the range [first, last) in ascending order. The
    /// relative order of equal elements is preserved. The function
    /// uses the given comparison function object comp (defaults to using
    /// operator<()).
    ///
    /// \note   Complexity: O(Nlog(N)), where N = std::distance(first, last)
    ///                     comparisons.
    ///
    /// A sequence is sorted with respect to a comparator \a comp and a
    /// projection \a proj if for every iterator i pointing to the sequence and
    /// every non-negative integer n such that i + n is a valid iterator
    /// pointing to an element of the sequence, and
    /// INVOKE(comp, INVOKE(proj, *(i + n)), INVOKE(proj, *i)) == false.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it applies user-provided function objects.
    /// \tparam Rng         The type of the source range used (deduced).
    ///                     The iterators extracted from this range type must
    ///                     meet the requirements of an input iterator.
    /// \tparam Comp        The type of the function/function object to use
    ///                     (deduced).
    /// \tparam Proj        The type of an optional projection function. This
    ///                     defaults to \a util::projection_identity
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param rng          Refers to the sequence of elements the algorithm
    ///                     will be applied to.
    /// \param comp         comp is a callable object. The return value of the
    ///                     INVOKE operation applied to an object of type Comp,
    ///                     when contextually converted to bool, yields true if
    ///                     the first argument of the call is less than the
    ///                     second, and false otherwise. It is assumed that comp
    ///                     will not apply any non-constant function through the
    ///                     dereferenced iterator.
    /// \param proj         Specifies the function (or function object) which
    ///                     will be invoked for each pair of elements as a
    ///                     projection operation before the actual predicate
    ///                     \a comp is invoked.
    ///
    /// \a comp has to induce a strict weak ordering on the values.
    ///
    /// The application of function objects in parallel algorithm
    /// invoked with an execution policy object of type
    /// \a sequenced_policy execute in sequential order in the
    /// calling thread.
    ///
    /// The application of function objects in parallel algorithm
    /// invoked with an execution policy object of type
    /// \a parallel_policy or \a parallel_task_policy are
    /// permitted to execute in an unordered fashion in unspecified
    /// threads, and indeterminately sequenced within each thread.
    ///
    /// \returns  The \a partial_sort_copy algorithm returns a
    ///           \a hpx::future<typename hpx::traits::range_iterator<Rng>
    ///           ::type> if the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and returns \a
    ///           typename hpx::traits::range_iterator<Rng>::type
    ///           otherwise.
    ///           It returns \a last.
    ///
    template <typename ExPolicy, typename Rng, typename Pred, typename Proj>
    typename util::detail::algorithm_result<ExPolicy,
        typename hpx::traits::range_iterator<Rng>::type>::type
    partial_sort_copy(ExPolicy&& policy, Rng&& rng, Comp&& comp, Proj&&);

    // clang-format on
}}    // namespace hpx::ranges

#else

#include <hpx/config.hpp>
#include <hpx/concepts/concepts.hpp>
#include <hpx/iterator_support/range.hpp>
#include <hpx/iterator_support/traits/is_range.hpp>

#include <hpx/algorithms/traits/projected_range.hpp>
#include <hpx/parallel/algorithms/partial_sort_copy.hpp>
#include <hpx/parallel/util/projection_identity.hpp>
#include <hpx/parallel/util/result_types.hpp>
#include <hpx/parallel/util/detail/sender_util.hpp>

#include <type_traits>
#include <utility>

namespace hpx { namespace ranges {
    template <typename I, typename O>
    using partial_sort_copy_result = parallel::util::in_out_result<I, O>;

    ///////////////////////////////////////////////////////////////////////////
    // DPO for hpx::ranges::partial_sort_copy
    HPX_INLINE_CONSTEXPR_VARIABLE struct partial_sort_copy_t final
      : hpx::detail::tag_parallel_algorithm<partial_sort_copy_t>
    {
    private:
        // clang-format off
        template <typename InIter, typename Sent1, typename RandIter,
            typename Sent2, typename Comp = ranges::less,
            typename Proj1 = parallel::util::projection_identity,
            typename Proj2 = parallel::util::projection_identity,
            HPX_CONCEPT_REQUIRES_(
                hpx::traits::is_iterator_v<InIter> &&
                hpx::traits::is_sentinel_for_v<Sent1, InIter> &&
                hpx::traits::is_iterator_v<RandIter> &&
                hpx::traits::is_sentinel_for_v<Sent2, RandIter> &&
                parallel::traits::is_projected_v<Proj1, InIter> &&
                parallel::traits::is_projected_v<Proj2, RandIter> &&
                parallel::traits::is_indirect_callable_v<
                    hpx::execution::sequenced_policy, Comp,
                    parallel::traits::projected<Proj2, RandIter>,
                    parallel::traits::projected<Proj2, RandIter>
                >
            )>
        // clang-format on
        friend partial_sort_copy_result<InIter, RandIter> tag_fallback_dispatch(
            hpx::ranges::partial_sort_copy_t, InIter first, Sent1 last,
            RandIter r_first, Sent2 r_last, Comp&& comp = Comp(),
            Proj1&& proj1 = Proj1(), Proj2&& proj2 = Proj2())
        {
            static_assert(hpx::traits::is_input_iterator_v<InIter>,
                "Requires an input iterator.");

            static_assert(hpx::traits::is_random_access_iterator_v<RandIter>,
                "Requires a random access iterator.");

            using result_type = partial_sort_copy_result<InIter, RandIter>;

            return hpx::parallel::v1::detail::partial_sort_copy<result_type>()
                .call(hpx::execution::seq, first, last, r_first, r_last,
                    std::forward<Comp>(comp), std::forward<Proj1>(proj1),
                    std::forward<Proj2>(proj2));
        }

        // clang-format off
        template <typename ExPolicy, typename FwdIter, typename Sent1,
            typename RandIter, typename Sent2,
            typename Comp = ranges::less,
            typename Proj1 = parallel::util::projection_identity,
            typename Proj2 = parallel::util::projection_identity,
            HPX_CONCEPT_REQUIRES_(
                hpx::is_execution_policy<ExPolicy>::value &&
                hpx::traits::is_iterator_v<FwdIter> &&
                hpx::traits::is_sentinel_for_v<Sent1, FwdIter> &&
                hpx::traits::is_iterator_v<RandIter> &&
                hpx::traits::is_sentinel_for_v<Sent2, RandIter> &&
                parallel::traits::is_projected_v<Proj1, FwdIter> &&
                parallel::traits::is_projected_v<Proj2, RandIter> &&
                parallel::traits::is_indirect_callable_v<
                    ExPolicy, Comp,
                    parallel::traits::projected<Proj2, RandIter>,
                    parallel::traits::projected<Proj2, RandIter>
                >
            )>
        // clang-format on
        friend typename parallel::util::detail::algorithm_result_t<ExPolicy,
            partial_sort_copy_result<FwdIter, RandIter>>
        tag_fallback_dispatch(hpx::ranges::partial_sort_copy_t,
            ExPolicy&& policy, FwdIter first, Sent1 last, RandIter r_first,
            Sent2 r_last, Comp&& comp = Comp(), Proj1&& proj1 = Proj1(),
            Proj2&& proj2 = Proj2())
        {
            static_assert(hpx::traits::is_forward_iterator_v<FwdIter>,
                "Requires a forward iterator.");

            static_assert(hpx::traits::is_random_access_iterator_v<RandIter>,
                "Requires a random access iterator.");

            using result_type = partial_sort_copy_result<FwdIter, RandIter>;

            return hpx::parallel::v1::detail::partial_sort_copy<result_type>()
                .call(std::forward<ExPolicy>(policy), first, last, r_first,
                    r_last, std::forward<Comp>(comp), std::forward<Proj1>(proj),
                    std::forward<Proj2>(proj2));
        }

        // clang-format off
        template <typename Rng1, typename Rng2,
            typename Compare = ranges::less,
            typename Proj1 = parallel::util::projection_identity,
            typename Proj2 = parallel::util::projection_identity,
            HPX_CONCEPT_REQUIRES_(
                hpx::traits::is_range_v<Rng1> &&
                hpx::traits::is_range_v<Rng2> &&
                parallel::traits::is_projected_range_v<Proj1, Rng1> &&
                parallel::traits::is_projected_range_v<Proj2, Rng2> &&
                parallel::traits::is_indirect_callable_v<
                    hpx::execution::sequenced_policy, Compare,
                    parallel::traits::projected_range<Proj1, Rng1>,
                    parallel::traits::projected_range<Proj2, Rng2>
                >
            )>
        // clang-format on
        friend partial_sort_copy_result<hpx::traits::range_iterator_t<Rng1>,
            hpx::traits::range_iterator_t<Rng2>>
        tag_fallback_dispatch(hpx::ranges::partial_sort_copy_t, Rng1&& rng1,
            Rng2&& rng2, Compare&& comp = Compare(), Proj1&& proj1 = Proj1(),
            Proj2&& proj2 = Proj2())
        {
            using iterator_type1 = hpx::traits::range_iterator_t<Rng1>;
            using iterator_type2 = hpx::traits::range_iterator_t<Rng2>;
            using result_type =
                partial_sort_copy_result<iterator_type1, iterator_type2>;

            static_assert(hpx::traits::is_forward_iterator_v<iterator_type1>,
                "Requires a forward iterator.");

            static_assert(
                hpx::traits::is_random_access_iterator_v<iterator_type2>,
                "Requires a random access iterator.");

            return hpx::parallel::v1::detail::partial_sort_copy<result_type>()
                .call(hpx::execution::seq, hpx::util::begin(rng1),
                    hpx::util::end(rng1), hpx::util::begin(rng2),
                    hpx::util::end(rng2), std::forward<Compare>(comp),
                    std::forward<Proj1>(proj1), std::forward<Proj2>(proj2));
        }

        // clang-format off
        template <typename ExPolicy, typename Rng1, typename Rng2,
            typename Compare = ranges::less,
            typename Proj1 = parallel::util::projection_identity,
            typename Proj2 = parallel::util::projection_identity,
            HPX_CONCEPT_REQUIRES_(
                hpx::is_execution_policy_v<ExPolicy> &&
                hpx::traits::is_range_v<Rng1> &&
                hpx::traits::is_range_v<Rng2> &&
                parallel::traits::is_projected_range_v<Proj1, Rng1> &&
                parallel::traits::is_projected_range_v<Proj2, Rng2> &&
                parallel::traits::is_indirect_callable_v<
                    ExPolicy, Compare,
                    parallel::traits::projected_range<Proj1, Rng1>,
                    parallel::traits::projected_range<Proj2, Rng2>
                >
            )>
        // clang-format on
        friend parallel::util::detail::algorithm_result_t<ExPolicy,
            partial_sort_copy_result<hpx::traits::range_iterator_t<Rng1>,
                hpx::traits::range_iterator_t<Rng2>>>
        tag_fallback_dispatch(hpx::ranges::partial_sort_copy_t,
            ExPolicy&& policy, Rng1&& rng1, Rng2&& rng2,
            Compare&& comp = Compare(), Proj1&& proj1 = Proj1(),
            Proj2&& proj2 = Proj2())
        {
            using iterator_type1 = hpx::traits::range_iterator_t<Rng1>;
            using iterator_type2 = hpx::traits::range_iterator_t<Rng2>;
            using result_type =
                partial_sort_copy_result<iterator_type1, iterator_type2>;

            static_assert(hpx::traits::is_forward_iterator_v<iterator_type1>,
                "Requires a forward iterator.");

            static_assert(
                hpx::traits::is_random_access_iterator_v<iterator_type2>,
                "Requires a random access iterator.");

            return hpx::parallel::v1::detail::partial_sort_copy<result_type>()
                .call(std::forward<ExPolicy>(policy), hpx::util::begin(rng1),
                    hpx::util::end(rng1), hpx::util::begin(rng2),
                    hpx::util::end(rng2), std::forward<Compare>(comp),
                    std::forward<Proj1>(proj1), std::forward<Proj2>(proj2));
        }
    } partial_sort_copy{};
}}    // namespace hpx::ranges

#endif