# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cxx_std="17"
gcc_version="9.3.0"
boost_version="1.71.0"
hwloc_version="1.11.5"
pika_version="main"
spack_compiler="gcc@${gcc_version}"
spack_arch="cray-cnl7-broadwell"

spack_spec="pika-algorithms@main arch=${spack_arch} %${spack_compiler} cxxstd=${cxx_std} ^pika@${pika_version} +generic_coroutines malloc=system ^boost@${boost_version} ^hwloc@${hwloc_version}"

configure_extra_options+=" -DPIKA_ALGORITHMS_WITH_CXX_STANDARD=${cxx_std}"

build_extra_options+=" -j10"
