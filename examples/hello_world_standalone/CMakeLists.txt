# Copyright (c) 2014-2016 Thomas Heller
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.18)

project(hello_world CXX)

if(EXISTS "${pika-algorithms_DIR}")
  find_package(pika REQUIRED)
  find_package(pika-algorithms REQUIRED)

  add_executable(hello_world hello_world.cpp)
  target_include_directories(hello_world PRIVATE ${test_SOURCE_DIR})
  target_link_libraries(
    hello_world PRIVATE pika::pika pika-algorithms::pika_algorithms
  )

  if(MSVC)
    # Only for the purposes of testing we output the executable and libraries to
    # the output directory of pika-algorithms
    set_target_properties(
      hello_world PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                             ${PIKA_ALGORITHMS_OUTPUT_DIRECTORY}
    )
  endif()

  enable_testing()
  add_test(hello_world_test hello_world)
else()
  message(
    WARNING
      "Skipping build test because pika-algorithms_DIR=${pika-algorithms_DIR} does not exist. This \
      last test requires pika to be installed.  Did you forget to run the \
      install rule?"
  )
endif()
