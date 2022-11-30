# Copyright (c) 2013 Hartmut Kaiser
# Copyright (c) 2014 Thomas Heller
# Copyright (c) 2016 John Biddiscombe
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

function(pika_algorithms_add_config_define definition)
  target_compile_definitions(
    pika_algorithms_public_flags INTERFACE "${definition}"
  )
endfunction()
