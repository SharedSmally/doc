# Docker Minikube 

## Docker
```
Management Commands:
  builder     Manage builds
  config      Manage Docker configs
  container   Manage containers
  context     Manage contexts
  engine      Manage the docker engine
  image       Manage images
  network     Manage networks
  plugin      Manage plugins
  secret      Manage Docker secrets
  service     Manage services
  stack       Manage Docker stacks
  system      Manage Docker
  trust       Manage trust on Docker images
  volume      Manage volumes

  node        Manage Swarm nodes
  swarm       Manage Swarm  

Container Commands:
  create      Create a new container
  rm          Remove one or more containers
  
  start       Start one or more stopped containers
  restart     Restart one or more containers  
  stop        Stop one or more running containers  
  kill        Kill one or more running containers  
  wait        Block until one or more containers stop, then print their exit codes
  
  exec        Run a command in a running container
  run         Run a command in a new container
  
  attach      Attach local standard input, output, and error streams to a running container
  ps          List containers
  top         Display the running processes of a container
  
  update      Update configuration of one or more containers  
  export      Export a container's filesystem as a tar archive
  import      Import the contents from a tarball to create a filesystem image  
  rename      Rename a container
  cp          Copy files/folders between a container and the local filesystem
  diff        Inspect changes to files or directories on a container's filesystem
  commit      Create a new image from a container's changes
  
  logs        Fetch the logs of a container
  port        List port mappings or a specific mapping for the container  
  pause       Pause all processes within one or more containers
  unpause     Unpause all processes within one or more containers

  stats       Display a live stream of container(s) resource usage statistics  

Image Commands:
  build       Build an image from a Dockerfile
  rmi         Remove one or more images
  load        Load an image from a tar archive or STDIN  
  save        Save one or more images to a tar archive (streamed to STDOUT by default)
  tag         Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE  
  images      List images
  history     Show the history of an image

Docker registry Commands:
  login       Log in to a Docker registry
  logout      Log out from a Docker registry
  pull        Pull an image or a repository from a registry
  push        Push an image or a repository to a registry
  search      Search the Docker Hub for images

Misc:
  events      Get real time events from the server
  info        Display system-wide information
  inspect     Return low-level information on Docker objects
  version     Show the Docker version information

````

## Minikube
```
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

## Uninstall Minikube
```
minikube stop; 
minikube delete
docker stop (docker ps -aq)
rm -r ~/.kube ~/.minikube
sudo rm /usr/local/bin/localkube /usr/local/bin/minikube
systemctl stop '*kubelet*.mount'
sudo rm -rf /etc/kubernetes/
docker system prune -af --volumes
```
