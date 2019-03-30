#!/bin/bash -e
#
# https://linuxize.com/post/how-to-install-jenkins-on-centos-7/
#
# Install JDK
sudo yum install java-1.8.0-openjdk-devel

# enable the Jenkins repository
curl --silent --location http://pkg.jenkins-ci.org/redhat-stable/jenkins.repo | sudo tee /etc/yum.repos.d/jenkins.repo
sudo rpm --import https://jenkins-ci.org/redhat/jenkins-ci.org.key

# install the latest stable version of Jenkins:
sudo yum install jenkins -y

# start the Jenkins service with:
sudo systemctl start jenkins

# check whether it started successfully run:
systemctl status jenkins

# enable the Jenkins service to start on system boot.
sudo systemctl enable jenkins
