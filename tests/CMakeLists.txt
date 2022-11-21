# Copyright (c) 2011 Bryce Adelstein-Lelbach
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(subdirs)

add_library(pika_algorithms_test_utilities INTERFACE)
target_link_libraries(pika_algorithms_test_utilities INTERFACE pika::pika)
target_include_directories(
  pika_algorithms_test_utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(PIKA_ALGORITHMS_WITH_TESTS_BENCHMARKS)
  list(APPEND subdirs performance)
endif()

if(PIKA_ALGORITHMS_WITH_TESTS_REGRESSIONS)
  list(APPEND subdirs regressions)
endif()

if(PIKA_ALGORITHMS_WITH_TESTS_UNIT)
  list(APPEND subdirs unit)
endif()

foreach(subdir ${subdirs})
  add_subdirectory(${subdir})
endforeach()

if(PIKA_ALGORITHMS_WITH_TESTS_HEADERS)
  pika_algorithms_add_header_tests(
    algorithms
    HEADERS ${pika_algorithms_headers}
    HEADER_ROOT ${PROJECT_SOURCE_DIR}/include
    DEPENDENCIES pika_algorithms
  )
endif()
