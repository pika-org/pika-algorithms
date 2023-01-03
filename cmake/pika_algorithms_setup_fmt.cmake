# Copyright (c) 2022 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(PIKA_ALGORITHMS_WITH_TESTS OR PIKA_ALGORITHMS_WITH_EXAMPLES)
  pika_algorithms_find_package(fmt 9.0.0 REQUIRED)
endif()
