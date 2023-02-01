# Copyright (c)      2020 Mikael Simberg
# Copyright (c) 2007-2020 Hartmut Kaiser
# Copyright (c) 2011-2014 Thomas Heller
# Copyright (c) 2007-2008 Chirag Dekate
# Copyright (c)      2011 Bryce Lelbach
# Copyright (c)      2011 Vinay C Amatya
# Copyright (c)      2013 Jeroen Habraken
# Copyright (c) 2014-2016 Andreas Schaefer
# Copyright (c) 2017      Abhimanyu Rawat
# Copyright (c) 2017      Google
# Copyright (c) 2017      Taeguk Kwon
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

# ##############################################################################
# Build type (needs to be handled before project command below)
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE
        STRING
        "Configuration type (one of Debug, RelWithDebInfo, Release, MinSizeRel)"
        FORCE
  )
endif()

# ##############################################################################
# project metadata
# ##############################################################################
project(pika-algorithms CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ##############################################################################
# Build all of pika-algorithms
# ##############################################################################
set(PIKA_ALGORITHMS_VERSION_MAJOR 0)
set(PIKA_ALGORITHMS_VERSION_MINOR 1)
set(PIKA_ALGORITHMS_VERSION_PATCH 1)
set(PIKA_ALGORITHMS_VERSION_DATE 20230201)
set(PIKA_ALGORITHMS_VERSION_TAG "-trunk")

set(PIKA_ALGORITHMS_VERSION
    "${PIKA_ALGORITHMS_VERSION_MAJOR}.${PIKA_ALGORITHMS_VERSION_MINOR}.${PIKA_ALGORITHMS_VERSION_PATCH}"
)
set(PIKA_ALGORITHMS_LIBRARY_VERSION "${PIKA_ALGORITHMS_VERSION}")
set(PIKA_ALGORITHMS_SOVERSION ${PIKA_ALGORITHMS_VERSION_MAJOR})
set(PIKA_ALGORITHMS_PACKAGE_NAME pika)
# To keep track of the pika root when other subprojects are declared
set(PIKA_ALGORITHMS_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
set(PIKA_ALGORITHMS_BINARY_DIR "${PROJECT_BINARY_DIR}")

# ##############################################################################
# CMake configuration
# ##############################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)
include(pika_algorithms_utils)

# explicitly set certain policies
cmake_policy(VERSION 3.18)
pika_algorithms_set_cmake_policy(CMP0042 NEW)
pika_algorithms_set_cmake_policy(CMP0060 NEW)
pika_algorithms_set_cmake_policy(CMP0074 NEW)

# We save the passed compiler flag to a special variable. This is needed for our
# build system unit tests. Some flags might influence the created symbols
# (_GLIBCXX_DEBUG i look at you)
set(CMAKE_CXX_FLAGS_SAFE ${CMAKE_CXX_FLAGS})
include(pika_algorithms_check_cxx_standard)

include(CheckCXXCompilerFlag)
include(CMakeDependentOption)

# include additional macro definitions
include(pika_algorithms_add_config_test)
include(pika_algorithms_add_definitions)

pika_algorithms_force_out_of_tree_build(
  "This project requires an out-of-source-tree build. See README.rst. Clean your CMake cache and CMakeFiles if this message persists."
)

if(NOT PIKA_ALGORITHMS_CMAKE_LOGLEVEL)
  set(PIKA_ALGORITHMS_CMAKE_LOGLEVEL "WARN")
endif()

# print initial diagnostics
pika_algorithms_info("CMake version: ${CMAKE_VERSION}")
pika_algorithms_info("pika-algorithms version: ${PIKA_ALGORITHMS_VERSION}")

# ##############################################################################
# reset cached variables that need to be re-filled
unset(PIKA_ALGORITHMS_EXPORT_TARGETS CACHE)
unset(PIKA_ALGORITHMS_EXPORT_INTERNAL_TARGETS CACHE)
unset(PIKA_ALGORITHMS_LIBS CACHE)
unset(PIKA_ALGORITHMS_ENABLED_MODULES CACHE)

# ##############################################################################
# Set up dummy compiler flags targets
# ##############################################################################
include(pika_algorithms_compiler_flags_targets)

if(MSVC)
  pika_algorithms_option(
    PIKA_ALGORITHMS_WITH_VS_STARTUP_PROJECT
    STRING
    "Define the startup project for the pika-algorithms solution (default: ALL_BUILD)."
    "ALL_BUILD"
    ADVANCED
  )
  if(PIKA_ALGORITHMS_WITH_VS_STARTUP_PROJECT)
    set(VS_STARTUP_PROJECT ${PIKA_ALGORITHMS_WITH_VS_STARTUP_PROJECT})
  endif()
endif()

# ##############################################################################
# Set our build options cache variables which are customizable by users

# Compiler related build options
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_GCC_VERSION_CHECK BOOL
  "Don't ignore version reported by gcc (default: ON)" ON ADVANCED
)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_COMPILER_WARNINGS BOOL
  "Enable compiler warnings (default: ON)" ON ADVANCED
)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_COMPILER_WARNINGS_AS_ERRORS BOOL
  "Turn compiler warnings into errors (default: OFF)" OFF ADVANCED
)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_EXECUTABLE_PREFIX STRING
  "Executable prefix (default: none)." ""
  CATEGORY "Build Targets"
  ADVANCED
)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_BINARY_DIR
  PATH
  "Root directory for libraries and executables for the build. This does not affect the installed location of libraries and executables."
  "${PROJECT_BINARY_DIR}"
  CATEGORY "Build Targets"
  ADVANCED
)

