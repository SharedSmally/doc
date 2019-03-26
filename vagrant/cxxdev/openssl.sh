#!/bin/bash

DIR=openssl-1.1.1b
FILE=${DIR}.tar.gz

# compile openssl
cd src
if [ ! -f $FILE ]; then
   wget https://www.openssl.org/source/${FILE} -O $FILE
fi

tar -xzf ${FILE}

cd ${DIR}
./config --prefix=${HOME}/sdk
make && make install

# Install to system
#sudo yum install openssl -y
#sudo yum install openssl-devel -y
#./config --prefix=/usr/local/openssl --openssldir=/usr/local/openssl shared zlib
#make && make test && make install
#sudo vi /etc/profile.d/openssl.sh
