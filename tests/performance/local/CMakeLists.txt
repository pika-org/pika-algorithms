# Copyright (c) 2014-2017 Hartmut Kaiser
# Copyright (c) 2011 Bryce Adelstein-Lelbach
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(benchmarks stream stream_report)

if(PIKA_ALGORITHMS_WITH_STD_EXPERIMENTAL_SIMD)
  list(APPEND benchmarks transform_reduce_binary_scaling)
endif()

foreach(benchmark ${benchmarks})
  set(sources ${benchmark}.cpp ${${benchmark}_SOURCES})

  source_group("Source Files" FILES ${sources})
  if(${benchmark}_HEADERS)
    source_group("Header Files" FILES ${${benchmark}_HEADERS})
    set(${benchmark}_HEADERS HEADERS ${${benchmark}_HEADERS})
  endif()

  pika_algorithms_add_executable(
    ${benchmark}_test INTERNAL_FLAGS
    SOURCES ${sources} ${${benchmark}_FLAGS} ${${benchmark}_HEADERS}
    EXCLUDE_FROM_ALL
    FOLDER "Benchmarks"
  )

  target_include_directories(
    ${benchmark}_test SYSTEM PRIVATE ${${benchmark}_INCLUDE_DIRECTORIES}
  )
  target_link_libraries(${benchmark}_test PRIVATE ${${benchmark}_LIBRARIES})

  if(NOT "${${benchmark}_PARAMETERS}" MATCHES NO_PIKA_ALGORITHMS_MAIN)
    pika_algorithms_add_performance_test(
      "local" ${benchmark} ${${benchmark}_PARAMETERS}
    )
  endif()

endforeach()
