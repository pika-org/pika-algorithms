# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cxx_std="17"
cce_version="12.0.3"
boost_version="1.78.0"
hwloc_version="2.0.3"
pika_version="main"
spack_compiler="cce@${cce_version}"
spack_arch="cray-cnl7-broadwell"

spack_spec="pika-algorithms@main arch=${spack_arch} %${spack_compiler} cxxstd=${cxx_std} ^pika@${pika_version} malloc=system ^boost@${boost_version} ^cray-mpich ^hwloc@${hwloc_version}"

configure_extra_options+=" -DPIKA_ALGORITHMS_WITH_CXX_STANDARD=${cxx_std}"
