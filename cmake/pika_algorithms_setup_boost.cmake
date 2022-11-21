# Copyright (c) 2018 Christopher Hinz
# Copyright (c) 2014 Thomas Heller
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(NOT TARGET Boost::boost)
  # Add additional version to recognize
  # cmake-format: off
  set(Boost_ADDITIONAL_VERSIONS
      ${Boost_ADDITIONAL_VERSIONS}
      "1.81.0" "1.81"
      "1.80.0" "1.80"
      "1.79.0" "1.79"
      "1.78.0" "1.78"
      "1.77.0" "1.77"
      "1.76.0" "1.76"
      "1.75.0" "1.75"
      "1.74.0" "1.74"
      "1.73.0" "1.73"
      "1.72.0" "1.72"
      "1.71.0" "1.71"
  )
  # cmake-format: on
  set(Boost_MINIMUM_VERSION
      "1.71"
      CACHE INTERNAL "1.71" FORCE
  )

  set(Boost_NO_BOOST_CMAKE ON) # disable the search for boost-cmake

  # Find the headers and get the version
  find_package(Boost ${Boost_MINIMUM_VERSION} REQUIRED)
  if(NOT Boost_VERSION_STRING)
    set(Boost_VERSION_STRING
        "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}"
    )
  endif()
endif()
