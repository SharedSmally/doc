#!/bin/bash

DIR=xerces-c-3.2.2
FILE=${DIR}.tar.gz

# compile openssl
cd src
if [ ! -f $FILE ]; then
   wget http://mirror.olnevhost.net/pub/apache//xerces/c/3/sources/${FILE} -O $FILE
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
