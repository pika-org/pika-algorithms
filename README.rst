..
    Copyright (c) 2022 ETH Zurich

    SPDX-License-Identifier: BSL-1.0
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

|bors_enabled|
|circleci_status|
|github_actions_linux_debug_status|
|github_actions_linux_hip_status|
|github_actions_linux_sanitizers_status|
|github_actions_macos_debug_status|
|codacy|
|codacy_coverage|

===============
pika-algorithms
===============

pika-algorithms is a C++ library containing parallel algorithms built on top of
`pika <https://github.com/pika-org/pika>`_. **pika-algorithms is mostly in
maintenance mode**. The intention is to replace the algorithms based on a
generic implementation built on  `P2300 <https://wg21.link/p2300>`_.

Dependencies
============

pika-algorithms requires:

* a C++17-capable compiler:

  * `GCC <https://gcc.gnu.org>`_ 9 or greater
  * `clang <https://clang.llvm.org>`_ 11 or greater
  * MSVC may work but it is not tested

* `CMake <https://cmake.org>`_ 3.22.0 or greater
* `pika <https://github.com/pika-org/pika>`_ 0.11.0 or greater

The following are required for tests and examples:

* `header-only Boost <https://boost.org>`_ 1.71.0 or greater
* `fmt <https://fmt.dev/latest/index.html>`_

Documentation
=============

Documentation is a work in progress. The following headers are part of the
public API. Any other headers are internal implementation details.

- ``pika/algorithm.hpp``
- ``pika/memory.hpp``
- ``pika/numeric.hpp``

.. |bors_enabled| image:: https://bors.tech/images/badge_small.svg
     :target: https://app.bors.tech/repositories/57076
     :alt: Bors enabled

.. |circleci_status| image:: https://circleci.com/gh/pika-org/pika-algorithms/tree/main.svg?style=svg
     :target: https://circleci.com/gh/pika-org/pika-algorithms/tree/main
     :alt: CircleCI

.. |github_actions_linux_debug_status| image:: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_debug.yml/badge.svg
     :target: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_debug.yml
     :alt: Linux CI (Debug)

.. |github_actions_linux_hip_status| image:: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_hip.yml/badge.svg
     :target: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_hip.yml
     :alt: Linux CI (HIP, Debug)

.. |github_actions_linux_sanitizers_status| image:: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_sanitizers.yml/badge.svg
     :target: https://github.com/pika-org/pika-algorithms/actions/workflows/linux_sanitizers.yml
     :alt: Linux CI (asan/ubsan)

.. |github_actions_macos_debug_status| image:: https://github.com/pika-org/pika-algorithms/actions/workflows/macos_debug.yml/badge.svg
     :target: https://github.com/pika-org/pika-algorithms/actions/workflows/macos_debug.yml
     :alt: macOS CI (Debug)

.. |codacy| image:: https://api.codacy.com/project/badge/Grade/e03f57f1c4cd40e7b514e552a723c125
     :target: https://www.codacy.com/gh/pika-org/pika
     :alt: Codacy

.. |codacy_coverage| image:: https://api.codacy.com/project/badge/Coverage/e03f57f1c4cd40e7b514e552a723c125
     :target: https://www.codacy.com/gh/pika-org/pika
     :alt: Codacy coverage
