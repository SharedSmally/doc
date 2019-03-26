#!/bin/bash

DIR=unixODBC-2.3.7
FILE=${DIR}.tar.gz

# compile openssl
cd src
if [ ! -f $FILE ]; then
   wget http://www.unixodbc.org/${FILE} -O $FILE
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
