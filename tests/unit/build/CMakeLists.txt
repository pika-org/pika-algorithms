# Copyright (c) 2014 Thomas Heller
# Copyright (c) 2018 Nikunj Gupta
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# If build of external build tests is disabled, exit now
if(NOT PIKA_ALGORITHMS_WITH_TESTS_EXTERNAL_BUILD)
  return()
endif()

# Try building an external cmake based project ...
function(pika_algorithms_create_cmake_test name using_install_dir
         pika_algorithms_dir build_type test_dir
)
  set(build_dir "${CMAKE_CURRENT_BINARY_DIR}/${name}")
  if(CMAKE_TOOLCHAIN_FILE)
    set(ADDITIONAL_CMAKE_OPTIONS ${ADDITIONAL_CMAKE_OPTIONS}
                                 -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    )
  endif()
  if(CMAKE_MAKE_COMMAND)
    set(ADDITIONAL_CMAKE_OPTIONS ${ADDITIONAL_CMAKE_OPTIONS}
                                 -DCMAKE_MAKE_COMMAND=${CMAKE_MAKE_COMMAND}
    )
  endif()
  if(CMAKE_SYSROOT)
    set(ADDITIONAL_CMAKE_OPTIONS ${ADDITIONAL_CMAKE_OPTIONS}
                                 -DCMAKE_SYSROOT=${CMAKE_SYSROOT}
    )
  endif()
  if(NOT MSVC)
    set(ADDITIONAL_CMAKE_OPTIONS ${ADDITIONAL_CMAKE_OPTIONS}
                                 -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    )
  else()
    set(ADDITIONAL_CMAKE_OPTIONS
        ${ADDITIONAL_CMAKE_OPTIONS}
        -DPIKA_ALGORITHMS_OUTPUT_DIRECTORY=${PIKA_ALGORITHMS_WITH_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
    )
  endif()
  set(test_dir "${PROJECT_SOURCE_DIR}/${test_dir}")
  if(PIKA_ALGORITHMS_WITH_CLANG_CUDA)
    set(cmake_cuda_compiler -DCMAKE_CUDA_COMPILER=${CMAKE_CUDA_COMPILER})
  endif()
  add_custom_target(
    ${name}
    COMMAND
      "${CMAKE_CTEST_COMMAND}" --build-and-test "${test_dir}" "${build_dir}"
      --build-generator "${CMAKE_GENERATOR}" --build-noclean --build-options
      -Dpika-algorithms_DIR=${pika_algorithms_dir} -Dpika_DIR=${pika_DIR}
      ${ADDITIONAL_CMAKE_OPTIONS} -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS_SAFE}
      -DCMAKE_BUILD_TYPE=${build_type} ${cmake_cuda_compiler} --test-command
      "${CMAKE_CTEST_COMMAND}" --output-on-failure
    VERBATIM
  )
  add_dependencies(${name} pika_algorithms)

  if(MSVC)
    set_target_properties(${name} PROPERTIES FOLDER "Tests/Unit/Build")
  endif()
endfunction()

if(MSVC)
  set(build_types ${CMAKE_BUILD_TYPE})
else()
  set(build_types Debug Release RelWithDebInfo)
  # lld (which HIP uses) does not support the -Os flags in older versions. We do
  # not attempt to detect the linker in the general case, but disable the
  # MinSizeRel test here since we know that HIP only uses lld.
  if(NOT PIKA_ALGORITHMS_WITH_HIP OR (HIP_VERSION VERSION_GREATER_EQUAL "4.0.0"
                                     )
  )
    list(APPEND build_types MinSizeRel)
  endif()
endif()

if(NOT MSVC)
  foreach(build_type ${build_types})
    string(TOLOWER "${build_type}" build_type_lc)

    pika_algorithms_create_cmake_test(
      cmake_${build_type_lc}_build_dir_test FALSE
      "${PROJECT_BINARY_DIR}/lib/cmake/pika-algorithms" ${build_type}
      "examples/hello_world_standalone"
    )

    pika_algorithms_create_cmake_test(
      cmake_${build_type_lc}_install_dir_test TRUE
      "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/pika-algorithms" ${build_type}
      "examples/hello_world_standalone"
    )
  endforeach()
endif()

set(cmake_tests build_dir install_dir)

pika_algorithms_add_pseudo_target(tests.unit.build.cmake)
foreach(build_type ${build_types})
  string(TOLOWER "${build_type}" build_type_lc)
  pika_algorithms_add_pseudo_target(tests.unit.build.cmake.${build_type_lc})
  foreach(test ${cmake_tests})
    pika_algorithms_add_pseudo_target(
      tests.unit.build.cmake.${build_type_lc}.${test}
    )
    pika_algorithms_add_pseudo_dependencies(
      tests.unit.build.cmake.${build_type_lc}.${test}
      cmake_${build_type_lc}_${test}_test
    )
    pika_algorithms_add_pseudo_dependencies(
      tests.unit.build.cmake.${build_type_lc}
      tests.unit.build.cmake.${build_type_lc}.${test}
    )
  endforeach()
  pika_algorithms_add_pseudo_dependencies(
    tests.unit.build.cmake tests.unit.build.cmake.${build_type_lc}
  )
endforeach()
pika_algorithms_add_pseudo_dependencies(tests.unit.build tests.unit.build.cmake)
