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
     sudo yum install epel-release -y
     sudo yum groupinstall -y "Development Tools"  # includ gcc,g++,make,.... kernel needs perl

     sudo yum install -y binutils bison flex 
     sudo yum install -y gcc gcc-c++ gdb glibc-devel 
     sudo yum install -y make libtool autoconf automake git cmake pkgconfig
     sudo yum install -y python3 python3-devel
     sudo pip3 install meson  # implemented in python3
     sudo yum install -y ninja-build  #1.7.2
     sudo yum install -y http://repo.okay.com.mx/centos/7/x86_64/release/ninja-build-1.8.2-1.el7.x86_64.rpm
     sudo yum install -y man-pages
  SHELL
```
- centos version
```
$hostnamectl

yum install kernel-devel kernel-headers  #(need to update perl)
yum install -y kernel-devel-`uname -r` --enablerepo=C*-base --enablerepo=C*-updates: Unknow repo C*-base
```

## Libs:
- gcc: c/c++(https://gcc.gnu.org/): depends on ftp://gcc.gnu.org/pub/gcc/infrastructure:
    - GMP: GNU Multiple Precision Arithmetic Library
    - MPFR: GNU Multiple-precision floating-point rounding library
    - MPC: GNU Multiple-precision C library
    - ELF: Executable and Linkable Format library
    - PPL: Parma Polyhedra Library (optional, for memory optimizations)
```
git clone git://gcc.gnu.org/git/gcc.git

```
- glib: git clone  https://gitlab.gnome.org/GNOME/glib.git
```
sudo yum install -y glib glib-devel: 1.2.0
sudo yum install -y glib2 glib2-devel: 2.56.0 (need pcre)

     meson --prefix /home/user/pkgs _build        
     meson compile -C _build
     meson test -C _build
     meson install -C _build

$ cd /path/to/source/root
$ meson --prefix /usr --buildtype=plain builddir -Dc_args=... -Dcpp_args=... -Dc_link_args=... -Dcpp_link_args=...
$ meson compile -C builddir
$ meson test -C builddir
$ DESTDIR=/home/vagrant/pkgs meson install -C build
```     
- gstream: https://github.com/GStreamer/gstreamer.git
    - https://github.com/GStreamer
    - [Build](https://gstreamer.freedesktop.org/documentation/installing/building-from-source-using-meson.html?gi-language=c)
    - [meson buildin options](https://mesonbuild.com/Builtin-options.html)
```
    meson build
    ninja -C build
```
- ssh:
- 
