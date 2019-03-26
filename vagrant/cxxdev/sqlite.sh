#!/bin/bash

DIR=sqlite-autoconf-3270200
FILE=${DIR}.tar.gz
SRC_FILE=sqlite-autoconf-3270200.tar.gz

cd src
if [ ! -f $FILE ]; then
   wget https://www.sqlite.org/2019/${SRC_FILE} -O $FILE
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
