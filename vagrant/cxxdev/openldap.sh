#!/bin/bash

DIR=openldap-2.4.47
FILE=${DIR}.tgz

# needs BDB/HDB
cd src
if [ ! -f $FILE ]; then
   wget ftp://ftp.openldap.org/pub/OpenLDAP/openldap-release/${FILE} -O $FILE
fi

tar -xzf ${FILE}

cd ${DIR}
if [ -f ./config ]; then
  ./config --prefix=${HOME}/sdk --with-libssl-prefix=${HOME}/sdk --disable-slapd --disable-slurpd
fi

if [ -f ./configure ]; then
  ./configure --prefix=${HOME}/sdk  --with-libssl-prefix=${HOME}/sdk --disable-slapd --disable-slurpd
fi

make && make install
