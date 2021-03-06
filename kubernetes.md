## Kubernetes Cluster Nodes
- Master(s): apiServer, scheduler, controllers
   - kube-apiproxy (the master)
   - kube-scheduler (resources manager)
   - kube-controller-manager (monitor RC, and maintain the desired state)
- Worker(s): kubelet, proxy
   - kubelet (start/stop containers, sync conf.),
   - kube-proxy (expose services on each node)
kubernetes may need to run etcd, docker and kubelet as the services. Others can be running as a POD.

The hyperkube binary is an all in one binary (in a way similar to busybox), combining all the binaries.

## [Kubernetes Download](https://kubernetes.io/docs/setup/release/notes/)
- server: hyperkube; kube-apiserver; kube-scheduler; kube-controller-manager; cloud-controller-manager; apiextensions-apiserver + node components
- node: kubeadm; kubectl; kubelet; kube-proxy
- client: kubectl

## Kubernetes Concepts
- Container: Docker Container, or some others, such as rtk, etc.

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


The following command:
```
hyperkube kubelet \
  --api-servers=http://localhost:8080 \
  --v=2 \
  --address=0.0.0.0 \
  --enable-server \
  --hostname-override=127.0.0.1 \
  --config=/etc/kubernetes/manifests-multi \
  --cluster-dns=10.0.0.10 \
  --cluster-domain=cluster.local
```
runs the daemon kubelet.

## kubectl: communicate with K8s master nodes for k8s operations
```
$ kubectl
kubectl controls the Kubernetes cluster manager.

Basic Commands (Beginner):
  create         Create a resource from a file or from stdin.
  expose         Take a replication controller, service, deployment or pod and expose it as a new Kubernetes Service
  run            Run a particular image on the cluster
  set            Set specific features on objects
  run-container  Run a particular image on the cluster. This command is deprecated, use "run" instead

Basic Commands (Intermediate):
  get            Display one or many resources
  explain        Documentation of resources
  edit           Edit a resource on the server
  delete         Delete resources by filenames, stdin, resources and names, or by resources and label selector

Deploy Commands:
  rollout        Manage the rollout of a resource
  rolling-update Perform a rolling update of the given ReplicationController
  scale          Set a new size for a Deployment, ReplicaSet, Replication Controller, or Job
  autoscale      Auto-scale a Deployment, ReplicaSet, or ReplicationController

Cluster Management Commands:
  certificate    Modify certificate resources.
  cluster-info   Display cluster info
  top            Display Resource (CPU/Memory/Storage) usage.
  cordon         Mark node as unschedulable
  uncordon       Mark node as schedulable
  drain          Drain node in preparation for maintenance
  taint          Update the taints on one or more nodes

Troubleshooting and Debugging Commands:
  describe       Show details of a specific resource or group of resources
  logs           Print the logs for a container in a pod
  attach         Attach to a running container
  exec           Execute a command in a container
  port-forward   Forward one or more local ports to a pod
  proxy          Run a proxy to the Kubernetes API server
  cp             Copy files and directories to and from containers.
  auth           Inspect authorization

Advanced Commands:
  apply          Apply a configuration to a resource by filename or stdin
  patch          Update field(s) of a resource using strategic merge patch
  replace        Replace a resource by filename or stdin
  convert        Convert config files between different API versions

Settings Commands:
  label          Update the labels on a resource
  annotate       Update the annotations on a resource
  completion     Output shell completion code for the specified shell (bash or zsh)

Other Commands:
  api-versions   Print the supported API versions on the server, in the form of "group/version"
  config         Modify kubeconfig files
  help           Help about any command
  plugin         Runs a command-line plugin
  version        Print the client and server version information

Use "kubectl <command> --help" for more information about a given command.
Use "kubectl options" for a list of global command-line options (applies to all commands).
```
