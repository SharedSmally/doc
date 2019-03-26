#!/bin/bash

DIR=c-ares-1.15.0
FILE=${DIR}.tar.gz
SRC_FILE=${FILE}

# async name resolve: required by grpc

cd src
if [ ! -f $FILE ]; then
   wget https://c-ares.haxx.se/download/${SRC_FILE} -O $FILE
fi

tar -xzf ${FILE}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk
fi

make && make install
