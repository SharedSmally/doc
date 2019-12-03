# K8s cluster
## [Architecture](https://www.ibm.com/support/knowledgecenter/en/SSBS6K_3.2.0/getting_started/architecture.html)
- Boot node: ansible-based installer
- Master node: HA
- Worker node
- Proxy node: transmits external request to the internal services in cluster (haproxy)
- Management node: only hosts management services such as monitoring, metering, and logging.
- VA node
- etcd node

Example: [IBM Cloud Private](). Applications: image registry, manage charts and apps.

- CDK on LXD
- Docker Desktop
- Minishift/OpenShift
- MicroK8s
- IBM Cloud Private-CE(Community Edition)
- k3s

## K8s components
- VM management: vagrant (Using images for HyperV, libvirt-kvm, VirtualBox and VMware)on VM or physical machine(OpenStack, AWS, GCE, Azure,...)
- VM OS: centos/8 (https://www.centos.org) 
- Pod Container runtime: docker

## K8s control plane VMs (masters)
- api-server
- etcd
- controller-manager
- scheduler   
    
## K8s working VMs (workers)
- kubelet
    
## K8s adm VMs
- kubectl 
- kube-proxy 

### kubectl config
```
$ kubectl config -h
$ kubectl config view
```
using context (cluster-user-credential) based on config file:
- --kubeconfig flag: Only that file without merging
- $KUBECONFIG environment variable: A list of paths with merging
- ${HOME}/.kube/config file: no merging

### [certificates in K8s cluster](https://kubernetes.io/docs/setup/best-practices/certificates/)
- Client certificates for the kubelet to authenticate to the API server
- Server certificate for the API server endpoint
- Client certificates for administrators of the cluster to authenticate to the API server
- Client certificates for the API server to talk to the kubelets
- Client certificate for the API server to talk to etcd
- Client certificate/kubeconfig for the controller manager to talk to the API server
- Client certificate/kubeconfig for the scheduler to talk to the API server.
- Client and server certificates for the front-proxy
