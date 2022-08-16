//  Copyright (c) 2007-2020 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/algorithms/includes.hpp

#pragma once

#if defined(DOXYGEN)
namespace pika {
    // clang-format off

    /// Returns true if every element from the sorted range [first2, last2) is
    /// found within the sorted range [first1, last1). Also returns true if
    /// [first2, last2) is empty. The version expects both ranges to be sorted
    /// with the user supplied binary predicate \a f.
    ///
    /// \note   At most 2*(N1+N2-1) comparisons, where
    ///         N1 = std::distance(first1, last1) and
    ///         N2 = std::distance(first2, last2).
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
    ///                     overload of \a includes requires \a Pred to meet the
    ///                     requirements of \a CopyConstructible. This defaults
    ///                     to std::less<>
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first1       Refers to the beginning of the sequence of elements
    ///                     of the first range the algorithm will be applied to.
    /// \param last1        Refers to the end of the sequence of elements of
    ///                     the first range the algorithm will be applied to.
    /// \param first2       Refers to the beginning of the sequence of elements
    ///                     of the second range the algorithm will be applied to.
    /// \param last2        Refers to the end of the sequence of elements of
    ///                     the second range the algorithm will be applied to.
    /// \param op           The binary predicate which returns true if the
    ///                     elements should be treated as includes. The signature
    ///                     of the predicate function should be equivalent to
    ///                     the following:
    ///                     \code
    ///                     bool pred(const Type1 &a, const Type2 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const &, but
    ///                     the function must not modify the objects passed to
    ///                     it. The types \a Type1 and \a Type2 must be such
    ///                     that objects of types \a FwdIter1 and \a FwdIter2 can
    ///                     be dereferenced and then implicitly converted to
    ///                     \a Type1 and \a Type2 respectively
    ///
    /// The comparison operations in the parallel \a includes algorithm invoked
    /// with an execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The comparison operations in the parallel \a includes algorithm invoked
    /// with an execution policy object of type \a parallel_policy
    /// or \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a includes algorithm returns a \a pika::future<bool> if the
    ///           execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy and
    ///           returns \a bool otherwise.
    ///           The \a includes algorithm returns true every element from the
    ///           sorted range [first2, last2) is found within the sorted range
    ///           [first1, last1). Also returns true if [first2, last2) is empty.
    ///
    template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
        typename Pred = detail::less>
    typename util::detail::algorithm_result<ExPolicy, bool>::type>::type
    includes(ExPolicy&& policy, FwdIter1 first1, FwdIter1 last1,
            FwdIter2 first2, FwdIter2 last2, Pred&& op = Pred());

    // clang-format on
}    // namespace pika

#else    // DOXYGEN

#include <pika/config.hpp>
#include <pika/concepts/concepts.hpp>
#include <pika/functional/invoke.hpp>
#include <pika/iterator_support/traits/is_iterator.hpp>
#include <pika/parallel/util/detail/sender_util.hpp>

