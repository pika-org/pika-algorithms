# Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
# Copyright (c) 2007-2017 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(tests
    count_3646
    for_each_annotated_function
    for_loop_2281
    minimal_findend
    reduce_3641
    scan_different_inits
    scan_non_commutative
    scan_shortlength
    search_zerolength
    set_operations_3442
    stable_merge_2964
    static_chunker_2282
    transform_inclusive_scan_4786
    transform_inclusive_scan_4787
    ranges_facilities
)

if(PIKA_ALGORITHMS_WITH_STD_EXPERIMENTAL_SIMD)
  list(APPEND tests for_each_datapar)
endif()

foreach(test ${tests})
  set(sources ${test}.cpp)

  set(${test}_PARAMETERS THREADS 4)

  source_group("Source Files" FILES ${sources})

  pika_algorithms_add_executable(
    ${test}_test INTERNAL_FLAGS
    SOURCES ${sources}
    EXCLUDE_FROM_ALL ${${test}_FLAGS}
    FOLDER "Tests/Regressions/"
  )

  target_link_libraries(${test}_test PRIVATE pika_algorithms_test_utilities)

  pika_algorithms_add_regression_test("" ${test} ${${test}_PARAMETERS})
endforeach()
