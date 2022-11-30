# Copyright (c) 2019 Mikael Simberg
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# These are a dummy targets that we add compile flags to. All pika-algorithms
# targets should link to them.
add_library(pika_algorithms_private_flags INTERFACE)
add_library(pika_algorithms_public_flags INTERFACE)

# Set other flags that should always be set

# PIKA_ALGORITHMS_DEBUG must be set without a generator expression as it
# determines ABI compatibility. Projects in Release mode using pika-algorithms
# in Debug mode must have PIKA_ALGORITHMS_DEBUG set, and projects in Debug mode
# using pika-algorithms in Release mode must not have PIKA_ALGORITHMS_DEBUG set.
# PIKA_ALGORITHMS_DEBUG must also not be set by projects using pika-algorithms.
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  target_compile_definitions(
    pika_algorithms_private_flags INTERFACE PIKA_ALGORITHMS_DEBUG
  )
  target_compile_definitions(
    pika_algorithms_public_flags INTERFACE PIKA_ALGORITHMS_DEBUG
  )
endif()

target_compile_definitions(
  pika_algorithms_private_flags
  INTERFACE $<$<CONFIG:MinSizeRel>:NDEBUG>
  INTERFACE $<$<CONFIG:Release>:NDEBUG>
  INTERFACE $<$<CONFIG:RelWithDebInfo>:NDEBUG>
)

# Remaining flags are set through the macros in
# cmake/pika_algorithms_add_compile_flag.cmake

include(pika_algorithms_export_targets)
# Modules can't link to this if not exported
install(
  TARGETS pika_algorithms_private_flags
  EXPORT pika_algorithms_internal_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT pika_algorithms_private_flags
)
install(
  TARGETS pika_algorithms_public_flags
  EXPORT pika_algorithms_internal_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT pika_algorithms_public_flags
)
pika_algorithms_export_internal_targets(pika_algorithms_private_flags)
pika_algorithms_export_internal_targets(pika_algorithms_public_flags)
