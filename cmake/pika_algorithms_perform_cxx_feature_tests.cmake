# Copyright (c) 2007-2017 Hartmut Kaiser
# Copyright (c) 2011-2014 Thomas Heller
# Copyright (c) 2013-2016 Agustin Berge
# Copyright (c)      2017 Taeguk Kwon
# Copyright (c)      2020 Giannis Gonidelis
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# ##############################################################################
# C++ feature tests
# ##############################################################################
function(pika_algorithms_perform_cxx_feature_tests)
  pika_algorithms_check_for_cxx17_std_transform_scan(
    DEFINITIONS PIKA_ALGORITHMS_HAVE_CXX17_STD_TRANSFORM_SCAN_ALGORITHMS
  )

  pika_algorithms_check_for_cxx17_std_scan(
    DEFINITIONS PIKA_ALGORITHMS_HAVE_CXX17_STD_SCAN_ALGORITHMS
  )

  pika_algorithms_check_for_std_experimental_simd(
    DEFINITIONS PIKA_ALGORITHMS_HAVE_STD_EXPERIMENTAL_SIMD
    PIKA_ALGORITHMS_HAVE_DATAPAR
  )

  pika_algorithms_check_for_cxx20_std_ranges_iter_swap(
    DEFINITIONS PIKA_ALGORITHMS_HAVE_CXX20_STD_RANGES_ITER_SWAP
  )
endfunction()
