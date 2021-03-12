# Development env setup for centos using vagrant

## Vagrant in Ubuntu
- Using VirtualBox (default)
```
$sudo apt-get install virtualbox  #install virtualbox and virtualbox-qt
```
- Using libvirt
```
Installed KVM, Libvirt and QEMU-KVM
$sudo apt install qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils
$sudo systemctl start libvirtd
$sudo systemctl enable libvirtd
$sudo systemctl status libvirtd

Installing libvirt plugin for Vagrant
$ vagrant plugin install vagrant-libvirt
```

## [centos](https://www.centos.org/):[ Linux Release](https://www.centos.org/centos-linux/)
- centos/7 or centos/8
- Install Development Tools:
```
  config.vm.box = "centos/7"
  config.vm.box = "centos/8"
  
  config.vm.provision "shell", inline: <<-SHELL
     sudo yum update -y
     sudo yum install groupinstall "Development Tools"  # includ gcc,g++,make,.... kernel needs perl
     sudo yum install -y binutils bison flex 
     sudo yum install -y gcc gcc-c++ gdb glibc-devel 
     sudo yum install -y make libtool autoconf automake git cmake
     sudo yum install -y man-pages
  SHELL
```

## Libs:
- glib: git clone  https://gitlab.gnome.org/GNOME/glib.git
- ssh:
- 
