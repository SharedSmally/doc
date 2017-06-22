## Kubernetes Cluster Nodes
- Master(s): apiServer, scheduler, controllers
- Slave(s): kubelet, proxy

## Kubernetes
- Container: Docker Container

- Pod:
   - Tightly coupled a group of containers & volumes
   - The atom of scheduling & placement
   - Shared namespace, IP address & localhost, IPC.etc
   - Managed lifecycle (bound to a node, restart in place, can die, cannot be reborn with same ID)

- Label
   - A list of key/values metadata attached to any API object
   - Generally represent identity, and Queryable by selectors
 
 - Selector 
 
 - Service
 
    - A group of pods that work together (grouped by a selector)
    - Defines access policy (load balanced or headless)
    - Can have a stable virtual IP and por, and/or a DNS name
    - VIP is managed by kube-proxy
       - watches all services
       - updates iptables when backends change
       - default implementation - can be replaced!

