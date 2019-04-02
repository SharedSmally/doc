#!/bin/bash

DIR=hiredis-0.14.0
FILE=${DIR}.tar.gz
SRC_FILE=v0.14.0.tar.gz

# Release:  https://github.com/redis/hiredis/releases
#

cd src
if [ ! -f $FILE ]; then
   wget https://github.com/redis/hiredis/archive/${SRC_FILE} -O $FILE
fi

tar -xzf ${FILE}
export PKG_CONFIG_PATH=~/sdk/lib/pkgconfig
#export PATH=/home/vagrant/sdk/bin:${PATH}
#export LD_LIBRARY_PATH=/home/vagrant/sdk/lib:${LD_LIBRARY_PATH}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk
fi

make && make PREFIX=${HOME}/sdk install
