#!/bin/bash

DIR=expat-2.2.6
FILE=${DIR}.tar.bz2
TAR_FILE=${DIR}.tar

cd src
if [ ! -f $FILE ]; then
   wget https://github.com/libexpat/libexpat/releases/download/R_2_2_6/${FILE} -O $FILE
fi

bunzip2 ${FILE}
tar -xf ${TAR_FILE}
bzip2  ${TAR_FILE}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk
fi

make && make install
