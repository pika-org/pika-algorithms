# Copyright (c) 2014-2015 Hartmut Kaiser
# Copyright (c) 2011 Bryce Lelbach
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(example_programs transpose_serial transpose_serial_block transpose_smp
                     transpose_smp_block
)

set(transpose_smp_PARAMETERS THREADS 4)
set(transpose_smp_block_PARAMETERS THREADS 4)

foreach(example_program ${example_programs})

  set(sources ${example_program}.cpp)

  source_group("Source Files" FILES ${sources})

  pika_algorithms_add_executable(
    ${example_program} INTERNAL_FLAGS
    SOURCES ${sources} ${${example_program}_FLAGS}
    FOLDER "Examples/Transpose"
  )

  pika_algorithms_add_example_target_dependencies(
    "transpose" ${example_program}
  )

  if(PIKA_ALGORITHMS_WITH_TESTS AND PIKA_ALGORITHMS_WITH_TESTS_EXAMPLES)
    pika_algorithms_add_example_test(
      "transpose" ${example_program} ${${example_program}_PARAMETERS}
    )
  endif()
endforeach()
