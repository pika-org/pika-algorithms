# Copyright (c) 2022 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

pika_algorithms_find_package(pika 0.12.0 REQUIRED)

if(NOT PIKA_ALGORITHMS_FIND_PACKAGE)
  target_link_libraries(pika_algorithms_base_libraries INTERFACE pika::pika)
endif()
