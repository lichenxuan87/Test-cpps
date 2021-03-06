#/bin/bash

######################
#Specify tool chain path and other environment variables
#####################
export TOOL_CHAIN_PATH=/home/saic/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux
export TOOL_PREFIX=arm-linux-gnueabihf-

export CC=${TOOL_CHAIN_PATH}/bin/${TOOL_PREFIX}gcc
export CXX=${TOOL_CHAIN_PATH}/bin/${TOOL_PREFIX}g++
export PKG_CONFIG=${TOOL_CHAIN_PATH}/bin/${TOOL_PREFIX}pkg-config

export SYSTEM_ROOT=/home/saic/IP31_4.0.0-R-1610311534
export PKG_CONFIG_PATH=${SYSTEM_ROOT}/usr/lib/pkgconfig
export TARGET_ARC=arm
