#!/bin/bash
NAME=libevent
VERSION=2.1.8
FILE=${NAME}.tar.gz
DIR=libevent-${VERSION}-stable

# libevent
# http://libevent.org/

cd src
if [ ! -f $FILE ]; then
   wget https://github.com/libevent/libevent/releases/download/release-${VERSION}-stable/libevent-${VERSION}-stable.tar.gz -O $FILE
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
