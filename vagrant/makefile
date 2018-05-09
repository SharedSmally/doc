main:

init:Vagrantfile

start:
        vagrant.exe up;

stop:
        vagrant.exe halt

login:
        vagrant.exe ssh

update:
        vagrant.exe provision

Vagrantfile:
        vagrant.exe init
        sed -i "s/base/centos\/7/" $@

clean:
        rm -rf Vagrantfile
###########################
# vi Vagrantfile
#config.vm.synced_folder "C:\\MySpace", "/myspace"

# For debian
config.vm.provision "shell", inline: <<-SHELL
   apt-get update
   apt-get install -y apache2
SHELL
# For Redhat
config.vm.provision "shell", inline: <<-SHELL
   yum update
   yum install -y git
SHELL
  
###########################
## cd /opt && tar -xzf /myspace/src/jdk-10.0.1_linux-x64_bin.tar.gz && ln -s jdk-10.0.1 jdk
# /etc/bashrc
# /etc/profile.d
#
# # vi /etc/profile.d/java.sh
# [ -d /opt/jdk ] && export JDK_HOME="/opt/jdk" && export PATH=${JDK_HOME}/bin:${PATH}
###########################
