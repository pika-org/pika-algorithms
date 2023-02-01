# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

string(TOLOWER "${CMAKE_BUILD_TYPE}" PYUTILS_BUILD_TYPE)

set(PYUTILS_COMPILER "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_VERSION}")

configure_file(pyutils/buildinfo.py.in pyutils/buildinfo.py)
