#!/bin/bash

#xslt: needs xerces
DIR=xalan-c-1.11
FILE=xalan_c-1.11-src.tar.gz

# compile openssl
cd src
if [ ! -f $FILE ]; then
   wget ftp://ftp.osuosl.org/pub/apache/xalan/xalan-c/sources/${FILE} -O $FILE
fi

tar -xzf ${FILE}

export XERCESCROOT=~/sdk
export XALANCROOT=~/src/xalan-c-1.11/c

cd ${DIR}/c
./runConfigure -p linux -c gcc -x g++ -P "${HOME}/sdk" -C "--srcdir=${HOME}/src/xalan-c-1.11/c"

# ./configure --prefix=${HOME}/sdk

make && make install
