#!/bin/bash

cd Vision/tests/lib
./installGTest.sh

cd ../../..

mkdir depsInstall

cd depsInstall

###C++ VISION INSTALL###

#APT CONFIG#
sudo apt-add-repository universe
sudo apt-add-repository multiverse

sudo apt-get update

#BASE DEP#

sudo apt-get -y install libopencv-dev build-essential cmake git libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils libtiff5-dev libxine2-dev unzip

#wget -O boost-1.62.zip 'http://downloads.sourceforge.net/project/boost/boost/1.62.0/boost_1_62_0.zip?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.62.0%2F&ts=1482524403&use_mirror=pilotfiber'

#unzip boost-1.62.zip
#cd boost_1_62_0

#./bootstrap.sh

#sudo ./b2 -j$(nproc) install

#cd ..

#BOOST#

sudo apt-get -y install libboost-all-dev #We can install a suitable version of boost from apt (much faster)

#OPENCV#
if [ ! -f /usr/local/lib/libopencv_core.so.3.1 ]; then #If the opencv >3.1< core module isn't there
wget https://github.com/Itseez/opencv/archive/3.1.0.zip

unzip 3.1.0.zip
cd opencv-3.1.0

mkdir build
cd build

cmake -DWITH_CUDA=ON -DCUDA_ARCH_BIN="3.2" -DCUDA_ARCH_PTX="" -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF ..
sudo make -j4 install

cd ../..
else
echo "----OPENCV FOUND, NOT INSTALLING----"
fi

#LIBZMQ#
if [ ! -f /usr/local/lib/libzmq.so ]; then
git clone https://github.com/zeromq/libzmq
cd libzmq

mkdir build
cd build

cmake ..
sudo make -j4 install

cd ../..
else
echo "----LIBZMQ FOUND, NOT INSTALLING----"
fi

sudo apt-get -y install libzmq-dev

#CPPZMQ#
if [ ! -f /usr/local/include/zmq.hpp ]; then
git clone https://github.com/zeromq/cppzmq

cd cppzmq

sudo cp zmq.hpp /usr/local/include
sudo cp zmq_addon.hpp /usr/local/include

cd ..
else
echo "----CPPZMQ FOUND, NOT INSTALLING----"
fi

#ZHELPERS#
if [ ! -f /usr/local/include/zhelpers.hpp ]; then
git clone https://github.com/booksbyus/zguide

cd zguide/examples/C++

sudo cp zhelpers.hpp /usr/local/include

cd ../../..
else
echo "----ZHELPERS FOUND, NOT INSTALLING----"
fi

#V4L2#

sudo apt-get -y install v4l-utils

sudo ldconfig #Refresh everything

###END C++ VISION INSTALL###