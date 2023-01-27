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
```
      FROM [--platform=<platform>] <image> [AS <name>]
      FROM [--platform=<platform>] <image>[:<tag>] [AS <name>]
      FROM [--platform=<platform>] <image>[@<digest>] [AS <name>]
```      
- RUN
```
    RUN <command> (shell form, the command is run in a shell,/bin/sh -c on Linux or cmd /S /C on Windows)
    RUN ["executable", "param1", "param2"] (exec form)
    RUN --mount=[type=<TYPE>][,option=<value>[,option=<value>]...]
```
- CMD: only one CMD in one docker file,  provide defaults for an executing container.
```
    CMD ["executable","param1","param2"] (exec form, the preferred form)
    CMD ["param1","param2"] (as default parameters to ENTRYPOINT)
    CMD command param1 param2 (shell form)
```
- LABEL:  LABEL <key>=<value> <key>=<value> <key>=<value> ...
- EXPOSE: EXPOSE <port> [<port>/<protocol>...]
- ENV:  ENV <key>=<value> ...     #ENV abc=bye def=$abc
     - ${variable_name};
     - ${variable:-word}: If not set, word is the result.
     - ${variable:+word}: If set, word is the result, otherwise is the empty string.
- ADD:  copies new files, directories or remote file URLs, accept *, ? 
```
   ADD [--chown=<user>:<group>] [--checksum=<checksum>] <src>... <dest>
   ADD [--chown=<user>:<group>] ["<src>",... "<dest>"]
   ADD [--keep-git-dir=<boolean>] <git ref> <dir>      
```      
- COPY
```
   COPY [--chown=<user>:<group>] <src>... <dest>
   COPY [--chown=<user>:<group>] ["<src>",... "<dest>"]
```
- ENTRYPOINT:  configure a container that will run as an executable.
```
  ENTRYPOINT ["executable", "param1", "param2"]
  ENTRYPOINT command param1 param2
```      
- VOLUME:  VOLUME ["/data"]
- USER:  USER <user>[:<group>]/<UID>[:<GID>]
- WORKDIR: WORKDIR /path/to/workdir  # dir for RUN, CMD, ENTRYPOINT, COPY and ADD
- ARG:  ARG <name>[=<default value>] # variable passed at build-time using --build-arg <varname>=<value> flag
     - Predefined ARGs: HTTP_PROXY/ http_proxy/HTTPS_PROXY/https_proxy/FTP_PROXY/ftp_proxy/NO_PROXY/no_proxy/ALL_PROXY/all_proxy
     - Automatic platform ARGs: TARGETPLATFORM/TARGETOS/TARGETARCH/TARGETVARIANT; BUILDPLATFORM/BUILDOS/BUILDARCH/BUILDVARIANT    
- ONBUILD:  ONBUILD <INSTRUCTION>  #trigger instruction
- STOPSIGNAL: STOPSIGNAL signal    #system signal that will be sent to the container to exit.
- HEALTHCHECK
```      
   HEALTHCHECK [OPTIONS] CMD command (check container health by running a command inside the container)
   HEALTHCHECK NONE (disable any healthcheck inherited from the base image      
  OPTIONS:
    --interval=DURATION (default: 30s)
    --timeout=DURATION (default: 30s)
    --start-period=DURATION (default: 0s)
    --retries=N (default: 3)      
```      
- SHELL: SHELL ["executable", "parameters"]  # default shell used for the shell form of commands 

### ADD vs COPY
- COPY takes in a source and destination. It only copy in a local or directory from the host (the machine-building the Docker image) into the Docker image itself.
- ADD  does that same but in addition, it also supports 2 other sources. 
     - A URL instead of a local file/directory.
     - Extract tar from the source directory into the destination.    

### RUN vs CMD vs ENTRYPOINT
- RUN: executes commands and creates new image layers.
- CMD: sets the command and its parameters to be executed by default after the container is started. it can be replaced by docker run command line parameters. 
- ENTRYPOINT: configures the command to run when the container starts, Sets default parameters that cannot be overridden while executing Docker containers with CLI parameters.
- SHELL: set the shell command used by the shell form of commands 
When both CMD and ENTRYPOINT are used, the executable is defined with ENTRYPOINT, while CMD specifies the default parameter.
```
FROM ubuntu
ENTRYPOINT ["echo", "Hello"]
CMD ["Abhinav"]      
      
docker build -t entrypoint-cmd .
docker run entrypoint-cmd   => Hello Abhinav
docker run entrypoint-cmd @abhinavd26 =>    Hello @abhinavd26 
      
```
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

###
- exec: run a command in a running container or open a shell session to a running container     
```
$ docker exec -it cranky_spence /bin/bash
$ docker exec cranky_spence /bin/bash -c "uptime; whoami; date"      
```  
- create: creates a fresh new container from a docker image. However, it doesn’t run it immediately.
- start: start any stopped container. If using docker create command to create a container, can start it with this command.
- run: a combination of create and start as it creates a new container and starts it immediately.
