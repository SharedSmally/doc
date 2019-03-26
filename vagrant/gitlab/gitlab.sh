#!/bin/bash -e

#https://www.tecmint.com/install-and-configure-gitlab-on-centos-7/
#https://about.gitlab.com/install/#centos-7

sudo yum update -y

###################################################
# update centos and install basic packages
function installHttpSsh {
   sudo yum install -y curl policycoreutils-python openssh-server
   sudo systemctl enable sshd
   sudo systemctl start sshd
   sudo firewall-cmd --permanent --add-service=http
   sudo systemctl reload firewalld
}

function installPostfix {
   sudo yum install -y postfix
   sudo systemctl enable postfix
   sudo systemctl start postfix
}

function installGitlab {
   curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.rpm.sh | sudo bash
   sudo EXTERNAL_URL="https://gitlab.example.com" yum install -y gitlab-ce
}
#######################################################

#installHttpSsh
installPostfix
installGitlab