if(WIN32)
  set(PIKA_ALGORITHMS_WITH_PSEUDO_DEPENDENCIES
      OFF
      CACHE INTERNAL "" FORCE
  )
else()
  set(PIKA_ALGORITHMS_WITH_PSEUDO_DEPENDENCIES
      ON
      CACHE INTERNAL "" FORCE
  )
endif()

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_UNITY_BUILD BOOL
  "Enable unity build for certain build targets (default: ON)" ON ADVANCED
)
if(PIKA_ALGORITHMS_WITH_UNITY_BUILD)
  set(PIKA_ALGORITHMS_WITH_UNITY_BUILD_OPTION UNITY_BUILD)
endif()

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_PRECOMPILED_HEADERS
  BOOL
  "Enable precompiled headers for certain build targets (experimental) (default: OFF)"
  OFF
  ADVANCED
)
if(PIKA_ALGORITHMS_WITH_PRECOMPILED_HEADERS)
  set(PIKA_ALGORITHMS_WITH_PRECOMPILED_HEADERS_INTERNAL ON)
  # Only create the targets here. They will be set up later once all modules are
  # known.
  add_executable(pika_algorithms_exe_precompiled_headers src/dummy.cpp)

  set_target_properties(
    pika_algorithms_exe_precompiled_headers PROPERTIES FOLDER "Core"
  )
endif()

# ##############################################################################
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_EXAMPLES BOOL "Build examples (default: OFF)" OFF
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS BOOL "Build tests (default: OFF)" OFF
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_BENCHMARKS BOOL
  "Build benchmark tests (default: ON)" ON DEPENDS "PIKA_ALGORITHMS_WITH_TESTS"
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_REGRESSIONS BOOL
  "Build regression tests (default: ON)" ON DEPENDS "PIKA_ALGORITHMS_WITH_TESTS"
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_UNIT BOOL "Build unit tests (default: ON)" ON
  DEPENDS "PIKA_ALGORITHMS_WITH_TESTS" CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_HEADERS
  BOOL
  "Build header tests (default: ON)"
  ON
  ADVANCED
  DEPENDS
  "PIKA_ALGORITHMS_WITH_TESTS"
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_EXTERNAL_BUILD
  BOOL
  "Build external CMake build tests (default: ON)"
  ON
  ADVANCED
  DEPENDS
  "PIKA_ALGORITHMS_WITH_TESTS"
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_EXAMPLES
  BOOL
  "Add examples as tests (default: ON)"
  ON
  DEPENDS
  "PIKA_ALGORITHMS_WITH_TESTS;PIKA_ALGORITHMS_WITH_EXAMPLES"
  ADVANCED
  CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_COMPILE_ONLY_TESTS BOOL
  "Create build system support for compile time only tests (default: ON)" ON
  DEPENDS "PIKA_ALGORITHMS_WITH_TESTS" CATEGORY "Build Targets"
)
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_FAIL_COMPILE_TESTS BOOL
  "Create build system support for fail compile tests (default: ON)" ON DEPENDS
  "PIKA_ALGORITHMS_WITH_TESTS" CATEGORY "Build Targets"
)

# We create a target to contain libraries like rt, dl etc. in order to remove
# global variables
add_library(pika_algorithms_base_libraries INTERFACE)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TESTS_MAX_THREADS
  STRING
  "Maximum number of threads to use for tests (default: 0, use the number of threads specified by the test)"
  0
  CATEGORY "Debugging"
  ADVANCED
)

pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_PARALLEL_TESTS_BIND_NONE
  BOOL
  "Pass --pika:bind=none to tests that may run in parallel (cmake -j flag) (default: OFF)"
  OFF
  CATEGORY "Debugging"
  ADVANCED
)

# BADBAD: This enables an overload of swap which is necessary to work around the
# problems caused by zip_iterator not being a real random access iterator.
# Dereferencing zip_iterator does not yield a true reference but only a
# temporary tuple holding true references.
#
# A real fix for this problem is proposed in PR0022R0
# (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0022r0.html)
#
pika_algorithms_option(
  PIKA_ALGORITHMS_WITH_TUPLE_RVALUE_SWAP BOOL
  "Enable swapping of rvalue tuples (needed for sort_by_key, default: OFF)." OFF
  CATEGORY "Utility"
  ADVANCED
)
if(PIKA_ALGORITHMS_WITH_TUPLE_RVALUE_SWAP)
  pika_algorithms_add_config_define(PIKA_ALGORITHMS_HAVE_TUPLE_RVALUE_SWAP)
endif()

# Check for compiler compatibility
#