#include <pika/execution/algorithms/detail/predicates.hpp>
#include <pika/executors/execution_policy.hpp>
#include <pika/parallel/algorithms/detail/dispatch.hpp>
#include <pika/parallel/algorithms/detail/upper_lower_bound.hpp>
#include <pika/parallel/util/cancellation_token.hpp>
#include <pika/parallel/util/detail/algorithm_result.hpp>
#include <pika/parallel/util/partitioner.hpp>
#include <pika/parallel/util/projection_identity.hpp>
#include <pika/parallel/util/result_types.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace pika::parallel::detail {
    ///////////////////////////////////////////////////////////////////////////
    // includes
    template <typename Iter1, typename Sent1, typename Iter2, typename Sent2,
        typename F, typename Proj1, typename Proj2, typename CancelToken>
    bool sequential_includes(Iter1 first1, Sent1 last1, Iter2 first2,
        Sent2 last2, F&& f, Proj1&& proj1, Proj2&& proj2, CancelToken& tok)
    {
        while (first2 != last2)
        {
            if (tok.was_cancelled())
            {
                return false;
            }

            if (first1 == last1)
            {
                return false;
            }

            auto&& value1 = PIKA_INVOKE(proj1, *first1);
            auto&& value2 = PIKA_INVOKE(proj2, *first2);

            if (PIKA_INVOKE(f, value2, value1))
            {
                return false;
            }

            if (!PIKA_INVOKE(f, value1, value2))
            {
                ++first2;
            }

            ++first1;
        }
        return true;
    }

    template <typename Iter1, typename Sent1, typename Iter2, typename Sent2,
        typename F, typename Proj1, typename Proj2>
    constexpr bool sequential_includes(Iter1 first1, Sent1 last1, Iter2 first2,
        Sent2 last2, F&& f, Proj1&& proj1, Proj2&& proj2)
    {
        while (first2 != last2)
        {
            if (first1 == last1)
            {
                return false;
            }

            auto&& value1 = PIKA_INVOKE(proj1, *first1);
            auto&& value2 = PIKA_INVOKE(proj2, *first2);

            if (PIKA_INVOKE(f, value2, value1))
            {
                return false;
            }

            if (!PIKA_INVOKE(f, value1, value2))
            {
                ++first2;
            }

            ++first1;
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    struct includes : public detail::algorithm<includes, bool>
    {
        includes()
          : includes::algorithm("includes")
        {
        }

        template <typename ExPolicy, typename Iter1, typename Sent1,
            typename Iter2, typename Sent2, typename F, typename Proj1,
            typename Proj2>
        static bool sequential(ExPolicy, Iter1 first1, Sent1 last1,
            Iter2 first2, Sent2 last2, F&& f, Proj1&& proj1, Proj2&& proj2)
        {
            return sequential_includes(first1, last1, first2, last2,
                PIKA_FORWARD(F, f), PIKA_FORWARD(Proj1, proj1),
                PIKA_FORWARD(Proj2, proj2));
        }

        template <typename ExPolicy, typename Iter1, typename Sent1,
            typename Iter2, typename Sent2, typename F, typename Proj1,
            typename Proj2>
        static typename util::detail::algorithm_result<ExPolicy, bool>::type
        parallel(ExPolicy&& policy, Iter1 first1, Sent1 last1, Iter2 first2,
            Sent2 last2, F&& f, Proj1&& proj1, Proj2&& proj2)
        {
            if (first1 == last1)
            {
                return util::detail::algorithm_result<ExPolicy, bool>::get(
                    false);
            }
            if (first2 == last2)
            {
                return util::detail::algorithm_result<ExPolicy, bool>::get(
                    true);
            }

            util::cancellation_token<> tok;

            auto f1 = [first1, last1, first2, last2, tok,
                          f = PIKA_FORWARD(F, f),
                          proj1 = PIKA_FORWARD(Proj1, proj1),
                          proj2 = PIKA_FORWARD(Proj2, proj2)](Iter2 part_begin,
                          std::size_t part_count) mutable -> bool {
                Iter2 part_end = detail::next(part_begin, part_count);

                auto value = PIKA_INVOKE(proj2, *part_begin);
                if (first2 != part_begin && part_count > 1)
                {
                    part_begin = detail::upper_bound(
                        part_begin, part_end, value, f, proj2, tok);
                    if (tok.was_cancelled())
                    {
                        return false;
                    }
                    if (part_begin == part_end)
                    {
                        return true;
                    }
                    value = PIKA_INVOKE(proj2, *part_begin);
                }

                Iter1 low =
                    detail::lower_bound(first1, last1, value, f, proj1, tok);
                if (tok.was_cancelled())
                {
                    return false;
                }

                if (low == last1 ||
                    PIKA_INVOKE(f, value, PIKA_INVOKE(proj1, *low)))
                {
                    tok.cancel();
                    return false;
                }

                Iter1 high = last1;
                if (part_end != last2)
                {
                    auto&& value1 = PIKA_INVOKE(proj2, *part_end);

                    high =
                        detail::upper_bound(low, last1, value1, f, proj1, tok);
                    part_end = detail::upper_bound(
                        part_end, last2, value1, f, proj2, tok);

                    if (tok.was_cancelled())
                    {
                        return false;
                    }
                }

                if (!sequential_includes(
                        low, high, part_begin, part_end, f, proj1, proj2, tok))
                {
                    tok.cancel();
                }
                return !tok.was_cancelled();
            };

            auto f2 = [](std::vector<pika::future<bool>>&& results) {
                return std::all_of(pika::util::begin(results),
                    pika::util::end(results),
                    [](pika::future<bool>& val) { return val.get(); });
            };

            return util::partitioner<ExPolicy, bool>::call(
                PIKA_FORWARD(ExPolicy, policy), first2,
                detail::distance(first2, last2), PIKA_MOVE(f1), PIKA_MOVE(f2));
        }
    };
}    // namespace pika::parallel::detail

namespace pika {
    ///////////////////////////////////////////////////////////////////////////
    // DPO for pika::includes
    inline constexpr struct includes_t final
      : pika::detail::tag_parallel_algorithm<includes_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename Pred = pika::parallel::detail::less,
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
        friend typename pika::parallel::util::detail::algorithm_result<ExPolicy,
            bool>::type
        tag_fallback_invoke(includes_t, ExPolicy&& policy, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2, Pred&& op = Pred())
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::includes().call(
                PIKA_FORWARD(ExPolicy, policy), first1, last1, first2, last2,
                PIKA_FORWARD(Pred, op),
                pika::parallel::util::projection_identity(),
                pika::parallel::util::projection_identity());
        }

        // clang-format off
        template <typename FwdIter1, typename FwdIter2,
            typename Pred = pika::parallel::detail::less,
            PIKA_CONCEPT_REQUIRES_(
                pika::traits::is_iterator<FwdIter1>::value &&
                pika::traits::is_iterator<FwdIter2>::value &&
                pika::detail::is_invocable_v<Pred,
                    typename std::iterator_traits<FwdIter1>::value_type,
                    typename std::iterator_traits<FwdIter2>::value_type
                >
            )>
        // clang-format on
        friend bool tag_fallback_invoke(includes_t, FwdIter1 first1,
            FwdIter1 last1, FwdIter2 first2, FwdIter2 last2, Pred&& op = Pred())
        {
            static_assert((pika::traits::is_forward_iterator<FwdIter1>::value),
                "Requires at least forward iterator.");
            static_assert((pika::traits::is_forward_iterator<FwdIter2>::value),
                "Requires at least forward iterator.");

            return pika::parallel::detail::includes().call(pika::execution::seq,
                first1, last1, first2, last2, PIKA_FORWARD(Pred, op),
                pika::parallel::util::projection_identity(),
                pika::parallel::util::projection_identity());
        }
    } includes{};
}    // namespace pika

#endif    // DOXYGEN
