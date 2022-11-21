# Copyright (c) 2007-2019 Hartmut Kaiser
# Copyright (c) 2011      Bryce Adelstein-Lelbach
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(example_programs
    disable_thread_stealing_executor hello_world matrix_multiplication
    potpourri vector_counting_dotproduct vector_zip_dotproduct
)

set(vector_counting_dotproduct_PARAMETERS THREADS 4)
set(vector_zip_dotproduct_PARAMETERS THREADS 4)

# the following example fails compiling on someversions of MSVC
if(PIKA_ALGORITHMS_WITH_TUPLE_RVALUE_SWAP AND (NOT MSVC))
  list(APPEND example_programs sort_by_key_demo)
endif()

foreach(example_program ${example_programs})
  set(sources ${example_program}.cpp)

  source_group("Source Files" FILES ${sources})

  pika_algorithms_add_executable(
    ${example_program} INTERNAL_FLAGS
    SOURCES ${sources} ${${example_program}_FLAGS}
    FOLDER "Examples/Quickstart"
  )

  target_link_libraries(
    ${example_program} PRIVATE ${${example_program}_LIBRARIES}
  )
  pika_algorithms_add_example_target_dependencies(
    "quickstart" ${example_program}
  )

  if(PIKA_ALGORITHMS_WITH_TESTS AND PIKA_ALGORITHMS_WITH_TESTS_EXAMPLES)
    pika_algorithms_add_example_test(
      "quickstart" ${example_program} ${${example_program}_PARAMETERS}
    )
  endif()

endforeach()
