# MiniKube
- [https://minikube.sigs.k8s.io/docs/]

## Commands
```
minikube --help
```
### Basic Commands:
```
  start            Starts a local Kubernetes cluster
  status           Gets the status of a local Kubernetes cluster
  stop             Stops a running local Kubernetes cluster
  delete           Deletes a local Kubernetes cluster
  dashboard        Access the Kubernetes dashboard running within the minikube cluster
  pause            pause Kubernetes
  unpause          unpause Kubernetes
```
### Images Commands:
```
  docker-env       Provides instructions to point your terminal's docker-cli to the Docker Engine inside minikube.
  podman-env       Configure environment to use minikube's Podman service
  cache            Manage cache for images
  image            Manage images
```

### Configuration and Management Commands:
```
  addons           Enable or disable a minikube addon
  config           Modify persistent configuration values
  profile          Get or list the current profiles (clusters)
  update-context   Update kubeconfig in case of an IP or port change
```

### Networking and Connectivity Commands:
```
  service          Returns a URL to connect to a service
  tunnel           Connect to LoadBalancer services
```

### Advanced Commands:
```
  mount            Mounts the specified directory into minikube
  ssh              Log into the minikube environment (for debugging)
  kubectl          Run a kubectl binary matching the cluster version
  node             Add, remove, or list additional nodes
  cp               Copy the specified file into minikube
```
### Troubleshooting Commands:
```
  ssh-key          Retrieve the ssh identity key path of the specified node
  ssh-host         Retrieve the ssh host key of the specified node
  ip               Retrieves the IP address of the specified node
  logs             Returns logs to debug a local Kubernetes cluster
  update-check     Print current and latest version number
  version          Print the version of minikube
  options          Show a list of global command-line options (applies to all commands).
```
