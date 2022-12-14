# Copyright (c) 2020-2021 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(tests chunk_size_iterator chunk_size_idx_iterator test_insertion_sort
          test_parallel_stable_sort test_sample_sort test_spin_sort
)

set(test_parallel_stable_sort_PARAMETERS THREADS 4)
set(test_sample_sort_PARAMETERS THREADS 4)

foreach(test ${tests})
  set(sources ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  set(folder_name "Tests/Unit/Detail")

  # add example executable
  pika_algorithms_add_executable(
    ${test}_test INTERNAL_FLAGS
    SOURCES ${sources} ${${test}_FLAGS}
    EXCLUDE_FROM_ALL
    FOLDER ${folder_name}
  )

  target_link_libraries(${test}_test PRIVATE pika_algorithms_test_utilities)

  pika_algorithms_add_unit_test(
    "algorithms.detail" ${test} ${${test}_PARAMETERS}
  )
endforeach()
