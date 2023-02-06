#!/bin/bash

#
#   适用环境  ubuntu20.4
#

source /etc/profile

echo "
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse" >>/etc/apt/sources.list

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install adb -y

sudo apt-get install rar -y

sudo apt-get install vim -y

sudo apt-get install tree -y

sudo apt-get install xvfb -y

sudo apt-get install wget -y

sudo apt-get install nginx -y

sudo apt-get install apt-file -y

sudo apt-get install terminator -y

sudo apt-get install imagemagick -y

sudo apt-get gcc g++ gcc-10 g++-10 -y

sudo apt-get install libopencv-dev -y

sudo apt-get install git gitk gitg -y

sudo apt-get install openssh-server -y

sudo apt-get install libyaml-cpp-dev -y

sudo apt-get install libusb-1.0-0-dev -y

sudo apt-get install libmemcached-dev -y

sudo apt-get install libtokyocabinet-dev -y

sudo apt-get install redis-tools redis-server -y

sudo apt-get install cmake make automake autoconf -y

sudo apt-get install libgflags-dev libgoogle-glog-dev -y

sudo apt-get install libatlas-base-dev libsuitesparse-dev -y

sudo apt-get install gfortran libgtk-3-dev libavresample-dev -y

sudo apt-get install mysql-server mysql-client libmysqlcppconn-dev -y

sudo apt-get install libbz2-dev libegl1-mesa-dev libwayland-dev libxkbcommon-dev wayland-protocols -y

sudo apt-get install yasm libvpx-dev libopus-dev libfdk-aac-dev libmp3lame-dev libx265-dev libnuma-dev -y

sudo apt-get ffmpeg libglew-dev intel-mkl-full libsuitesparse-dev libpcl-dev -y
