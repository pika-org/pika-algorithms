# Copyright (c) 2007-2014 Hartmut Kaiser
# Copyright (c) 2017 Taeguk Kwon
# Copyright (c) 2017 Google
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(subdirs local)

foreach(subdir ${subdirs})
  pika_algorithms_add_pseudo_target(tests.performance.${subdir})
  add_subdirectory(${subdir})
  pika_algorithms_add_pseudo_dependencies(
    tests.performance tests.performance.${subdir}
  )
endforeach()

set(benchmarks
    benchmark_inplace_merge
    benchmark_is_heap
    benchmark_is_heap_until
    benchmark_merge
    benchmark_nth_element
    benchmark_nth_element_parallel
    benchmark_partial_sort
    benchmark_partial_sort_parallel
    benchmark_partition
    benchmark_partition_copy
    benchmark_remove
    benchmark_remove_if
    benchmark_scan_algorithms
    benchmark_unique
    benchmark_unique_copy
    foreach_report
    foreach_scaling
    transform_reduce_scaling
)

foreach(benchmark ${benchmarks})
  set(sources ${benchmark}.cpp)

  source_group("Source Files" FILES ${sources})

  pika_algorithms_add_executable(
    ${benchmark}_test INTERNAL_FLAGS
    SOURCES ${sources}
    EXCLUDE_FROM_ALL ${${benchmark}_FLAGS}
    FOLDER "Benchmarks"
  )

  pika_algorithms_add_performance_test(
    "" ${benchmark} ${${benchmark}_PARAMETERS}
  )
endforeach()
