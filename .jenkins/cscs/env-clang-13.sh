# Copyright (c) 2020 ETH Zurich
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cxx_std="20"
clang_version="13.0.1"
boost_version="1.79.0"
hwloc_version="2.6.0"
pika_version="0.11.0"
spack_compiler="clang@${clang_version}"
spack_arch="cray-cnl7-broadwell"
stdexec_version="6510f5bd69cc03b24668f26eda3dd3cca7e81bb2"

spack_spec="pika-algorithms@main arch=${spack_arch} %${spack_compiler} cxxflags=-stdlib=libc++ cxxstd=${cxx_std} ^pika@${pika_version} cxxflags=-stdlib=libc++ malloc=system +stdexec ^boost@${boost_version} ^hwloc@${hwloc_version} ^stdexec@${stdexec_version}"

configure_extra_options+=" -DCMAKE_CXX_FLAGS=-stdlib=libc++"
configure_extra_options+=" -DPIKA_ALGORITHMS_WITH_CXX_STANDARD=${cxx_std}"
