### uname -a: print all info of the system
### uname -s: print kernel name: -r: kernel release; -v: kernel version
### uname -n: print the node hostname
### uname -m: print the hardware name
### uname -p: print the processor name
### uname -i: print the hardware platform
### uname -o: print the OS

### ifconfig -a
list of addresses.

### netstat -g
list of multicast group and NIC that join the group.


### Multicast. See [sample](https://www.tenouk.com/Module41c.html)
#### NIC
- if_nameindex/if_freenameindex: get  network  interface names and indexes
- getifaddrs/freeifaddrs: get interface addresses (static info)
- datagram socket/ioctl: get interface information (dynamic info)
    - SIOCGIFHWADDR: MAC address
    - SIOCGIFMTU: mtu
    - SIOCGIFADDR: address
    - SIOCGIFBRDADDR: broadcast address
    - SIOCGIFNETMASK: network mask    
    
#### Server:
- Create an AF_INET, SOCK_DGRAM type socket.
- Initialize a group sockaddr_in with the destination group IP address and port number.
- Enable/Disable loopback using IP_MULTICAST_LOOP socket option 
- Set the IP_MULTICAST_IF socket option to define the local interface (local IP address).
- Send the datagram to group.
#### Client:
- Create an AF_INET, SOCK_DGRAM type socket.
- Set the SO_REUSEADDR option to allow multiple applications to receive datagrams that are destined to the same local port number.
- Use the bind() to specify the local port number(server group port).  Specify the IP address as INADDR_ANY to receive datagrams that are addressed to a multicast group.
- Use the IP_ADD_MEMBERSHIP socket option to join the multicast group that receives the datagrams. specify the class D group address(group.imr_multiaddr.s_addr) along with the IP address of a local interface(group.imr_interface.s_addr). The system must call the IP_ADD_MEMBERSHIP socket option for each local interface receiving the multicast datagrams.
- Receive the datagram.
