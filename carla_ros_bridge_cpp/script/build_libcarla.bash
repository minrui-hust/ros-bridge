#!/bin/bash

LIBCARLA_BUILD_DIR=$1

# Check if we have build it already
cd ${LIBCARLA_BUILD_DIR}
if [ ! -f "build.ninja" ]; then
    cd ${CARLA_ROOT} && make setup && cd ${LIBCARLA_BUILD_DIR}
    cmake\
    -G "Ninja"\
    -DCMAKE_BUILD_TYPE=Client\
    -DLIBCARLA_BUILD_RELEASE=ON\
    -DLIBCARLA_BUILD_DEBUG=OFF\
    -DLIBCARLA_BUILD_TEST=OFF\
    -DCMAKE_TOOLCHAIN_FILE=${LIBCARLA_BUILD_DIR}/toolchain.cmake\
    -DCMAKE_INSTALL_PREFIX=${LIBCARLA_BUILD_DIR}/install\
    ${CARLA_ROOT}
    ninja && ninja install
fi