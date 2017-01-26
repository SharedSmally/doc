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
