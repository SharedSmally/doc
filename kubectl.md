# [kubectl](https://kubernetes.io/docs/reference/kubectl/)
Kubectl is a command line interface for running commands against Kubernetes clusters.
```
kubectl [command] [TYPE] [NAME] [flags]

Common commands:create, get, describe, delete, patch/replace, run/exec, expose
Types: pods, replicateset, service, deployments,
```

## config & context: kubectl config
Kubernetes uses a YAML file called kubeconfig to store cluster authentication information for kubectl. kubeconfig contains a list of contexts to which kubectl refers when running commands. By default, the file is saved at $HOME/.kube/config.

A context is a group of access parameters. Each context contains a Kubernetes cluster, a user, and a namespace. The current context is the cluster that is currently the default for kubectl: all kubectl commands run against that cluster.
```
Available Commands:
  current-context Displays the current-context
  delete-cluster  Delete the specified cluster from the kubeconfig
  delete-context  Delete the specified context from the kubeconfig
  get-clusters    Display clusters defined in the kubeconfig
  get-contexts    Describe one or many contexts
  rename-context  Renames a context from the kubeconfig file.
  set             Sets an individual value in a kubeconfig file
  set-cluster     Sets a cluster entry in kubeconfig
  set-context     Sets a context entry in kubeconfig
  set-credentials Sets a user entry in kubeconfig
  unset           Unsets an individual value in a kubeconfig file
  use-context     Sets the current-context in a kubeconfig file
  view            Display merged kubeconfig settings or a specified kubeconfig file

Usage:
  kubectl config SUBCOMMAND [options]
```


## Commands
### Basic Commands (Beginner):
```
   create         Create a resource from a file or from stdin.
   expose         Take a replication controller, service, deployment or pod and expose it as a new Kubernetes Service
   run            Run a particular image on the cluster
   set            Set specific features on objects
   run-container  Run a particular image on the cluster. This command is deprecated, use "run" instead
```
### Basic Commands (Intermediate):
```
   get            Display one or many resources
   explain        Documentation of resources
   edit           Edit a resource on the server
   delete         Delete resources by filenames, stdin, resources and names, or by resources and label selector
```
### Deploy Commands:
```
   rollout        Manage the rollout of a resource
   rolling-update Perform a rolling update of the given ReplicationController
   scale          Set a new size for a Deployment, ReplicaSet, Replication Controller, or Job
   autoscale      Auto-scale a Deployment, ReplicaSet, or ReplicationController
```
### Cluster Management Commands:
```
   certificate    Modify certificate resources.
   cluster-info   Display cluster info
   top            Display Resource (CPU/Memory/Storage) usage.
   cordon         Mark node as unschedulable
   uncordon       Mark node as schedulable
   drain          Drain node in preparation for maintenance
   taint          Update the taints on one or more nodes
```
### Troubleshooting and Debugging Commands:
```
   describe       Show details of a specific resource or group of resources
   logs           Print the logs for a container in a pod
   attach         Attach to a running container
   exec           Execute a command in a container
   port-forward   Forward one or more local ports to a pod
   proxy          Run a proxy to the Kubernetes API server
   cp             Copy files and directories to and from containers.
   auth           Inspect authorization
```
### Advanced Commands:
```
   apply          Apply a configuration to a resource by filename or stdin
   patch          Update field(s) of a resource using strategic merge patch
   replace        Replace a resource by filename or stdin
   convert        Convert config files between different API versions
```
### Settings Commands:
```
   label          Update the labels on a resource: used for id labeling
   annotate       Update the annotations on a resource: used for non-id labeling
   completion     Output shell completion code for the specified shell (bash or zsh)
```
### Other Commands:
```
   api-versions   Print the supported API versions on the server, in the form of "group/version"
   config         Modify kubeconfig files
   help           Help about any command
   plugin         Runs a command-line plugin
   version        Print the client and server version information
```