# Check if the selected compiler versions are supposed to work with our codebase
if(CMAKE_COMPILER_IS_GNUCXX AND PIKA_ALGORITHMS_WITH_GCC_VERSION_CHECK)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    pika_algorithms_error(
      "GCC 9.0 or higher is required. Specify PIKA_ALGORITHMS_WITH_GCC_VERSION_CHECK=OFF to ignore this error."
    )
  endif()
endif()

if(MSVC)
  if(MSVC_VERSION LESS 1900)
    pika_algorithms_error("MSVC x64 2015 or higher is required.")
  elseif(NOT CMAKE_CL_64)
    pika_algorithms_warn(
      "MSVC (32Bit) will compile but will fail running larger applications because of limitations in the Windows OS."
    )
  endif()
endif()

# ##############################################################################
# C++ feature tests
# ##############################################################################
include(pika_algorithms_perform_cxx_feature_tests)
pika_algorithms_perform_cxx_feature_tests()

# ##############################################################################
# check for miscellaneous things
# ##############################################################################
pika_algorithms_check_for_mm_prefetch(
  DEFINITIONS PIKA_ALGORITHMS_HAVE_MM_PREFETCH
)

if(NOT WIN32)
  # ############################################################################
  # Macro definitions for system headers
  # ############################################################################
  add_definitions(-D_GNU_SOURCE)

  # ############################################################################
  # System libraries
  # ############################################################################
  if(APPLE)
    pika_algorithms_add_compile_flag_if_available(-ftemplate-depth=256)
  endif()
endif()

if(WIN32)
  if(MSVC)
    pika_algorithms_add_target_compile_option(-Ox PUBLIC CONFIGURATIONS Release)

    # even VS2017 has an ICE when compiling with -Ob2
    pika_algorithms_add_target_compile_option(
      -Ob1 PUBLIC CONFIGURATIONS Release
    )

    # VS2012 and above has a special flag for improving the debug experience by
    # adding more symbol information to the build (-d2Zi)
    pika_algorithms_add_target_compile_option(
      -d2Zi+ PUBLIC CONFIGURATIONS RelWithDebInfo
    )

    # VS2013 and above know how to do link time constant data segment folding
    # VS2013 update 2 and above know how to remove debug information for
    # non-referenced functions and data (-Zc:inline)
    pika_algorithms_add_target_compile_option(-Zc:inline PUBLIC)
    pika_algorithms_add_target_compile_option(
      -Gw PUBLIC CONFIGURATIONS Release RelWithDebInfo MinSizeRel
    )
    pika_algorithms_add_target_compile_option(
      -Zo PUBLIC CONFIGURATIONS RelWithDebInfo
    )

    # Exceptions
    pika_algorithms_add_target_compile_option(-EHsc)
    if(MSVC_VERSION GREATER_EQUAL 1900)
      # assume conforming (throwing) operator new implementations
      pika_algorithms_add_target_compile_option(-Zc:throwingNew PUBLIC)

      # enable faster linking (requires VS2015 Update1) disabled for now as this
      # flag crashes debugger pika_algorithms_remove_link_flag(/debug
      # CONFIGURATIONS Debug) pika_algorithms_add_link_flag(/debug:fastlink
      # CONFIGURATIONS Debug)

      # Update 2 requires to set _ENABLE_ATOMIC_ALIGNMENT_FIX for it to compile
      # atomics
      pika_algorithms_add_config_define(_ENABLE_ATOMIC_ALIGNMENT_FIX)

      # Update 3 allows to flag rvalue misuses and enforces strict string const-
      # qualification conformance
      pika_algorithms_add_target_compile_option(-Zc:rvalueCast PUBLIC)
      pika_algorithms_add_target_compile_option(-Zc:strictStrings PUBLIC)

      # Update 8 requires to set _ENABLE_EXTENDED_ALIGNED_STORAGE for it to
      # compile atomics
      pika_algorithms_add_config_define(_ENABLE_EXTENDED_ALIGNED_STORAGE)

      # Make sure that __cplusplus is properly defined
      pika_algorithms_add_target_compile_option(-Zc:__cplusplus PUBLIC)

      # Silence C++17 deprecation warnings
      pika_algorithms_add_config_define(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)

      # Silence C++20 deprecation warnings
      pika_algorithms_add_config_define(_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS)

      # ASan is available in Visual Studion starting V16.8
      if((MSVC_VERSION GREATER_EQUAL 1928) AND PIKA_ALGORITHMS_WITH_SANITIZERS)
        pika_algorithms_add_target_compile_option(
          -fsanitize=address PUBLIC CONFIGURATIONS RelWithDebInfo Debug
        )
      endif()
    endif()

    # Runtime type information
    pika_algorithms_add_target_compile_option(-GR PUBLIC)
    # Multiprocessor build
    pika_algorithms_add_target_compile_option(-MP PUBLIC)
    # Increase the maximum size of object file sections
    pika_algorithms_add_target_compile_option(-bigobj PUBLIC)
  endif()

  target_link_libraries(pika_algorithms_base_libraries INTERFACE psapi shlwapi)

  # ############################################################################
  # Macro definitions for system headers
  # ############################################################################
  add_definitions(-D_WINDOWS)
  add_definitions(-D_WIN32)
  pika_algorithms_add_config_define("_WIN32_WINNT=0x0602")
  pika_algorithms_add_config_define(_SCL_SECURE_NO_WARNINGS)
  pika_algorithms_add_config_define(_CRT_SECURE_NO_WARNINGS)
  pika_algorithms_add_config_define(_SCL_SECURE_NO_DEPRECATE)
  pika_algorithms_add_config_define(_CRT_SECURE_NO_DEPRECATE)
  pika_algorithms_add_config_define(_CRT_NONSTDC_NO_WARNINGS)
  pika_algorithms_add_config_define(_WINSOCK_DEPRECATED_NO_WARNINGS)
  pika_algorithms_add_config_define(_CRT_NON_CONFORMING_SWPRINTFS)
  pika_algorithms_add_config_define(_SILENCE_FPOS_SEEKPOS_DEPRECATION_WARNING)

  # ############################################################################
  # Boost
  # ############################################################################

  pika_algorithms_add_config_define(BOOST_USE_WINDOWS_H)
  if(NOT CMAKE_CL_64)
    pika_algorithms_add_config_define(BOOST_NO_ALIGNMENT)
  endif()
  pika_algorithms_add_config_define("PSAPI_VERSION=1")
