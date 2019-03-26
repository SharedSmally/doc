#!/bin/bash

DIR=openldap-2.4.47
FILE=${DIR}.tgz

# needs BDB/HDB
cd src
if [ ! -f $FILE ]; then
   wget http://download.oracle.com/otn/berkeley-db/db-18.1.32.tar.gz/${FILE} -O $FILE
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
