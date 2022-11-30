# Copyright (c) 2020 Kor de Jong
# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# This project tests that pika-algorithms can be built using FetchContent. It is
# built by the .github/workflows/linux_fetchcontent.yml GitHub actions workflow.

cmake_minimum_required(VERSION 3.18)
project(pika-fetchcontent LANGUAGES CXX)

# Test that pika correctly handles having Boost Filesystem and ProgramOptions
# found before setting up pika, if they are available (do not REQUIRE these)
find_package(Boost COMPONENTS filesystem program_options)

include(FetchContent)

fetchcontent_declare(
  pika-algorithms
  GIT_REPOSITORY ${PIKA_ALGORITHMS_REPOSITORY}
  GIT_TAG ${PIKA_ALGORITHMS_TAG}
)
fetchcontent_getproperties(pika-algorithms)
if(NOT pika-algorithms_POPULATED)
  fetchcontent_populate(pika-algorithms)
  add_subdirectory(${pika-algorithms_SOURCE_DIR} ${pika-algorithms_BINARY_DIR})
endif()
