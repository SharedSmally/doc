#!/bin/bash -e

# update centos and install basic packages
function update {
   sudo yum update -y
   sudo yum install -y wget
   sudo yum install -y git
   sudo yum install -y java-1.8.0-openjdk-devel
}

#######################################
update
#######################################
