#!/bin/bash

#needs Python.h
# only install to system

DIR=libxml2-2.9.9
FILE=${DIR}.tar.gz

# compile c libxml2
cd src
if [ ! -f $FILE ]; then
   wget ftp://xmlsoft.org/libxml2/${FILE} -O $FILE
fi

tar -xzf ${FILE}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk --without-python
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk --without-python
fi

make && make install
