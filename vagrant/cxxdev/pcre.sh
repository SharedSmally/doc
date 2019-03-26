#!/bin/bash

DIR=pcre-8.43
FILE=${DIR}.tar.gz

cd src
if [ ! -f $FILE ]; then
   wget ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/${FILE} -O $FILE
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
