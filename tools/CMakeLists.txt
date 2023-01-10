# Copyright (c) 2014-2019 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(subdirs)

if(PIKA_ALGORITHMS_WITH_TESTS_BENCHMARKS)
  list(APPEND subdirs perftests_ci)
endif()

foreach(subdir ${subdirs})
  add_subdirectory(${subdir})
endforeach()