endif()

# Configure Warnings
if(PIKA_ALGORITHMS_WITH_COMPILER_WARNINGS)
  if(MSVC) # Adding special warning settings for the MSVC compiler ...
    pika_algorithms_add_compile_flag(-W3)

    # MSVC2012/2013 are overeager to report 'qualifier applied to function type
    # has no meaning; ignored'
    pika_algorithms_add_compile_flag(-wd4180)

    # Boost.Lockfree triggers 'warning C4307: '+' : integral constant overflow'
    # which is benign
    pika_algorithms_add_compile_flag(-wd4307)

    # object allocated on the heap may not be aligned
    pika_algorithms_add_compile_flag(-wd4316)

    # max symbol length exceeded
    pika_algorithms_add_compile_flag(-wd4503)

    # 'int': forcing value to bool 'true' or 'false' (performance warning)
    pika_algorithms_add_compile_flag(-wd4800)

    # vcpkg enables the /utf-8 option which causes (benign) warnings in the
    # Spirit headers: The file contains a character starting at offset ... that
    # is illegal in the current source character set
    pika_algorithms_add_compile_flag(-wd4828)

  else() # Trial and error approach for any other compiler ...
    pika_algorithms_add_compile_flag_if_available(-Wall)
    pika_algorithms_add_compile_flag_if_available(-Wextra)
    pika_algorithms_add_compile_flag_if_available(-Wpedantic)
    pika_algorithms_add_compile_flag_if_available(-Wno-strict-aliasing)
    pika_algorithms_add_compile_flag_if_available(-Wno-sign-promo)
    pika_algorithms_add_compile_flag_if_available(-Wno-attributes)
    pika_algorithms_add_compile_flag_if_available(-Wno-cast-align)

    # We do not in general guarantee ABI compatibility between C++ standards, so
    # we ignore this warning
    pika_algorithms_add_compile_flag_if_available(-Wno-noexcept-type)

    # Be extra strict about format checks Boost.Logging is built on fprintf,
    # sadly
    pika_algorithms_add_compile_flag_if_available(-Wformat=2)
    pika_algorithms_add_compile_flag_if_available(-Wno-format-nonliteral)

    # Self initialization is dangerous
    pika_algorithms_add_compile_flag_if_available(-Winit-self)

    # For portability
    pika_algorithms_add_compile_flag_if_available(-Wdouble-promotion)

    # Warn about casting that violates qualifiers or alignment
    pika_algorithms_add_compile_flag_if_available(-Wcast-qual)
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      # Clang is overeager in reporting cast alignment problems in Boost
      pika_algorithms_add_compile_flag_if_available(-Wcast-align)
    endif()

    pika_algorithms_add_compile_flag_if_available(-Werror=parentheses)
    pika_algorithms_add_compile_flag_if_available(-Werror=reorder)
    pika_algorithms_add_compile_flag_if_available(-Werror=return-type)
    pika_algorithms_add_compile_flag_if_available(-Werror=sequence-point)
    pika_algorithms_add_compile_flag_if_available(-Werror=uninitialized)
    pika_algorithms_add_compile_flag_if_available(-Werror=format)
    pika_algorithms_add_compile_flag_if_available(-Werror=missing-braces)
    pika_algorithms_add_compile_flag_if_available(-Werror=sign-compare)
  endif()
endif()

if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION
                                VERSION_GREATER_EQUAL 12.0
)
  pika_algorithms_add_compile_flag_if_available(-Wno-interference-size)
endif()

# Configure compiler warnings as errors
if(PIKA_ALGORITHMS_WITH_COMPILER_WARNINGS_AS_ERRORS)
  if(MSVC)
    pika_algorithms_add_compile_flag(-WX)
  else()
    pika_algorithms_add_compile_flag_if_available(-Werror)
  endif()
endif()

# Diagnostics
if(MSVC)
  # Display full paths in diagnostics
  pika_algorithms_add_compile_flag(-FC)
