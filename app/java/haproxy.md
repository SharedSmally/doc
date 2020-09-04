# [HAProxy](http://www.haproxy.org/)

HAProxy is a free, very fast and reliable solution offering high availability, load balancing, and proxying for TCP and HTTP-based applications.
- [Document](http://cbonte.github.io/haproxy-dconv/)
- [Architecture](https://www.haproxy.org/download/1.2/doc/architecture.txt)
- [Introduction](http://cbonte.github.io/haproxy-dconv/2.3/intro.html)
- [Configuration](http://cbonte.github.io/haproxy-dconv/2.3/configuration.html)
- [Management](http://cbonte.github.io/haproxy-dconv/2.3/management.html)
- High Available/Failover in [Ubuntu](https://www.digitalocean.com/community/tutorials/how-to-set-up-highly-available-haproxy-servers-with-keepalived-and-floating-ips-on-ubuntu-14-04) or [centOS](https://www.centlinux.com/2018/08/keepalived-configure-floating-ip-centos-7.html):

Using some form of VRRP to maintain a virtual IP address across 1 or more servers, each running HAproxy. This is typically done with [keepalived](https://www.keepalived.org/) as
[described](https://autoize.com/redundant-load-balancing-haproxy-keepalived/).

High availability HAProxy setup is possible with Heartbeat on Linux or CARP or BSD systems. It requires one "floating" IP address 
(which will be used for HAProxy), which will be assigned to one of computers in cluster. One current computer holding IP address 
fails, failover server will take IP address and continue serving requests. If you combine CARP with pfsync, TCP connection 
state will be synced between servers and failover will be "seamless"

Using Virtual Router Redundancy Protocol([vrrp])(https://www.haproxy.com/documentation/hapee/1-9r1/configuration/vrrp/)


## Config (haproxy.cfg )
```
global
tune.ssl.default-dh-param 1024

defaults
timeout connect 10000ms
timeout client 60000ms
timeout server 60000ms

frontend fe_http
mode http
bind *:80
# Redirect to https
redirect scheme https code 301

frontend fe_https
mode tcp
bind *:443 ssl no-sslv3 crt domain.pem ciphers TLSv1.2 alpn h2,http/1.1
default_backend be_http

backend be_http
mode tcp
server domain 127.0.0.1:8282
```

## [HAProxy with jetty](https://www.eclipse.org/jetty/documentation/current/http2-configuring-haproxy.html)

## [KeepAlive configuration](https://www.keepalived.org/manpage.html)

## [HAProxy_keepalive for K8s](https://vitobotta.com/2020/03/20/haproxy-kubernetes-hetzner-cloud/)

## [Pacemaker](https://clusterlabs.org/)
Pacemaker is a high-availability cluster resource manager.

