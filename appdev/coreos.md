# coreos
- VM OS:
- Container OS:  manage a list of containers via kubernetes using etcd ()
- etcd

## [CNCF](https://www.cncf.io/) and [Projects](https://www.cncf.io/projects/)
- Kubernetes
- Prometheus
- Envoy
- CoreDNS
- ContainerD

## Container Runtime 
- [docker](https://www.docker.com/)
A user runs commands from Docker-CLI > Docker-CLI talks to the Docker daemon(dockerd) > Docker daemon(dockerd) 
- listens for requests and manages the lifecycle of the container via containerd which it contacts > containerd 
- takes the request and starts a container through runC and does all the container life-cylces within the host.
![docker](https://computingforgeeks.com/wp-content/uploads/2019/12/Docker1.11-1024x590.png)
runc is a CLI tool for spawning and running containers according to the OCI specification.

- [containerD](https://containerd.io/)
containerd is a daemon that controls runC.

- [CRIO](https://cri-o.io/): Container Runtime Interface, the Lightweight Container Runtime for Kubernetes
![CRIO](https://computingforgeeks.com/wp-content/uploads/2019/12/Kubernetes-1024x620.png)
![kubectl-crio](https://vmblog.com/images/kubelet-node.png)

## container OS
- minimum os with container runtime 
- container runtime: 
    - docker
    - rkt 
    - [Container Linux](https://en.wikipedia.org/wiki/Container_Linux)
- deployment: kubernetes
