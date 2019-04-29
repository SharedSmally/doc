#!/bin/bash

DIR=grpc-1.19.1
FILE=${DIR}.tar.gz
SRC_FILE=v1.19.1.tar.gz

# Build: https://github.com/grpc/grpc/blob/v1.19.0/BUILDING.md
# Needs libcares.so from https://c-ares.haxx.se/
# from https://c-ares.haxx.se/download/c-ares-1.15.0.tar.gz
# export CPPFLAGS=-I~/sdk/include:${CPPFLAGS}
# export LDFLAGS=-L~/sdk/lib:${LDFLAGS}
#
# Needs gperftools from https://github.com/couchbase/gperftools

cd src
if [ ! -f $FILE ]; then
   wget https://github.com/grpc/grpc/archive/${SRC_FILE} -O $FILE
fi

tar -xzf ${FILE}
#export PKG_CONFIG_PATH=~/sdk/lib/pkgconfig
#export PATH=/home/vagrant/sdk/bin:${PATH}
#export LD_LIBRARY_PATH=/home/vagrant/sdk/lib:${LD_LIBRARY_PATH}

cd ${DIR}

make && make prefix=${HOME}/sdk install
