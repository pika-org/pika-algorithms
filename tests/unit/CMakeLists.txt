# Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
# Copyright (c) 2007-2012 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(subdirs algorithms block build container_algorithms)

if(PIKA_ALGORITHMS_WITH_STD_EXPERIMENTAL_SIMD)
  list(APPEND subdirs datapar_algorithms)
endif()

foreach(subdir ${subdirs})
  if(NOT TARGET tests.unit.${subdir})
    pika_algorithms_add_pseudo_target(tests.unit.${subdir})
  endif()
  add_subdirectory(${subdir})
  pika_algorithms_add_pseudo_dependencies(tests.unit tests.unit.${subdir})
endforeach()
