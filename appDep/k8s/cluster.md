# K8s Cluster

- kubeadm: https://devopscube.com/setup-kubernetes-cluster-kubeadm/
- Deploy K8s Cluster using Ansible: https://buildvirtual.net/deploy-a-kubernetes-cluster-using-ansible/

## Roles
- Master Node (control node)
- Worker Nodes (work nodes)

## Setup
- Install container runtime on all nodes- We will be using Docker.
- Install Kubeadm, Kubelet, and kubectl on all the nodes.
- Initiate Kubeadm control plane configuration on the master node.
- Save the node join command with the token.
- Install the Calico network plugin.
- Join worker node to the master node (control plane) using the join command.
- Validate all cluster components and nodes.
- Install Kubernetes Metrics Server
- Deploy a sample app and validate the app
    
