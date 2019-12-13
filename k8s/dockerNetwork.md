# [docker network](https://docs.docker.com/engine/reference/commandline/network/)
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

## [network ls](https://docs.docker.com/engine/reference/commandline/network_ls/)
Support --filter. The currently supported filters are:
- driver
- id (network’s id)
- label (label=<key> or label=<key>=<value>)
- name (network’s name)
- scope (swarm|global|local)
- type (custom|builtin)
  