else()
  # Show the flags that toggle each warning
  pika_algorithms_add_compile_flag_if_available(-fdiagnostics-show-option)

  # VLAs are a GNU extensions that we forbid as they are not supported on MSVC
  pika_algorithms_add_compile_flag_if_available(-Werror=vla)
  # No return statement in a non-void function can lead to garbage return values
  # in GCC.
  pika_algorithms_add_compile_flag_if_available(-Werror=return-type)

  # We get false positives all over the place with this.
  if(CMAKE_COMPILER_IS_GNUCXX)
    pika_algorithms_add_compile_flag_if_available(-Wno-unused-but-set-parameter)
    pika_algorithms_add_compile_flag_if_available(-Wno-unused-but-set-variable)
    # Uninitialized variables are bad, earlier compilers issue spurious warnings
    pika_algorithms_add_compile_flag_if_available(-Werror=uninitialized)
    pika_algorithms_add_compile_flag_if_available(-Wno-unused-local-typedefs)
    # -Werror=maybe-uninitialized leads to false positives.
    pika_algorithms_add_compile_flag_if_available(-Wno-maybe-uninitialized)
  endif()

  # Silence warning about __sync_fetch_and_nand changing semantics
  pika_algorithms_add_compile_flag_if_available(-Wno-sync-nand)

  # Silence warnings about deleting polymorphic objects with non-virtual dtors.
  # These come from within Boost.
  if(CMAKE_COMPILER_IS_GNUCXX)
    pika_algorithms_add_compile_flag_if_available(-Wno-delete-non-virtual-dtor)
  endif()

  # Check if our libraries have unresolved symbols
  if(NOT APPLE
     AND NOT WIN32
     AND NOT PIKA_ALGORITHMS_WITH_SANITIZERS
  )
    pika_algorithms_add_link_flag_if_available(-Wl,-z,defs)
  endif()
  if(WIN32)
    target_link_libraries(
      pika_algorithms_base_libraries INTERFACE psapi WS2_32 mswsock
    )
  endif()

  if("${PIKA_ALGORITHMS_PLATFORM_UC}" STREQUAL "BLUEGENEQ")
    pika_algorithms_add_compile_flag_if_available(-Wno-deprecated-register)
  endif()

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    pika_algorithms_add_compile_flag_if_available(-Wno-cast-align)
  endif()

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # Disable the following warnings: #1170: invalid redeclaration of nested
    # class
    pika_algorithms_add_compile_flag_if_available(-wd1170)
    # #858: type qualifier on return type is meaningless
    pika_algorithms_add_compile_flag_if_available(-wd858)
    # #1098: the qualifier on this friend declaration is ignored
    pika_algorithms_add_compile_flag_if_available(-wd1098)
    # #488: template parameter not used in declaring the parameter type
    pika_algorithms_add_compile_flag_if_available(-wd488)
    # #2203: cast discards qualifiers from target type (needed for mvapich2 mpi
    # header)
    pika_algorithms_add_compile_flag_if_available(-wd2203)
    # #2536: cannot specify explicit initializer for arrays
    pika_algorithms_add_compile_flag_if_available(-wd2536)
    # #1286: invalid attribute
    pika_algorithms_add_compile_flag_if_available(-wd1286)
  endif()
endif()

# ##############################################################################
# Dependencies
# ##############################################################################
include(pika_algorithms_setup_boost)
include(pika_algorithms_setup_fmt)
include(pika_algorithms_setup_pika)

# ##############################################################################
# Git commit detection
# ##############################################################################
include(pika_algorithms_git_commit)
pika_algorithms_add_config_define(
  PIKA_ALGORITHMS_HAVE_GIT_COMMIT "\"${PIKA_ALGORITHMS_WITH_GIT_COMMIT}\""
)

include(pika_algorithms_set_output_paths)

# ##############################################################################
# Add custom targets for tests
# ##############################################################################
if(PIKA_ALGORITHMS_WITH_TESTS)
  pika_algorithms_add_pseudo_target(tests)
  if(PIKA_ALGORITHMS_WITH_TESTS_UNIT)
    pika_algorithms_add_pseudo_target(tests.unit)
    pika_algorithms_add_pseudo_dependencies(tests tests.unit)
  endif()
  if(PIKA_ALGORITHMS_WITH_TESTS_REGRESSIONS)
    pika_algorithms_add_pseudo_target(tests.regressions)
    pika_algorithms_add_pseudo_dependencies(tests tests.regressions)
  endif()
  if(PIKA_ALGORITHMS_WITH_TESTS_BENCHMARKS)
    pika_algorithms_add_pseudo_target(tests.performance)
    pika_algorithms_add_pseudo_dependencies(tests tests.performance)
  endif()
  if(PIKA_ALGORITHMS_WITH_TESTS_HEADERS)
    pika_algorithms_add_pseudo_target(tests.headers)
    pika_algorithms_add_pseudo_dependencies(tests tests.headers)
  endif()
  if(PIKA_ALGORITHMS_WITH_EXAMPLES AND PIKA_ALGORITHMS_WITH_TESTS_EXAMPLES)
    pika_algorithms_add_pseudo_target(tests.examples)
    pika_algorithms_add_pseudo_dependencies(tests tests.examples)
  endif()

  enable_testing()
  include(CTest)

  add_subdirectory(testing)
endif()

