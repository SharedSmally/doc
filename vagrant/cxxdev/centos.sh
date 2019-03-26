#!/bin/bash -e


# update centos and install basic packages
function update {
   sudo yum update -y
   sudo yum install -y wget
   sudo yum install -y git
   sudo yum install -y java-1.8.0-openjdk-devel
   mkdir sdk
}

function install_java {
   #Install OpenJDK 8 JRE
   #sudo yum install -y java-1.8.0-openjdk

   #Install OpenJDK 8 JDK
   sudo yum install -y java-1.8.0-openjdk-devel

   #Install OpenJDK 11 JDK
   #install_jdk11
}

function install_jdk11 {
   curl -O https://download.java.net/java/GA/jdk11/13/GPL/openjdk-11.0.1_linux-x64_bin.tar.gz
   tar zxvf openjdk-11.0.1_linux-x64_bin.tar.gz
   sudo mv jdk-11.0.1 /usr/local/
   #copy jdk11.sh to /etc/profile.d/jdk11.sh
}


###############################
#update
sudo yum install autoconf automake libtool unzip gcc-c++ -y
yum install -y python-devel
# for /usr/include/json.hpp and
#    /usr/include/nlohmann/json.hpp
yum install -y json-devel
###############################
