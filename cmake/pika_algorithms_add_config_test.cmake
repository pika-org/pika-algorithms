# Copyright (c) 2011 Bryce Lelbach
# Copyright (c) 2014 Thomas Heller
# Copyright (c) 2017 Denis Blank
# Copyright (c) 2017 Google
# Copyright (c) 2017 Taeguk Kwon
# Copyright (c) 2020 Giannis Gonidelis
# Copyright (c) 2021 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(PIKA_ALGORITHMS_ADDCONFIGTEST_LOADED TRUE)

include(CheckLibraryExists)

function(pika_algorithms_add_config_test variable)
  set(options FILE EXECUTE GPU)
  set(one_value_args SOURCE ROOT CMAKECXXFEATURE CHECK_CXXSTD)
  set(multi_value_args
      CXXFLAGS
      INCLUDE_DIRECTORIES
      LINK_DIRECTORIES
      COMPILE_DEFINITIONS
      LIBRARIES
      ARGS
      DEFINITIONS
      REQUIRED
  )
  cmake_parse_arguments(
    ${variable} "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN}
  )

  if(${variable}_CHECK_CXXSTD AND ${variable}_CHECK_CXXSTD GREATER
                                  PIKA_ALGORITHMS_WITH_CXX_STANDARD
  )
    if(DEFINED ${variable})
      unset(${variable} CACHE)
      pika_algorithms_info(
        "Unsetting ${variable} because of PIKA_ALGORITHMS_WITH_CXX_STANDARD (${PIKA_ALGORITHMS_WITH_CXX_STANDARD})"
      )
    endif()
    return()
  endif()

  set(_run_msg)
  # Check CMake feature tests if the user didn't override the value of this
  # variable:
  if(NOT DEFINED ${variable} AND NOT ${variable}_GPU)
    if(${variable}_CMAKECXXFEATURE)
      # We don't have to run our own feature test if there is a corresponding
      # cmake feature test and cmake reports the feature is supported on this
      # platform.
      list(FIND CMAKE_CXX_COMPILE_FEATURES ${${variable}_CMAKECXXFEATURE} __pos)
      if(NOT ${__pos} EQUAL -1)
        set(${variable}
            TRUE
            CACHE INTERNAL ""
        )
        set(_run_msg "Success (cmake feature test)")
      endif()
    endif()
  endif()

  if(NOT DEFINED ${variable})
    file(MAKE_DIRECTORY
         "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests"
    )

    string(TOLOWER "${variable}" variable_lc)
    if(${variable}_FILE)
      if(${variable}_ROOT)
        set(test_source "${${variable}_ROOT}/share/pika/${${variable}_SOURCE}")
      else()
        set(test_source "${PROJECT_SOURCE_DIR}/${${variable}_SOURCE}")
      endif()
    else()
      if(${variable}_GPU)
        set(test_source
            "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests/${variable_lc}.cu"
        )
      else()
        set(test_source
            "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests/${variable_lc}.cpp"
        )
      endif()
      file(WRITE "${test_source}" "${${variable}_SOURCE}\n")
    endif()
    set(test_binary
        ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests/${variable_lc}
    )

    get_directory_property(CONFIG_TEST_INCLUDE_DIRS INCLUDE_DIRECTORIES)
    get_directory_property(CONFIG_TEST_LINK_DIRS LINK_DIRECTORIES)
    set(COMPILE_DEFINITIONS_TMP)
    set(CONFIG_TEST_COMPILE_DEFINITIONS)
    get_directory_property(COMPILE_DEFINITIONS_TMP COMPILE_DEFINITIONS)
    foreach(def IN LISTS COMPILE_DEFINITIONS_TMP
                         ${variable}_COMPILE_DEFINITIONS
    )
      set(CONFIG_TEST_COMPILE_DEFINITIONS
          "${CONFIG_TEST_COMPILE_DEFINITIONS} -D${def}"
      )
    endforeach()
    get_property(
      PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PUBLIC_VAR GLOBAL
      PROPERTY PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PUBLIC
    )
    get_property(
      PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PRIVATE_VAR GLOBAL
      PROPERTY PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PRIVATE
    )
    set(PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_VAR
        ${PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PUBLIC_VAR}
        ${PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_PRIVATE_VAR}
    )
    foreach(_flag ${PIKA_ALGORITHMS_TARGET_COMPILE_OPTIONS_VAR})
      if(NOT "${_flag}" MATCHES "^\\$.*")
        set(CONFIG_TEST_COMPILE_DEFINITIONS
            "${CONFIG_TEST_COMPILE_DEFINITIONS} ${_flag}"
        )
      endif()
    endforeach()

    set(CONFIG_TEST_INCLUDE_DIRS ${CONFIG_TEST_INCLUDE_DIRS}
                                 ${${variable}_INCLUDE_DIRECTORIES}
    )
    set(CONFIG_TEST_LINK_DIRS ${CONFIG_TEST_LINK_DIRS}
                              ${${variable}_LINK_DIRECTORIES}
    )

    set(CONFIG_TEST_LINK_LIBRARIES ${${variable}_LIBRARIES})

    set(additional_cmake_flags)
    if(MSVC)
      set(additional_cmake_flags "-WX")
    else()
      set(additional_cmake_flags "-Werror")
    endif()

    if(${variable}_EXECUTE)
      if(NOT CMAKE_CROSSCOMPILING)
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} ${additional_cmake_flags} ${${variable}_CXXFLAGS}"
        )
        # cmake-format: off
        try_run(
          ${variable}_RUN_RESULT ${variable}_COMPILE_RESULT
          ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests
          ${test_source}
          COMPILE_DEFINITIONS ${CONFIG_TEST_COMPILE_DEFINITIONS}
          CMAKE_FLAGS
            "-DINCLUDE_DIRECTORIES=${CONFIG_TEST_INCLUDE_DIRS}"
            "-DLINK_DIRECTORIES=${CONFIG_TEST_LINK_DIRS}"
            "-DLINK_LIBRARIES=${CONFIG_TEST_LINK_LIBRARIES}"
          CXX_STANDARD ${PIKA_ALGORITHMS_WITH_CXX_STANDARD}
          CXX_STANDARD_REQUIRED ON
          CXX_EXTENSIONS FALSE
          RUN_OUTPUT_VARIABLE ${variable}_OUTPUT
          ARGS ${${variable}_ARGS}
        )
        # cmake-format: on
        if(${variable}_COMPILE_RESULT AND NOT ${variable}_RUN_RESULT)
          set(${variable}_RESULT TRUE)
        else()
          set(${variable}_RESULT FALSE)
        endif()
      else()
        set(${variable}_RESULT FALSE)
      endif()
    else()
      if(PIKA_ALGORITHMS_WITH_CUDA)
        set(cuda_parameters CUDA_STANDARD ${CMAKE_CUDA_STANDARD})
      endif()
      set(CMAKE_CXX_FLAGS
          "${CMAKE_CXX_FLAGS} ${additional_cmake_flags} ${${variable}_CXXFLAGS}"
      )
      set(CMAKE_CUDA_FLAGS
          "${CMAKE_CUDA_FLAGS} ${additional_cmake_flags} ${${variable}_CXXFLAGS}"
      )
      # cmake-format: off
      try_compile(
        ${variable}_RESULT
        ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/config_tests
        ${test_source}
        COMPILE_DEFINITIONS ${CONFIG_TEST_COMPILE_DEFINITIONS}
        CMAKE_FLAGS
          "-DINCLUDE_DIRECTORIES=${CONFIG_TEST_INCLUDE_DIRS}"
          "-DLINK_DIRECTORIES=${CONFIG_TEST_LINK_DIRS}"
          "-DLINK_LIBRARIES=${CONFIG_TEST_LINK_LIBRARIES}"
        OUTPUT_VARIABLE ${variable}_OUTPUT
        CXX_STANDARD ${PIKA_ALGORITHMS_WITH_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS FALSE
        ${cuda_parameters}
        COPY_FILE ${test_binary}
      )
      # cmake-format: on
      pika_algorithms_debug("Compile test: ${variable}")
      pika_algorithms_debug("Compilation output: ${${variable}_OUTPUT}")
    endif()

    set(_run_msg "Success")
  else()
    set(${variable}_RESULT ${${variable}})
    if(NOT _run_msg)
      set(_run_msg "pre-set to ${${variable}}")
    endif()
  endif()

  set(_msg "Performing Test ${variable}")

  if(${variable}_RESULT)
    set(_msg "${_msg} - ${_run_msg}")
  else()
    set(_msg "${_msg} - Failed")
  endif()

  set(${variable}
      ${${variable}_RESULT}
      CACHE INTERNAL ""
  )
  pika_algorithms_info(${_msg})

  if(${variable}_RESULT)
    foreach(definition ${${variable}_DEFINITIONS})
      pika_algorithms_add_config_define(${definition})
    endforeach()
  elseif(${variable}_REQUIRED)
    pika_algorithms_warn(
      "Test failed, detailed output:\n\n${${variable}_OUTPUT}"
    )
    pika_algorithms_error(${${variable}_REQUIRED})
  endif()
endfunction()

# ##############################################################################
function(pika_algorithms_check_for_cxx17_std_transform_scan)
  pika_algorithms_add_config_test(
    PIKA_ALGORITHMS_WITH_CXX17_STD_TRANSFORM_SCAN_ALGORITHMS
    SOURCE cmake/tests/cxx17_std_transform_scan_algorithms.cpp
    FILE ${ARGN}
  )
endfunction()

# ##############################################################################
function(pika_algorithms_check_for_cxx17_std_scan)
  pika_algorithms_add_config_test(
    PIKA_ALGORITHMS_WITH_CXX17_STD_SCAN_ALGORITHMS
    SOURCE cmake/tests/cxx17_std_scan_algorithms.cpp
    FILE ${ARGN}
  )
endfunction()

# ##############################################################################
function(pika_algorithms_check_for_std_experimental_simd)
  pika_algorithms_add_config_test(
    PIKA_ALGORITHMS_WITH_STD_EXPERIMENTAL_SIMD
    SOURCE cmake/tests/std_experimental_simd.cpp
    FILE ${ARGN}
  )
endfunction()

# ##############################################################################
function(pika_algorithms_check_for_cxx20_std_ranges_iter_swap)
  pika_algorithms_add_config_test(
    PIKA_ALGORITHMS_WITH_CXX20_STD_RANGES_ITER_SWAP
    SOURCE cmake/tests/cxx20_std_ranges_iter_swap.cpp
    FILE ${ARGN} CHECK_CXXSTD 20
  )
endfunction()

# ##############################################################################
function(pika_algorithms_check_for_mm_prefetch)
  pika_algorithms_add_config_test(
    PIKA_ALGORITHMS_WITH_MM_PREFETCH
    SOURCE cmake/tests/mm_prefetch.cpp
    FILE ${ARGN}
  )
endfunction()
