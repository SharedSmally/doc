
## Multicast
[Multicast Tutorial](http://www.linuxfocus.org/English/January2001/article144.meta.shtml)


```
struct ip_mreq {
   struct in_addr imr_multiaddr; // IP multicast address of group
   struct in_addr imr_interface; // local IP address of interface
};

struct ip_mreqn {  // new version
    struct in_addr imr_multiaddr; // IP multicast group address
    struct in_addr imr_address;   // IP address of local interface
    int            imr_ifindex;   // interface index
};

struct ip_mreq_source {
    struct in_addr imr_multiaddr;  // IP multicast group address
    struct in_addr imr_interface;  // IP address of local interface
    struct in_addr imr_sourceaddr; // IP address of multicast source
};
```

- Multicast Address

| Scope   | TTL | Address range  | Description |
| ------------- | ------------- | ------------- | ------------- |
| Node  | 0  |   | The datagram is restricted to the local host. It will not reach any of the network interfaces.  |
| Link  | 1  | 224.0.0.0 - 224.0.0.255	  | The datagram will be restricted to the sender host subnet, and will not progress beyond any router.  |
| Department  | <32  | 239.255.0.0 - 239.255.255.255  | Restricted to one department of the organization.  |
| Organization  | <64  | 239.192.0.0 - 239.195.255.255  | Restricted for a specific organization.   |
| Global  | <255  | 224.0.1.0 - 238.255.255.255  | No restriction, global application.   |
                                                                      |

- Multicast Socket Options

| IPv4 Option	       | Data type       |	Description                                                 |
| ------------------- | --------------- | ----------------------------------------------------------- |
| IP_ADD_MEMBERSHIP   | struct ip_mreq  |	Join the multicast group. No port is needed.                |
| IP_DROP_MEMBERSHIP  | struct ip_mreq  | Resign from the multicast group.                            |
| IP_MULTICAST_IF	    | struct ip_mreq  | Specify an interface for submission of multicast messages.  |
| IP_MULTICAST_TTL    | u_char          |	Specify a TTL for submission of multicast messages.         |
| IP_MULTICAST_LOOP   | u_char          |	Activate or deactivate the multicast messages loopback.     |

needs to join the group and bind the local address if want to receive the message.
Only need to open socket of group addr if want to send the message.

Binding to a local address determines which local addresses the socket can send and receive
data on: one, or all of them: either one local address, which determines which of available
subnets listening to and can send via, or a port, or both. Normally it is best to use
INADDR_ANY as the bind-address, unless application magically knows about the network topology.
send to a multicast group by sending to the multicast address.

- Steps to receive traffic from a multicast group
1. Create the socket.
2. Bind the group/port.
3. Optionally, use the SO_REUSEADDR option, so more than one process can bind
   the same group and port on the same machine, i.e., have multiple receivers.
4. Join the group

All the server/client use the same group address and port, and clients bind the
local address:

//server:
```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#define MAXBUF 256
#define PUERTO 5000
#define GRUPO "224.0.1.1"

int main(void) {
  int s;
  struct sockaddr_in srv;
  char buf[MAXBUF];

  bzero(&srv, sizeof(srv));
  srv.sin_family = AF_INET;
  srv.sin_port = htons(PUERTO);
  if (inet_aton(GRUPO, &srv.sin_addr) < 0) {
   perror("inet_aton");
   return 1;
  }
  if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
   perror("socket");
   return 1;
  }

  while (fgets(buf, MAXBUF, stdin)) {
    if (sendto(s, buf, strlen(buf), 0,
              (struct sockaddr *)&srv, sizeof(srv)) < 0) {
      perror("recvfrom");
    } else {
      fprintf(stdout, "Enviado a %s: %s\n", GRUPO, buf);
    }
  }
}
```
//client
```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#define MAXBUF 256
#define PUERTO 5000
#define GRUPO "224.0.1.1"

int main(void) {
  int s, r;
  socklen_t n;
  int yes=1;
  struct sockaddr_in srv, cli;
  struct ip_mreq mreq;
  char buf[MAXBUF];

  bzero(&srv, sizeof(srv));
  srv.sin_family = AF_INET;
  srv.sin_port = htons(PUERTO);
  if (inet_aton(GRUPO, &srv.sin_addr) < 0) {
    perror("inet_aton");
    return 1;
  }

  if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    return 1;
  }

  if (setsockopt(s, SOL_SOCKET,  SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
      perror("reuseaddr setsockopt");
      return 1;
  }

  if (bind(s, (struct sockaddr *)&srv, sizeof(srv)) < 0) {
    perror("bind");
    return 1;
  }

  if (inet_aton(GRUPO, &mreq.imr_multiaddr) < 0) {
    perror("inet_aton");
    return 1;
  }
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);

  if (setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
    perror("setsockopt");
    return 1;
  }

  n = sizeof(cli);
  while (1) {
    if ((r = recvfrom(s, buf, MAXBUF, 0, (struct sockaddr *) &cli, &n)) < 0) {
      perror("recvfrom");
    } else {
      buf[r] = 0;
      fprintf(stdout, "Mensaje desde %s: %s\n",
              inet_ntoa(cli.sin_addr), buf);
    }
  }
}
```
