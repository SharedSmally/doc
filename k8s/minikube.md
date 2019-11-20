# [Minikube](https://github.com/kubernetes/minikube)
## [Document](https://minikube.sigs.k8s.io/docs/)
- [Commands](https://minikube.sigs.k8s.io/docs/reference/commands/)
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
- start minikube: download VM boot image minikube.iso and IP address(192.168.99.100)
```
minikube start
minikube start -p <cluster_name>
minikube status
kubectl get po -A  #list running Pods
```
- stop minikube
```
minikube stop
```
- login minikube VM
```
minikube ssh
```
- start Dashboard: will show URL for dashboard
```
minikube dashboard
```
- kubectl proxy: run kubectl acting as a reverse proxy, and handles locating the apiserver and authenticating
```
kubectl proxy --port=8080
curl http://localhost:8080/
curl http://localhost:8080/api/
curl http://localhost:8080/openapi/v2
```
- addon management
```
minikube addon
```
## [Examples](https://minikube.sigs.k8s.io/docs/examples/)
- starting a server:
```
kubectl create deployment hello-minikube --image=k8s.gcr.io/echoserver:1.4 
```
- Exposing a service as a NodePort
```
kubectl expose deployment hello-minikube --type=NodePort --port=8080
```
- open the exposed endpoint in browser (access the service):
```
minikube service hello-minikube
```
## Environment
The config directory is ~/.minikube/:
- addons
- cache
    - images: gcr.io; k8s.gcr.io (docker images from k8s, gcr repositories)
    - iso: minikube-xxx.iso (ISO for VM)
    - vx.x.x: kubeadm; kubelet
- certs
- config
- files
- logs
- machines: VM disk and image
- profiles

/var/lib/kubeadm.yaml is used by kubeadm for cluster networking setup:
- dnsDomain: cluster.local
- podSubnet: ""
- serviceSubnet: 10.96.0.0/12

minikube requires access from the host to the following IP ranges:
- 192.168.99.0/24: Used by the minikube VM. Configurable for some hypervisors via --host-only-cidr
- 192.168.39.0/24: Used by the minikube kvm2 driver.
- 10.96.0.0/12: Used by service cluster IP’s. Configurable via --service-cluster-ip-range

