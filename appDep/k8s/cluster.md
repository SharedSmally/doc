# K8s Cluster

## Roles
- Master Node (control node)
- Worker Nodes (work nodes)

## Setup K8s Cluster
- Kubeadm Ansible Playbook: https://github.com/kairen/kubeadm-ansible
- Vargent and Ansible: https://kubernetes.io/blog/2019/03/15/kubernetes-setup-using-ansible-and-vagrant/
- Ansible only: https://buildvirtual.net/deploy-a-kubernetes-cluster-using-ansible/
- Ansible on centos: https://faun.pub/how-to-create-your-own-kubernetes-cluster-using-ansible-7c6b5c031a5d
- Ansible on centos: https://computingforgeeks.com/deploy-kubernetes-cluster-on-centos-with-ansible-calico/
- kubeadm only: https://devopscube.com/setup-kubernetes-cluster-kubeadm/

## Setup Gluster
- Gluster on k8s: https://computingforgeeks.com/configure-kubernetes-dynamic-volume-provisioning-with-heketi-glusterfs/
- Setup Gluster on centos: https://computingforgeeks.com/setup-glusterfs-storage-with-heketi-on-centos-server/

## Steps
- Install container runtime on all nodes- We will be using Docker.
- Install Kubeadm, Kubelet, and kubectl on all the nodes.
- Initiate Kubeadm control plane configuration on the master node.
- Save the node join command with the token.
- Install the Calico network plugin.
- Join worker node to the master node (control plane) using the join command.
- Validate all cluster components and nodes.
- Install Kubernetes Metrics Server
- Deploy a sample app and validate the app
    
