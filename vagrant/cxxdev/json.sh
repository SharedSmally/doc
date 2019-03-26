#!/bin/bash

# compile openssl
#1. Install json-devel
#2. Include "json.hpp" in any C++ file
#3. Compile "g++ -std=c++11 mytest.cpp"

DIR=json-v3.6.1
FILE=${DIR}.tar.gz

# compile openssl
cd src
if [ ! -f $FILE ]; then
   wget https://github.com/nlohmann/json/releases/download/v3.6.1/include.zip -O $FILE
fi

unzip ${FILE} -d ~/sdk
