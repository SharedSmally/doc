# docker networking

## [docker network config](https://docs.docker.com/network/)

## [docker network](https://docs.docker.com/engine/reference/commandline/network/)
```
Usage:  docker network [OPTIONS] COMMAND [OPTIONS]
Commands:
  rm                       Remove a network
  create                   Create a network
  connect                  Connect container to a network
  disconnect               Disconnect container from a network
  inspect                  Display detailed network information
  ls                       List all networks
```

## [User Guide](https://docs.docker.com/v17.09/engine/userguide/networking/)
- Default networks: Docker creates three networks automatically. 
```
$ docker network ls
NETWORK ID          NAME                DRIVER
7fca4eb8c647        bridge              bridge
9f904ee27bf5        none                null
cf03ee007fb4        host                host
```
Use the --network flag to specify which networks the container should connect to.

The bridge network represents the docker0 network present in all Docker installations. The Docker daemon connects containers to this network by default unless specify the docker run --network=<NETWORK> option.
```
  $ ip addr show
  $ ifconfig
  # cat /etc/hosts
```

## network command

### [network create](https://docs.docker.com/engine/reference/commandline/network_create/)
Creates a new network. The DRIVER accepts bridge(default) or overlay which are the built-in network drivers. If a third party or custom network driver have been installed specify that DRIVER with --driver option.
```
$ docker network create -d bridge my-bridge-network
```
- Bridge networks are isolated networks on a single Engine installation. 
- Overlay networks are created to spans multiple Docker hosts each running an Engine. It require some pre-existing conditions:
    - Access to a key-value store. Engine supports Consul, Etcd, and ZooKeeper (Distributed store) key-value stores.
    - A cluster of hosts with connectivity to the key-value store.
    - A properly configured Engine daemon on each host in the cluster.

### [network ls](https://docs.docker.com/engine/reference/commandline/network_ls/)
Support --filter. The currently supported filters are:
- driver
- id (network’s id)
- label (label=<key> or label=<key>=<value>)
- name (network’s name)
- scope (swarm|global|local)
- type (custom|builtin)
  
## [Network drivers]
Docker’s networking subsystem is pluggable, using drivers. Several drivers exist by default, and provide core networking functionality:
- [bridge](https://docs.docker.com/network/bridge/): The default network driver. Bridge networks are usually used when your applications run in standalone containers that need to communicate. 
- [host](https://docs.docker.com/network/host/): For standalone containers, remove network isolation between the container and the Docker host, and use the host’s networking directly. host is only available for swarm services on Docker 17.06 and higher.
- [overlay](https://docs.docker.com/network/overlay/): Overlay networks connect multiple Docker daemons together and enable swarm services to communicate with each other. You can also use overlay networks to facilitate communication between a swarm service and a standalone container, or between two standalone containers on different Docker daemons. This strategy removes the need to do OS-level routing between these containers. See overlay networks.
- [macvlan](https://docs.docker.com/network/macvlan/): Macvlan networks allow you to assign a MAC address to a container, making it appear as a physical device on your network. The Docker daemon routes traffic to containers by their MAC addresses. Using the macvlan driver is sometimes the best choice when dealing with legacy applications that expect to be directly connected to the physical network, rather than routed through the Docker host’s network stack. See Macvlan networks.
- [none](https://docs.docker.com/network/none/): For this container, disable all networking. Usually used in conjunction with a custom network driver. none is not available for swarm services. 
- [Network plugins](https://hub.docker.com/search?category=network&q=&type=plugin): You can install and use third-party network plugins with Docker. These plugins are available from Docker Hub or from third-party vendors. 