if(PIKA_ALGORITHMS_WITH_EXAMPLES)
  pika_algorithms_add_pseudo_target(examples)
endif()

# ##############################################################################
# Debug library postfix
# ##############################################################################
set(CMAKE_DEBUG_POSTFIX "d")
set(PIKA_ALGORITHMS_DEBUG_POSTFIX "d")

# ##############################################################################
# pika_algorithms target
# ##############################################################################
set(pika_algorithms_headers
    pika/algorithm.hpp
    pika/algorithms/traits/pointer_category.hpp
    pika/algorithms/traits/projected.hpp
    pika/algorithms/traits/projected_range.hpp
    pika/memory.hpp
    pika/numeric.hpp
    pika/parallel/algorithm.hpp
    pika/parallel/algorithms/adjacent_difference.hpp
    pika/parallel/algorithms/adjacent_find.hpp
    pika/parallel/algorithms/all_any_none.hpp
    pika/parallel/algorithms/copy.hpp
    pika/parallel/algorithms/count.hpp
    pika/parallel/algorithms/destroy.hpp
    pika/parallel/algorithms/detail/accumulate.hpp
    pika/parallel/algorithms/detail/adjacent_difference.hpp
    pika/parallel/algorithms/detail/advance_and_get_distance.hpp
    pika/parallel/algorithms/detail/advance_to_sentinel.hpp
    pika/parallel/algorithms/detail/dispatch.hpp
    pika/parallel/algorithms/detail/distance.hpp
    pika/parallel/algorithms/detail/fill.hpp
    pika/parallel/algorithms/detail/find.hpp
    pika/parallel/algorithms/detail/generate.hpp
    pika/parallel/algorithms/detail/indirect.hpp
    pika/parallel/algorithms/detail/insertion_sort.hpp
    pika/parallel/algorithms/detail/is_negative.hpp
    pika/parallel/algorithms/detail/is_sorted.hpp
    pika/parallel/algorithms/detail/parallel_stable_sort.hpp
    pika/parallel/algorithms/detail/pivot.hpp
    pika/parallel/algorithms/detail/predicates.hpp
    pika/parallel/algorithms/detail/rotate.hpp
    pika/parallel/algorithms/detail/sample_sort.hpp
    pika/parallel/algorithms/detail/search.hpp
    pika/parallel/algorithms/detail/set_operation.hpp
    pika/parallel/algorithms/detail/spin_sort.hpp
    pika/parallel/algorithms/detail/transfer.hpp
    pika/parallel/algorithms/detail/upper_lower_bound.hpp
    pika/parallel/algorithms/ends_with.hpp
    pika/parallel/algorithms/equal.hpp
    pika/parallel/algorithms/exclusive_scan.hpp
    pika/parallel/algorithms/fill.hpp
    pika/parallel/algorithms/find.hpp
    pika/parallel/algorithms/for_each.hpp
    pika/parallel/algorithms/for_loop.hpp
    pika/parallel/algorithms/for_loop_induction.hpp
    pika/parallel/algorithms/for_loop_reduction.hpp
    pika/parallel/algorithms/generate.hpp
    pika/parallel/algorithms/includes.hpp
    pika/parallel/algorithms/inclusive_scan.hpp
    pika/parallel/algorithms/is_heap.hpp
    pika/parallel/algorithms/is_partitioned.hpp
    pika/parallel/algorithms/is_sorted.hpp
    pika/parallel/algorithms/lexicographical_compare.hpp
    pika/parallel/algorithms/make_heap.hpp
    pika/parallel/algorithms/merge.hpp
    pika/parallel/algorithms/minmax.hpp
    pika/parallel/algorithms/mismatch.hpp
    pika/parallel/algorithms/move.hpp
    pika/parallel/algorithms/nth_element.hpp
    pika/parallel/algorithms/partial_sort.hpp
    pika/parallel/algorithms/partial_sort_copy.hpp
    pika/parallel/algorithms/partition.hpp
    pika/parallel/algorithms/reduce.hpp
    pika/parallel/algorithms/reduce_by_key.hpp
    pika/parallel/algorithms/remove.hpp
    pika/parallel/algorithms/remove_copy.hpp
    pika/parallel/algorithms/replace.hpp
    pika/parallel/algorithms/reverse.hpp
    pika/parallel/algorithms/rotate.hpp
    pika/parallel/algorithms/search.hpp
    pika/parallel/algorithms/set_difference.hpp
    pika/parallel/algorithms/set_intersection.hpp
    pika/parallel/algorithms/set_symmetric_difference.hpp
    pika/parallel/algorithms/set_union.hpp
    pika/parallel/algorithms/shift_left.hpp
    pika/parallel/algorithms/shift_right.hpp
    pika/parallel/algorithms/sort.hpp
    pika/parallel/algorithms/sort_by_key.hpp
    pika/parallel/algorithms/stable_sort.hpp
    pika/parallel/algorithms/starts_with.hpp
    pika/parallel/algorithms/swap_ranges.hpp
    pika/parallel/algorithms/transform.hpp
    pika/parallel/algorithms/transform_exclusive_scan.hpp
    pika/parallel/algorithms/transform_inclusive_scan.hpp
    pika/parallel/algorithms/transform_reduce.hpp
    pika/parallel/algorithms/transform_reduce_binary.hpp
    pika/parallel/algorithms/uninitialized_copy.hpp
    pika/parallel/algorithms/uninitialized_default_construct.hpp
    pika/parallel/algorithms/uninitialized_fill.hpp
    pika/parallel/algorithms/uninitialized_move.hpp
    pika/parallel/algorithms/uninitialized_value_construct.hpp
    pika/parallel/algorithms/unique.hpp
    pika/parallel/container_algorithms.hpp
    pika/parallel/container_algorithms/adjacent_difference.hpp
    pika/parallel/container_algorithms/adjacent_find.hpp
    pika/parallel/container_algorithms/all_any_none.hpp
    pika/parallel/container_algorithms/copy.hpp
    pika/parallel/container_algorithms/count.hpp
    pika/parallel/container_algorithms/destroy.hpp
    pika/parallel/container_algorithms/ends_with.hpp
    pika/parallel/container_algorithms/equal.hpp
    pika/parallel/container_algorithms/exclusive_scan.hpp
    pika/parallel/container_algorithms/fill.hpp
    pika/parallel/container_algorithms/find.hpp
    pika/parallel/container_algorithms/for_each.hpp
    pika/parallel/container_algorithms/for_loop.hpp
    pika/parallel/container_algorithms/generate.hpp
    pika/parallel/container_algorithms/includes.hpp
    pika/parallel/container_algorithms/inclusive_scan.hpp
    pika/parallel/container_algorithms/is_heap.hpp
    pika/parallel/container_algorithms/is_partitioned.hpp
    pika/parallel/container_algorithms/is_sorted.hpp
    pika/parallel/container_algorithms/lexicographical_compare.hpp
    pika/parallel/container_algorithms/make_heap.hpp
    pika/parallel/container_algorithms/merge.hpp
    pika/parallel/container_algorithms/minmax.hpp
    pika/parallel/container_algorithms/mismatch.hpp
    pika/parallel/container_algorithms/move.hpp
    pika/parallel/container_algorithms/nth_element.hpp
    pika/parallel/container_algorithms/partial_sort.hpp
    pika/parallel/container_algorithms/partial_sort_copy.hpp
    pika/parallel/container_algorithms/partition.hpp
    pika/parallel/container_algorithms/reduce.hpp
    pika/parallel/container_algorithms/remove.hpp
    pika/parallel/container_algorithms/remove_copy.hpp
    pika/parallel/container_algorithms/replace.hpp
    pika/parallel/container_algorithms/reverse.hpp
    pika/parallel/container_algorithms/rotate.hpp
    pika/parallel/container_algorithms/search.hpp
    pika/parallel/container_algorithms/set_difference.hpp
    pika/parallel/container_algorithms/set_intersection.hpp
    pika/parallel/container_algorithms/set_symmetric_difference.hpp
    pika/parallel/container_algorithms/set_union.hpp
    pika/parallel/container_algorithms/shift_left.hpp
    pika/parallel/container_algorithms/shift_right.hpp
    pika/parallel/container_algorithms/sort.hpp
    pika/parallel/container_algorithms/stable_sort.hpp
    pika/parallel/container_algorithms/starts_with.hpp
    pika/parallel/container_algorithms/swap_ranges.hpp
    pika/parallel/container_algorithms/transform.hpp
    pika/parallel/container_algorithms/transform_exclusive_scan.hpp
    pika/parallel/container_algorithms/transform_inclusive_scan.hpp
    pika/parallel/container_algorithms/transform_reduce.hpp
    pika/parallel/container_algorithms/uninitialized_copy.hpp
    pika/parallel/container_algorithms/uninitialized_default_construct.hpp
    pika/parallel/container_algorithms/uninitialized_fill.hpp
    pika/parallel/container_algorithms/uninitialized_move.hpp
    pika/parallel/container_algorithms/uninitialized_value_construct.hpp
    pika/parallel/container_algorithms/unique.hpp
    pika/parallel/container_memory.hpp
    pika/parallel/container_numeric.hpp
    pika/parallel/datapar.hpp
    pika/parallel/datapar/adjacent_difference.hpp
    pika/parallel/datapar/fill.hpp
    pika/parallel/datapar/find.hpp
    pika/parallel/datapar/generate.hpp
    pika/parallel/datapar/iterator_helpers.hpp
    pika/parallel/datapar/loop.hpp
    pika/parallel/datapar/transfer.hpp
    pika/parallel/datapar/transform_loop.hpp
    pika/parallel/datapar/zip_iterator.hpp
    pika/parallel/memory.hpp
    pika/parallel/numeric.hpp
    pika/parallel/spmd_block.hpp
    pika/parallel/util/cancellation_token.hpp
    pika/parallel/util/compare_projected.hpp
    pika/parallel/util/detail/algorithm_result.hpp
    pika/parallel/util/detail/chunk_size.hpp
    pika/parallel/util/detail/chunk_size_iterator.hpp
    pika/parallel/util/detail/handle_local_exceptions.hpp
    pika/parallel/util/detail/partitioner_iteration.hpp
    pika/parallel/util/detail/scoped_executor_parameters.hpp
    pika/parallel/util/detail/select_partitioner.hpp
    pika/parallel/util/detail/sender_util.hpp
    pika/parallel/util/detail/simd/vector_pack_alignment_size.hpp
    pika/parallel/util/detail/simd/vector_pack_all_any_none.hpp
    pika/parallel/util/detail/simd/vector_pack_count_bits.hpp
    pika/parallel/util/detail/simd/vector_pack_find.hpp
    pika/parallel/util/detail/simd/vector_pack_load_store.hpp
    pika/parallel/util/detail/simd/vector_pack_type.hpp
    pika/parallel/util/foreach_partitioner.hpp
    pika/parallel/util/invoke_projected.hpp
    pika/parallel/util/loop.hpp
    pika/parallel/util/low_level.hpp
    pika/parallel/util/merge_four.hpp
    pika/parallel/util/merge_vector.hpp
    pika/parallel/util/nbits.hpp
    pika/parallel/util/partitioner.hpp
    pika/parallel/util/partitioner_with_cleanup.hpp
    pika/parallel/util/prefetching.hpp
    pika/parallel/util/projection_identity.hpp
    pika/parallel/util/range.hpp
    pika/parallel/util/ranges_facilities.hpp
    pika/parallel/util/result_types.hpp
    pika/parallel/util/scan_partitioner.hpp
    pika/parallel/util/transfer.hpp
    pika/parallel/util/transform_loop.hpp
    pika/parallel/util/vector_pack_alignment_size.hpp
    pika/parallel/util/vector_pack_all_any_none.hpp
    pika/parallel/util/vector_pack_count_bits.hpp
    pika/parallel/util/vector_pack_find.hpp
    pika/parallel/util/vector_pack_load_store.hpp
    pika/parallel/util/vector_pack_type.hpp
    pika/parallel/util/zip_iterator.hpp
)

