#!/bin/bash

# Need to install openssl devel
#sudo yum install openssl-devel -y
$

DIR=libssh2-1.8.2
FILE=${DIR}.tar.gz

cd src
if [ ! -f $FILE ]; then
   wget https://www.libssh2.org/download/${FILE} -O $FILE
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
