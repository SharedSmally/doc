# Application Deployment

## Kubernetes Cluster
- Master Node (1)
- Worker Node (2)

## HA Platform
- [keepalived](https://github.com/acassen/keepalived):Load Balancing & High-Availability based on Virtual Router Redundancy Protocol (VRRP)/IP Multicast.
Keepalived is configured in VRRP high availability mode (1 active/n-1 passive) running on the same servers that provide the service. All servers on the VRRP instance run the listening service and keepalived;

If a fail event is signalled by one of the servers, it leaves the VRRP instance which could cause the Virtual IP to point at a different host, if the failed host was the active server.

Once setup, keepalived will initiate the VRRP protocol between all nodes in the same instance, assign the Virtual IP to the active node and monitor the instance using the command provided. Requests done to the Virtual IP end up on the active node.

Sample Config file: For master/
```
vrrp_instance VI1SL {
        state MASTER   # (optional) initial state for this server; BACKUP for the backup nodes
        interface eth1 # interface where VRRP traffic will exist
        advert_int 5   # interval between sync
        virtual_router_id 71 # unique identifier per VRRP instance (same across all servers on the instance)
        priority 100   # server priority - higher number == higher priority for master selection

        # authentication for VRRP messages, same for all servers
        authentication {
                #auth_type PASS # simple authentication (plain)
                auth_type AH    # good authentication
                auth_pass marvin # password
        }
        virtual_ipaddress {
                192.168.111.35/24 dev eth0 # Virtual IP address and interface assignment
        }
        track_script {
                check_rsyslog # tracking script
        }
}
vrrp_script check_rsyslog {
        script "/usr/local/sbin/checkrsyslog.sh"
        interval 5 # 5s per check
        fall 2 # 2 fails - 10s
        rise 2 # 2 OKs - 10s
        #timeout 15 # wait up to 15 seconds for script before assuming fail
        #weight 50 # Reduce priority by 10 on fall
}
```
For Load Balance, replace virtual_server instead of vrrp_script check_rsyslog
```
# Virtual server configured to listen on the VRRP Virtual IP
# This section instructs keepalive to configure the kernel's Virtual Server subsystem
virtual_server 192.168.133.38 25 {
        delay_loop 60 # time between checks, in seconds
        lb_algo rr    # load balancing algorithm
        lb_kind DR    # load balancing type: Direct Routing in this case
        protocol TCP
        persistence_timeout 60 # client to real-server mappings will be maintained for at least 60 seconds after a connection is terminated

        # Real Server A
        real_server 192.168.133.8 25 {
                weight 100 # used to influence the load balancing algorithm
                # real server check mechanism (this can be changed to other types of checking including custom scripts)
                # in this case, if a TCP connection cannot be established to the real server ip:port, then it is
                # removed from the pool
                TCP_CHECK {
                        connect_timeout 6
                }
        }

        # Real Server B
        real_server 192.168.133.12 25 {
                weight 100
                TCP_CHECK {
                        connect_timeout 6
                }
        }
}
```
- [haproxy](http://www.haproxy.org/)

Global parameters

Proxy configuration can be located in a set of sections :
- defaults [<name>] [ from <defaults_name> ]
- frontend <name>   [ from <defaults_name> ]
- backend  <name>   [ from <defaults_name> ]
- listen   <name>   [ from <defaults_name> ]
  
## Application Platform
- Postgresql for database
- Redis for Cache
- Kafka for Trace/Record (multiple instance)
- ActiveMQ Armtis/RabbitQ for JMS
- Monitor System
- Logging: EFK(Elasticsearch/search, FluentD/Collect and Kibana/Visualization) 
https://www.digitalocean.com/community/tutorials/how-to-set-up-an-elasticsearch-fluentd-and-kibana-efk-logging-stack-on-kubernetes
(namespace kube-logging/)

## Application

  
### AppContext
Contains a list of predefined Beans or BeanFactory  