add_library(pika_algorithms INTERFACE)
target_link_libraries(
  pika_algorithms INTERFACE pika_algorithms_base_libraries
                            pika_algorithms_public_flags
)
target_include_directories(
  pika_algorithms
  INTERFACE $<BUILD_INTERFACE:${PIKA_ALGORITHMS_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(
  pika_algorithms
  PROPERTIES VERSION ${PIKA_VERSION}
             SOVERSION ${PIKA_SOVERSION}
             CLEAN_DIRECT_OUTPUT 1
             OUTPUT_NAME pika_algorithms
             FOLDER "Core"
)
install(
  TARGETS pika_algorithms
  EXPORT pika_algorithms_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT pika_algorithms
)
pika_algorithms_export_targets(pika_algorithms)

# ##############################################################################
# Target specification
# ##############################################################################
add_subdirectory(tools)

# ##############################################################################
# Tests
# ##############################################################################
if(PIKA_ALGORITHMS_WITH_TESTS)
  add_subdirectory(tests)
endif()

if(PIKA_ALGORITHMS_WITH_EXAMPLES)
  add_subdirectory(examples)
endif()

# Set up precompiled headers
if(PIKA_ALGORITHMS_WITH_PRECOMPILED_HEADERS)
  target_link_libraries(
    pika_algorithms_exe_precompiled_headers
    PRIVATE pika_algorithms pika_algorithms_private_flags
  )
  target_precompile_headers(
    pika_algorithms_exe_precompiled_headers PRIVATE <pika/algorithm.hpp>
    <pika/memory.hpp> <pika/numeric.hpp>}
  )
endif()

# ##############################################################################
# installation instructions
# ##############################################################################
# Install all pika-algorithms header that have been configured using various
# CMake options
install(
  DIRECTORY "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/pika/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pika
  COMPONENT core
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN ".git" EXCLUDE
  PATTERN "CMakeFiles" EXCLUDE
  PATTERN "CTestFiles" EXCLUDE
)

# Install all headers
install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT core
)

