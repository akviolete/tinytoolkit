#!/usr/bin/env bash

####################################################################################################

#
# 脚本路径
#
CoreSourcePath=$(cd $(dirname $0) && pwd)

#
# Android NDK 路径
#
ANDROID_NDK=/home/${USER}/software/android-ndk-r21e

#
# 编译安装路径
#
TOOLKIT_INSTALL_PREFIX_LINUX=/home/${USER}/software/akviolet/tinyToolkit
TOOLKIT_INSTALL_PREFIX_ANDROID=/home/${USER}/software/android/akviolet/tinyToolkit

####################################################################################################

#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m[kToolkit] Start build project\033[0m"
echo -e ""

####################################################################################################

#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m---------- fmt ----------\033[0m"
echo -e ""

####################################################################################################

#
# Linux 创建并进入目录
#
cd ${CoreSourcePath}/tinyToolkit/3rd/fmt

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#

make -j8 && make install

#
# Android 创建并进入目录
#
cd ${CoreSourcePath}/tinyToolkit/3rd/fmt

mkdir build_android && cd build_android

#
# 生成make
#
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_SYSTEM_NAME=Android \
  -DCMAKE_SYSTEM_VERSION=26 \
  -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
  -DCMAKE_ANDROID_NDK=${ANDROID_NDK} \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_ANDROID}

#
# 编译安装
#
make -j8 && make install

####################################################################################################

#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m---------- tinyToolkit ----------\033[0m"
echo -e ""

####################################################################################################

#
# Linux 创建并进入目录
#

cd ${CoreSourcePath}/tinyToolkit

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake ../ \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#
make -j8 && make install

####################################################################################################

#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m---------- tinyToolkit-extra ----------\033[0m"
echo -e ""

####################################################################################################

#
# Linux 创建并进入目录
#
cd ${CoreSourcePath}/tinyToolkit-extra

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake ../ \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#
make -j8 && make install

####################################################################################################
#
# 输出信息
#
echo -e ""
echo -e "\033[1m\033[36m[linux_64] End build project\033[0m"
echo -e ""

####################################################################################################

