#!/bin/bash
#
#librdkafka - the Apache Kafka C/C++ client library
# https://github.com/edenhill/librdkafka
# Release: https://github.com/edenhill/librdkafka/releases
#
DIR=librdkafka-1.0.0
FILE=${DIR}.tar.gz
SRC_FILE=v1.0.0.tar.gz

cd src
if [ ! -f $FILE ]; then
   wget https://github.com/edenhill/librdkafka/archive/${SRC_FILE} -O $FILE
fi

tar -xzf ${FILE}
export PKG_CONFIG_PATH=~/sdk/lib/pkgconfig
#export PATH=/home/vagrant/sdk/bin:${PATH}
#export LD_LIBRARY_PATH=/home/vagrant/sdk/lib:${LD_LIBRARY_PATH}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk
fi

make && make prefix=/~/sdk install
