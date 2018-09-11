
##[K8s Cluster] https://cloud.google.com/kubernetes-engine/docs/concepts/cluster-architecture
A Kubernetes cluster consists of at least one cluster master and multiple worker machines called nodes. These master and node machines run the Kubernetes cluster orchestration system.

### [Master]()
- The cluster master runs the Kubernetes control plane processes, including the Kubernetes API server, scheduler, and core resource controllers. The master is the unified endpoint for your cluster. All interactions with the cluster are done via Kubernetes API calls, and the master runs the Kubernetes API Server process to handle those requests.

### [Nodes]()
- A cluster typically has one or more nodes, which are the worker machines that run your containerized applications and other workloads.
- Each node is managed from the master, which receives updates on each node's self-reported status. 
- A node runs the services necessary to support the Docker containers that make up your cluster's workloads. These include the Docker runtime and the Kubernetes node agent (kubelet) which communicates with the master and is responsible for starting and running Docker containers scheduled on that node.

###[Setup](https://kubernetes.io/docs/setup/scratch/)
###[Setup with kubeadm](https://kubernetes.io/docs/setup/independent/install-kubeadm/)

