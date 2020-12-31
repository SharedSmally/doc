# docker images for K8s
- k8container: k8 base image with container runtime, systemd as the init system  
    - k8containerd: k8 image with containerd runtime 
    - k8crio: k8 image with CRIO runtime
    - k8docker: k8 image with docker runtime
        - k8master: docker image for k8s server/master node: api-server + etcd + controller
        - k8server: docker image for k8s server/master node: api-server + controller
        - k8etcd:   docker image for k8s server/master node: etcd
        - k8worker: docker image for k8s client/worker node
- k8image: image for pod container
    - k8image with [Virtual Machine Runtime](https://en.wikipedia.org/wiki/Comparison_of_application_virtualization_software)
    - k8java: with java VM
    - k8python: with python VM
    - k8go: with go VM
    - k8js: with javascript VM
    - k8nodejs: with NodeJS
    - k8php: With PHP
    - k8ruby: with Ruby
    - k8perl: with Perl
    - k8cli: Common Language Runtime (CLR) C#
    - k8lua: Lua

## Tools
- kubectl/kubeadm
- [Install and Use [Helm 2/3]() on Kubernetes Cluster](https://computingforgeeks.com/install-and-use-helm-2-on-kubernetes-cluster/)
    - [Helm v3](https://v3.helm.sh/docs/)
- Deploy Production Ready Kubernetes Cluster with Ansible & Kubespray
- Deploy Lightweight Kubernetes Cluster in 5 minutes with K3s

## [Container runtimes](https://computingforgeeks.com/docker-vs-cri-o-vs-containerd/)
- Standard: [Open Container Initiative](https://opencontainers.org/) releases [image and runtime](https://opencontainers.org/release-notices/overview/)specs
- [CNCF](https://www.cncf.io/)

The Cloud Native Computing Foundation (CNCF) hosts critical components of the global technology infrastructure. The [projects](https://www.cncf.io/projects/) includes:
    - [containerd](https://containerd.io/)
    - [etcd](https://etcd.io/): Key/Value Store
    - [coreDNS](https://coredns.io/): Service Discovery
    - [envoyProxy](https://www.envoyproxy.io/): an open source edge and service proxy for cloud-native applications
    - [helm](https://v3.helm.sh/docs/)(the package manager for Kubernetes)
    - [fluentd](https://www.fluentd.org/): an open source data collector for unified logging layer.
    - [Prometheus](https://prometheus.io/): an open-source systems monitoring and alerting toolkit.
    ![architecture][https://prometheus.io/assets/architecture.png]
    Can be viewed by [grafana](https://grafana.com/)
    

### Implementation:

 All three, docker, containerd, cri-o,depend on runC at the lowest level to handle the running of containers. 
 
- [Docker](https://www.docker.com/)

The implementation of Docker before 1.1 was a monolithic daemon. The monolith did everything as one package such as downloading container images, launching container processes, exposing a remote API, and acting as a log collection daemon, all in a centralized process running as root. 

The new architecture of Docker 1.11 after building it on runC and containerd:
![New Docker Implementaion](https://computingforgeeks.com/wp-content/uploads/2019/12/Docker1.11-1024x590.png)

Runc is a CLI tool for spawning and running containers according to the OCI specification.

- [containerd](https://containerd.io/)

From a high level stand point, containerd is a daemon that controls runC.

Containerd is available as a daemon for Linux and Windows. It manages the complete container lifecycle of its host system, from image transfer and storage to container execution and supervision to low-level storage to network attachments and beyond.
![containerd architecture](https://containerd.io/img/architecture.png)


- [CRI-O](https://cri-o.io/)

CRI-O is an implementation of the Kubernetes CRI (Container Runtime Interface) to enable using OCI (Open Container Initiative) compatible runtimes. It is a lightweight alternative to using Docker as the runtime for kubernetes. It allows Kubernetes to use any OCI-compliant runtime as the container runtime for running pods. 
![CRI-O architecture](https://cri-o.io/assets/images/architecture.png)

The screenshot below illustrates the whole Kubernetes and CRI-O process:
![CRI-O-k8s](https://computingforgeeks.com/wp-content/uploads/2019/12/Kubernetes-1024x620.png)
