# [pod](https://kubernetes.io/docs/concepts/workloads/pods/)

- [Life Cycle](https://kubernetes.io/docs/concepts/workloads/pods/pod-lifecycle/)
    - pod phase
    - container state
    
- 

Pods are the smallest deployable units of computing that you can create and manage in Kubernetes.

A Pod is a group of one or more containers, with shared storage/network resources, and a specification for how to run the containers.
A Pod's contents are always co-located and co-scheduled, and run in a shared context. 
A Pod models an application-specific "logical host": it contains one or more application containers which are 
relatively tightly coupled. In non-cloud contexts, applications executed on the same physical or virtual machine
are analogous to cloud applications executed on the same logical host.

Each Pod is meant to run a single instance of a given application. 

The shared context of a Pod is a set of Linux namespaces, cgroups, and potentially other facets of isolation - 
the same things that isolate a Docker container. Within a Pod's context, the individual applications may have further sub-isolations applied.

Each Pod is assigned a unique IP address for each address family. Every container in a Pod shares the network namespace, including the IP address and 
network ports. Inside a Pod (and only then), the containers that belong to the Pod can communicate with one another using localhost. 
