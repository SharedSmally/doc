# MiniKube
## MiniKube Setup
- Download Minikube: https://github.com/kubernetes/minikube
- Copy minikube-windows-amd64.exe to minikube.exe
- Start MiniKube cluster: (VBox: CPUs=2, Memory=2048MB, Disk=20000MB;IP= 192.168.99.100)
```
minikube start
pods:  apiserver proxy etcd scheduler controller addon-manager dns
Images:kubernetes; kubeadm
```
- [minikube tutorial](https://kubernetes.io/docs/tutorials/hello-minikube/)

## Mini commands
```
  minikube [command]
Available Commands:
  addons         Modify minikube's kubernetes addons
  cache          Add or delete an image from the local cache.
  completion     Outputs minikube shell completion for the given shell (bash or zsh)
  config         Modify minikube config
  dashboard      Access the kubernetes dashboard running within the minikube cluster
  delete         Deletes a local kubernetes cluster
  docker-env     Sets up docker env variables; similar to '$(docker-machine env)'
  help           Help about any command
  ip             Retrieves the IP address of the running cluster
  logs           Gets the logs of the running instance, used for debugging minikube, not user code
  mount          Mounts the specified directory into minikube
  profile        Profile sets the current minikube profile
  service        Gets the kubernetes URL(s) for the specified service in your local cluster
  ssh            Log into or run a command on a machine with SSH; similar to 'docker-machine ssh'
  ssh-key        Retrieve the ssh identity key path of the specified cluster
  start          Starts a local kubernetes cluster
  status         Gets the status of a local kubernetes cluster
  stop           Stops a running local kubernetes cluster
  tunnel         tunnel makes services of type LoadBalancer accessible on localhost
  update-check   Print current and latest version number
  update-context Verify the IP address of the running cluster in kubeconfig.
  version        Print the version of minikube
```
## [Docker Components](http://alexander.holbreich.org/docker-components-explained/)
