#!/bin/bash

DIR=curl-7.64.0
FILE=${DIR}.tar.gz

cd src
if [ ! -f $FILE ]; then
   wget https://curl.haxx.se/download/${FILE} -O $FILE
fi

tar -xzf ${FILE}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk --with-libssl-prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk  --with-libssl-prefix=${HOME}/sdk
fi

make && make install
