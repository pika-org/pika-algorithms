//  Copyright (c) 2019 John Biddiscombe
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/config.hpp>
#include <pika/threading_base/print.hpp>
#include <pika/threading_base/thread_data.hpp>

#include <cstdint>
#include <thread>

// ------------------------------------------------------------
/// \cond NODETAIL
namespace pika { namespace debug {

    std::ostream& operator<<(
        std::ostream& os, threadinfo<threads::detail::thread_data*> const& d)
    {
        os << ptr(d.data) << " \""
           << ((d.data != nullptr) ? d.data->get_description() : "nullptr")
           << "\"";
        return os;
    }

    std::ostream& operator<<(
        std::ostream& os, threadinfo<threads::detail::thread_id_type*> const& d)
    {
        if (d.data == nullptr)
        {
            os << "nullptr";
        }
        else
        {
            os << threadinfo<threads::detail::thread_data*>(
                get_thread_id_data(*d.data));
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os,
        threadinfo<threads::detail::thread_id_ref_type*> const& d)
    {
        if (d.data == nullptr)
        {
            os << "nullptr";
        }
        else
        {
            os << threadinfo<threads::detail::thread_data*>(
                get_thread_id_data(*d.data));
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os,
        threadinfo<pika::threads::detail::thread_init_data> const& d)
    {
#if defined(PIKA_HAVE_THREAD_DESCRIPTION)
        os << std::left << " \"" << d.data.description.get_description()
           << "\"";
#else
        os << "??? " << /*hex<8,uintptr_t>*/ (std::uintptr_t(&d.data));
#endif
        return os;
    }

    // ------------------------------------------------------------------
    // helper class for printing thread ID, either std:: or pika::
    // ------------------------------------------------------------------
    namespace detail {

        void print_thread_info(std::ostream& os)
        {
            if (pika::threads::detail::get_self_id() ==
                pika::threads::detail::invalid_thread_id)
            {
                os << "-------------- ";
            }
            else
            {
                pika::threads::detail::thread_data* dummy =
                    pika::threads::detail::get_self_id_data();
                os << dummy << " ";
            }
            os << hex<12, std::thread::id>(std::this_thread::get_id())
#ifdef DEBUGGING_PRINT_LINUX
               << " cpu " << debug::dec<3, int>(sched_getcpu()) << " ";
#else
               << " cpu "
               << "--- ";
#endif
        }

        struct current_thread_print_helper
        {
            current_thread_print_helper()
            {
                detail::register_print_info(&detail::print_thread_info);
            }

            static current_thread_print_helper helper_;
        };

        current_thread_print_helper current_thread_print_helper::helper_{};
    }    // namespace detail
}}       // namespace pika::debug
/// \endcond
