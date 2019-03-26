#!/bin/bash

function autoconfig {
   libtoolize --force
   aclocal
   autoheader
   automake --force-missing --add-missing
   autoconf
}

DIR=googletest-release-1.8.1
FILE=googletest-1.8.1.tar.gz

# release: https://github.com/google/googletest/releases
cd src
if [ ! -f $FILE ]; then
   wget https://github.com/google/googletest/archive/release-1.8.1.tar.gz -O $FILE
fi

tar -xzf ${FILE}

# need to run autoconfig in googletest/ and googlemock/
cd ${DIR}
cd googletest && autoconfig
cd ../googlemock && autoconfig
cd ../ && autoconfig

if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk
fi

make

#make && make install
#make install' is dangerous and not supported
