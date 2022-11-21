# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cxx_std="20"
clang_version="14.0.6"
boost_version="1.79.0"
hwloc_version="2.7.0"
cuda_version="11.5.0"
pika_version="main"
spack_compiler="clang@${clang_version}"
spack_arch="cray-cnl7-haswell"

spack_spec="pika-algorithms@main arch=${spack_arch} %${spack_compiler} cxxstd=${cxx_std} ^pika@${pika_version} +cuda cuda_arch=60 malloc=system +p2300 ^boost@${boost_version} ^cuda@${cuda_version} +allow-unsupported-compilers ^hwloc@${hwloc_version}"

configure_extra_options+=" -DPIKA_ALGORITHMS_WITH_CXX_STANDARD=${cxx_std}"
configure_extra_options+=" -DCMAKE_CUDA_COMPILER=c++"

# TODO
# The build unit test with pika in Debug and the hello_world project in Debug
# mode hangs on this configuration. Release-Debug, Debug-Release, and
# Release-Release do not hang.
# configure_extra_options+=" -DPIKA_ALGORITHMS_WITH_TESTS_EXTERNAL_BUILD=OFF"
