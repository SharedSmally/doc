#!/bin/bash -e

#https://about.gitlab.com/install/#centos-7

# install and configure the necessary dependencies
sudo yum install -y curl policycoreutils-python openssh-server
sudo systemctl enable sshd
sudo systemctl start sshd
sudo firewall-cmd --permanent --add-service=http
sudo systemctl reload firewalld

# install Postfix to send notification emails. Need DNS for email server
sudo yum install postfix
sudo systemctl enable postfix
sudo systemctl start postfix

# add the GitLab package repository and install gitlab-ce
curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.rpm.sh | sudo bash
sudo EXTERNAL_URL="https://gitlab.cpw.com" yum install -y gitlab-ce

# browse to the hostname and login
# On your first visit, you'll be redirected to a password reset screen. Provide the password 
# for the initial administrator account and you will be redirected back to the login screen. 
# Use the default account's username root to login.
