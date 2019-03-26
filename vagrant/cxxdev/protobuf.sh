#!/bin/bash

sudo yum install autoconf automake libtool unzip gcc-c++ git -y
git clone https://github.com/google/protobuf.git
cd protobuf

# Generate and then run the configuration
./autogen.sh
./configure

# Build and test
make
make check

# Install Protobuf
sudo make install
sudo ldconfig

# Verify Installation
export LD_LIBRARY_PATH=/usr/local/lib
protoc --version
