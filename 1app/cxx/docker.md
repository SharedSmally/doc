# Docker
- [CLI reference](https://docs.docker.com/engine/reference/run/))
- [API reference](https://docs.docker.com/engine/api/)
- [Docker file](https://docs.docker.com/engine/reference/builder/)

## Docker Image
```
FROM busybox
ENV FOO=/bar
WORKDIR ${FOO}   # WORKDIR /bar
ADD . $FOO       # ADD . /bar
COPY \$FOO /quux # COPY $FOO /quux

$ docker build -t succeeds --no-cache=true .
```
- FROM: FROM ImageName
     - FROM [--platform=<platform>] <image> [AS <name>]
     - FROM [--platform=<platform>] <image>[:<tag>] [AS <name>]
     - FROM [--platform=<platform>] <image>[@<digest>] [AS <name>]
- RUN
- CMD
- LABEL
- EXPOSE
- ENV:  ENV abc=bye def=$abc
     - ${variable_name};
     - ${variable:-word}: If not set, word is the result.
     - ${variable:+word}: If set, word is the result, otherwise is the empty string.
- ADD
- COPY
- ENTRYPOINT
- VOLUME
- USER
- WORKDIR
- ARG
- ONBUILD
- STOPSIGNAL
- HEALTHCHECK
- SHELL

## Docker CLI
- Management Commands:
```
  builder     Manage builds
  config      Manage Docker configs
  container   Manage containers
  context     Manage contexts
  image       Manage images
  manifest    Manage Docker image manifests and manifest lists
  network     Manage networks
  node        Manage Swarm nodes
  plugin      Manage plugins
  secret      Manage Docker secrets
  service     Manage services
  stack       Manage Docker stacks
  swarm       Manage Swarm
  system      Manage Docker
  trust       Manage trust on Docker images
  volume      Manage volumes
```

Commands:
```
  create      Create a new container
  rm          Remove one or more containers
  start       Start one or more stopped containers  
  restart     Restart one or more containers
  stop        Stop one or more running containers    
  kill        Kill one or more running containers  
  pause       Pause all processes within one or more containers
  unpause     Unpause all processes within one or more containers
  rename      Rename a container
  update      Update configuration of one or more containers

  exec        Run a command in a running container
  run         Run a command in a new container
  cp          Copy files/folders between a container and the local filesystem
  export      Export a container's filesystem as a tar archive 
  attach      Attach local standard input, output, and error streams to a running container
  
  ps          List containers
  top         Display the running processes of a container
  logs        Fetch the logs of a container
  stats       Display a live stream of container(s) resource usage statistics  
  diff        Inspect changes to files or directories on a container's filesystem
  events      Get real time events from the server
  info        Display system-wide information
  inspect     Return low-level information on Docker objects

  port        List port mappings or a specific mapping for the container
  wait        Block until one or more containers stop, then print their exit codes
```
- Image Commands
```
  images      List images
  build       Build an image from a Dockerfile
  commit      Create a new image from a container's changes
  load        Load an image from a tar archive or STDIN  
  rmi         Remove one or more images    
  save        Save one or more images to a tar archive (streamed to STDOUT by default)
  import      Import the contents from a tarball to create a filesystem image    
  
  tag         Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE  
  history     Show the history of an image
  search      Search the Docker Hub for images  
  
  login       Log in to a Docker registry
  logout      Log out from a Docker registry
  pull        Pull an image or a repository from a registry
  push        Push an image or a repository to a registry
```