install(
  # Install all pika-algorithms CMake utility files
  DIRECTORY cmake/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pika-algorithms
  COMPONENT core
  PATTERN "templates" EXCLUDE
  PATTERN "packaging" EXCLUDE
  PATTERN ".git" EXCLUDE
)

install(
  FILES "${PROJECT_SOURCE_DIR}/LICENSE_1_0.txt"
  DESTINATION ${CMAKE_INSTALL_DATADIR}/pika-algorithms
  COMPONENT license
)

# ##############################################################################
# print overall configuration summary
include(pika_algorithms_print_summary)
pika_algorithms_create_configuration_summary(
  "Configuration summary:\n--" "pika_algorithms"
)

include(pika_algorithms_export_targets)
install(
  TARGETS pika_algorithms_base_libraries
  EXPORT pika_algorithms_internal_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT pika_algorithms_base_libraries
)
pika_algorithms_export_internal_targets(pika_algorithms_base_libraries)

# ##############################################################################
# store cache vars and their values in order for them to be forwarded to the
# projects (needs to be before the pika_algorithms_generate_package call)
include(pika_algorithms_forward_cache_variables)

# ##############################################################################
# External build system support.
include(pika_algorithms_generate_package)

message("")
message("pika-algorithms will be installed to ${CMAKE_INSTALL_PREFIX}")
message("")
