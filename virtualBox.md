## Network typs for Guest VM:
  - NAT - Host act as a router to map Host port to Guest port. Need DHCP server: Setting: HostIP=127.0.0.1/port; Guess IP=emppty/port
  - Bridged: Guest get a ip address on the same subnet as host. Bind to host NIC; Accessible from the out-side 
  - Host Only: Can connect to the guest servers from the host only (private). Need DHCP server.
  - Internal Network: - VMs can connect each other within the same internal network. no connection between host and guest. Need DHCP server.

## List NICs
- ifconfig -a(Solaris);  ipconfig (Windows); ip (linux)
- ip link show;  
- ip link set [name] up
   name: Two character prefixes based on the type of interface:
   - en -- ethernet;  enp0s10, ... 
   - sl -- serial line IP (slip)
   - wl -- wlan
   - ww -- wwan
 
## Ubuntu network config
 - ifconfig
 - sudo vi /etc/network/interfaces
```   
   auto enp0sx
   iface enp0sx inet dhcp
```   
 - sudo ifup/ifdown enp0sx
 - NAT: ip=10.0.2.15
```  
   NAT port froward: Host:127.0.0.1; HostPort:xxx;  GuestIP:10.0.2.15; GuestPort:22 (SSH)    
   ssh user@127.0.0.1 -p HostPort
```   
 - sudo /etc/init.d/networking restart
 
## Install package
- sudo add-apt-repository ppa:ubuntu-toolchain-r/test
- sudo apt-get update
- sudo apt-get install g++

## Init
- /etc/init.d:  init services
- /etc/init/: init.d configurations

## systemctl


## Shared Folder
- [Setup](http://askubuntu.com/questions/161759/how-to-access-a-shared-folder-in-virtualbox)
  - Install VBox Guest Additions  and Add user in vboxsf
```
sudo mount /dev/cdrom /media/cdrom
sudo apt-get install make gcc linux-headers-$(uname -r)
sudo /media/cdrom/VBoxLinuxAdditions.run
sudo usermod -a -G vboxsf $USER

mkdir /home/<user>/vboxshare
sudo mount -t vboxsf -o uid=1000,gid=1000 share /home/<user>/vboxshare
```
- Automated
shared folders will automatically be mounted in the guest with mount point /media/sf_<name_of_folder>. To have access to these folders users in the guest need to be a member of the group vboxsf

## Ubuntu BASH 
- /bin/bash:      The bash executable
- /etc/profile:   The systemwide initialization file, executed for login shells:  Add /etc/profile.d/*.sh
- /etc/bash.bashrc: The systemwide per-interactive-shell startup file
- /etc/bash.bash.logout:   The systemwide login shell cleanup file, executed when a login shell exits
- ~/.bash_profile:         The personal initialization file, executed for login shells
- ~/.bashrc:               The individual per-interactive-shell startup file
- ~/.bash_logout:          The individual login shell cleanup file, executed when a login shell exits
- ~/.inputrc:              Individual readline initialization file


