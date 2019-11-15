
# Kubernetes
- [Release Download](https://kubernetes.io/docs/setup/release/)
- [Concepts](https://kubernetes.io/docs/concepts/)
- [Reference](https://kubernetes.io/docs/reference/)
- [Tutorial](https://kubernetes.io/docs/tutorials/)
- [Tasks](https://kubernetes.io/docs/tasks/)
- Images
    - [MiniKube](https://github.com/kubernetes/minikube/releases): Simple all-in-one K8s cluster : [Reference](https://kubernetes.io/docs/setup/learning-environment/minikube/)
    - [Minishift](https://github.com/minishift/minishift/releases):The Openshift with All-In-One VM 
    - [OpenShift](https://www.okd.io/): distribution of Kubernetes optimized for continuous application development and multi-tenant deployment
    - [Fabric8](https://fabric8.io/): An end to end development platform spanning ideation to production for the creation of cloud native applications and microservices.


## [K8s Cluster](https://cloud.google.com/kubernetes-engine/docs/concepts/cluster-architecture)
A Kubernetes cluster consists of at least one cluster master and multiple worker machines called nodes. These master and node machines run the Kubernetes cluster orchestration system.

On cluster, apiserver/ kube-scheduler/ kube-controller-manager (needs etcd for data sharing) are running on the master. Kubelet and kube-proxy run on each working nodes. They also need to run container service (docker or rkt, ...).

![K8s components](https://d33wubrfki0l68.cloudfront.net/817bfdd83a524fed7342e77a26df18c87266b8f4/3da7c/images/docs/components-of-kubernetes.png)

### Master
- The cluster master runs the Kubernetes control plane processes, including the Kubernetes API server, scheduler, and core resource controllers. The master is the unified endpoint for your cluster. All interactions with the cluster are done via Kubernetes API calls, and the master runs the Kubernetes API Server process to handle those requests.

### Work Nodes
- A cluster typically has one or more nodes, which are the worker machines that run your containerized applications and other workloads.
- Each node is managed from the master, which receives updates on each node's self-reported status. 
- A node runs the services necessary to support the Docker containers that make up your cluster's workloads. These include the Docker runtime and the Kubernetes node agent (kubelet) which communicates with the master and is responsible for starting and running Docker containers scheduled on that node.

### User
The end user will use [kubectl](https://kubernetes.io/docs/reference/kubectl/kubectl/) tp communicate with api-server

### [Setup](https://kubernetes.io/docs/setup/)
### [Setup with kubeadm](https://kubernetes.io/docs/setup/independent/install-kubeadm/)

