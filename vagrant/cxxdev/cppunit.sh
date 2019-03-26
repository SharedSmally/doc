#!/bin/bash


DIR=cppunit-1.14.0
FILE=${DIR}.tar.gz

cd src
#wget http://dev-www.libreoffice.org/src/${FILE} -O $FILE
if [ ! -f $FILE ]; then
   wget https://src.fedoraproject.org/lookaside/extras/cppunit/cppunit-1.14.0.tar.gz/sha512/4ea1da423c6f7ab37e4144689f593396829ce74d43872d6b10709c1
ad5fbda4ee945842f7e9803592520ef81ac713e95a3fe130295bf048cd32a605d1959882e/${FILE} -O $FILE
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
