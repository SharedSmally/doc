# K8s cluster

## K8s control plane VMs (masters)
Using Vagrant images for HyperV, libvirt-kvm, VirtualBox and VMware.
- OS: centos/8 (https://www.centos.org)
- Components
    - api-server
    - etcd
    - controller
    
## K8s working VMs (workers)
- OS: centos/8 (https://www.centos.org)
- Components
    - kubelet
    
## K8s adm VMs
- Components
    - kubectl 

### kubectl config
```
$kubectl config -h
```
using context (cluster-user-credential) based on config file:
- --kubeconfig flag: Only that file without merging
- $KUBECONFIG environment variable: A list of paths with merging
- ${HOME}/.kube/config file: no merging

