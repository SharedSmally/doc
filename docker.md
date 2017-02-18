docker
======

## Docker VM (hold docker container)
- VM operations:

**docker-machine _create | rm | start | stop | restart | kill_**

- VM status:

**docker-machine _active | config | env | ip | url | status | ls | inspect_**

- VM setup:

**docker-machine _upgrade | regenerate-cert | provision_**

- VM interaction:

**docker-machine _ssh|scp_**

- Login docker VM:
```
   docker-machine ssh default
   login to docker VM of "default":
   docker@default:~$ sudo -i
    ...........
   root@default:~# 
   
   The docker related files (images) are stored in /mnt/sda1/var/lib/docker. 
```

## [Docker Image](https://docs.docker.com/engine/tutorials/dockerimages/)
 - Image docker commands
```
    images    List images
    build     Build an image from a Dockerfile
    tag       Tag an image into a repository
    rmi       Remove one or more images
    
    load      Load an image from a tar archive or STDIN
    save      Save one or more images to a tar archive (streamed to STDOUT by default)
    
    commit    Create a new image from a container's changes
    
    history   Show the history of an image
    search    Search the Docker Hub for images

    login     Log in to a Docker registry.
    pull      Pull an image or a repository from a registry
    push      Push an image or a repository to a registry
    logout    Log out from a Docker registry.
```    
- Example:

   - List Images
   
     $ docker images
     
   - Create Image: Image name(repository:tag or ID)
   
     $ docker build -f dockerfiles/Dockerfile.prod  -t myapp_prod:v1 . 
     
   - Tag Image
   
     $ docker tag 5db5f8471261 user/test1:devel
     
   - Create a new container and login (outside of container)
   
     $ docker run -i -t 5db5f8471261
     
   - Commit container changes to a new Image (outside of container):
   
     $ docker commit 5db5f8471261
     $ docker commit [OPTIONS] CONTAINER [REPOSITORY[:TAG]]

## [Docker Container](~/.docker)
- Container docker commands
```
    ps        List containers:   docker ps -a  (all)
    create    Create a new container:   docker create [OPTIONS] IMAGE [CMD] [ARGS]
    rm        Remove one or more containers:   docker rm CONTAINER
    rename    Rename a container:    docker renamte CONTAINER NEW_NAME
    restart   Restart a container:   
    start     Start one or more stopped containers: docker start CONTAINER
    stop      Stop one or more running containers
    kill      Kill one or more running containers
    pause     Pause all processes within one or more containers
    unpause   Unpause all processes within one or more containers
    attach    Attach to a running container
    wait      Block until a container stops, then print its exit code
    
    run       Run a command in a new container 
    exec      Run a command in a running container

    export    Export a container's filesystem as a tar archive:  docker export -o FILE CONTAINER 
    import    Import the contents from a tarball to create a filesystem image:  docker import [OPTIONS] file|URL|- [IMAGE]

    info      Display system-wide information:     docker info
    version   Show the Docker version information: docker version

    inspect   Return low-level information on a container, image or task
    diff      Inspect changes on a container's filesystem
    port      List port mappings or a specific mapping for the container
    stats     Display a live stream of container(s) resource usage statistics
    top       Display the running processes of a container    
    events    Get real time events from the server
    logs      Fetch the logs of a container:     docker logs [options] CONTAINER
    
    network   Manage Docker networks:  docker network [create|rm|connect|disconnect|inspect|ls] [OPTIONS]
    volume    Manage Docker volumes:   docker volume [create|rm|inspect|ls] [OPTIONS]
    cp        Copy files/folders between a container and the local filesystem
                  docker cp CONTAINER:SRC_PATH DEST_PATH
                  docker cp SRC_PATH CONTAINER:DEST_PATH 
    update    Update configuration of one or more containers, such as CPU, memory resource:
                  docker update CONTAINER [options]

    service   Manage Docker services:   dpcler service [create|inspect|ps|ls|rm|scale|update]
    node      Manage Docker Swarm nodes
    swarm     Manage Docker Swarm
        
```
- container operations:

**docker _create | start | stop | restart | kill | pause | unpause | update_**
```
    docker run -t -i ubuntu:14.04 /bin/bash
```
- containers status:

**docker _ps | top | logs | stats | load | export_**

- container config:

**docker _port | network | service | volume | cp_**

- container interaction:

**docker _run | exec_**
docker run -t -i training/sinatra /bin/bash : create a new container from image

docker exec -it container_name bash:    login running container

## Docker File:  [Reference](https://docs.docker.com/engine/reference/builder/)

- Build Image from docker file:
```
$ docker build .
$ docker build -f /path/to/a/Dockerfile .
```
  - Directive
```
  # directive=value1
```
  - FROM*: sets the Base Image for subsequent instructions (Each FROM create one image)
```
   FROM <image>
   FROM <image>:<tag>
   FROM <image>@<digest>
```

  - Run: execute any commands in a new layer on top of the current image and commit the results.
```
   RUN <command> (shell form, the command is run in a shell [/bin/sh -c on Linux or cmd /S /C on Windows])
   RUN ["executable", "param1", "param2"] (exec form)
```

  - CMD*: provide defaults for an executing container. only one CMD instruction in a Dockerfile
```  
  CMD ["executable","param1","param2"] (exec form, this is the preferred form)
  CMD ["param1","param2"] (as default parameters to ENTRYPOINT)
  CMD command param1 param2 (shell form)
```  
  - ENTRYPOINT*: provide defaults for an executing container. only one CMD instruction in a Dockerfile
```  
   ENTRYPOINT ["executable", "param1", "param2"] (exec form, preferred)
   ENTRYPOINT command param1 param2 (shell form)
```  

  - Expose: informs Docker that the container listens on the specified network ports at runtime
```
    EXPOSE <port> [<port>...]
```
  - VOLUME:creates a mount point and marks it as holding externally mounted volumes from native host or other containers.
```
   VOLUME ["/data"]
```
  - ADD: copy new files, directories or remote file URLs from \<src\> and adds them to the container filesystem at the path \<dest\>.
```
   ADD <src>... <dest>
   ADD ["<src>",... "<dest>"] (required for paths containing whitespace)
ex:
   ADD hom* /mydir/        # adds all files starting with "hom"
   ADD hom?.txt /mydir/    # ? is replaced with any single character, e.g., "home.txt"
```
  - COPY: copy new files, directories from \<src\> and adds them to the container filesystem at the path \<dest\>.
```
   COPY <src>... <dest>
   COPY ["<src>",... "<dest>"] (required for paths containing whitespace)
ex:
   COPY test relativeDir/   # adds "test" to `WORKDIR`/relativeDir/
   COPY test /absoluteDir/  # adds "test" to /absoluteDir/
```
  - ENV
```  
  ENV <key> <value>
  ENV <key>=<value> ...
such as:
  ENV abc=hello
  ENV abc=bye def=$abc
  ENV ghi=$abc
```
  - User: sets the user name or UID to use for running any RUN, CMD and ENTRYPOINT
```
   USER daemon
```
  - WORKDIR: sets the working directory for any RUN, CMD, ENTRYPOINT, COPY and ADD.
```
   WORKDIR /path/to/workdir
```
  - Label:  adds metadata to an image
```
  LABEL <key>=<value> <key>=<value> <key>=<value> ...
```
  - ARG:  defines a variable passed at build-time to the builder using --build-arg \<varname\>=\<value\> flag
```
   ARG <name>[=<default value>]
```
  - STOPSIGNAL:sets the system call signal that will be sent to the container to exit
```  
   STOPSIGNAL signal
```
  - HEALTHCHECK: tells Docker how to test a container to check that it is still working
```
   HEALTHCHECK [OPTIONS] CMD command (check container health by running a command inside the container)
   HEALTHCHECK NONE (disable any healthcheck inherited from the base image)
   
   The options that can appear before CMD are:
     --interval=DURATION (default: 30s)
     --timeout=DURATION (default: 30s)
     --retries=N (default: 3)
  
  ex.   
    HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl -f http://localhost/ || exit 1
```

  - SHELL: allows the default shell used for the shell form of commands to be overridden. 
```
   SHELL ["executable", "parameters"]
```

  - ONBUILD: adds to the image a trigger instruction to be executed at a later time, when the image is used as the base for another build.
```  
   ONBUILD [INSTRUCTION]
ex.   
   [...]
   ONBUILD ADD . /app/src
   ONBUILD RUN /usr/local/bin/python-build --dir /app/src
   [...]
```

```
    FROM ubuntu:14.04
    RUN apt-get update
    RUN apt-get install -y curl
    EXPOSE <port> [<port>...]
    ENV PATH /usr/local/postgres-$PG_MAJOR/bin:$PATH
    
    1 FROM ubuntu
    2 ARG CONT_IMG_VER
    3 ENV CONT_IMG_VER v1.0.0
    4 RUN echo $CONT_IMG_VER

# Multiple images example
# VERSION               0.1
FROM ubuntu
RUN echo foo > bar
# Will output something like ===> 907ad6c2736f

FROM ubuntu
RUN echo moo > oink
# Will output something like ===> 695d7793cbe4

# There are two images, 907ad6c2736f with /bar, and 695d7793cbe4 with /oink.

    $ docker build --build-arg CONT_IMG_VER=v2.0.1 Dockerfile
```

When the Docker container starts, only the **CMD** command is run. The only processes that will be running inside the container is the CMD command, and all processes that it spawns.

## [Docker Compose](https://docs.docker.com/compose/overview/):
Compose has commands for managing the whole lifecycle of your application:
- Start, stop and rebuild services
- View the status of running services
- Stream the log output of running services
- Run a one-off command on a service

## [Compose Reference](https://docs.docker.com/compose/compose-file/)
The Compose file is a YAML file defining services, networks and volumes. The default path for a Compose file is ./docker-compose.yml
- Service configuration reference

A service definition contains configuration applied to each container started for that service, much like passing command-line parameters to **docker run**.

- Network configuration reference

A network definition is analogous to **docker network create**.

- Volume configuration reference

A volume definition is analogous to **docker volume create**.

- Variable substitution

Both **$VARIABLE** and **${VARIABLE}** syntax are supported:
- ${VARIABLE:-default} will evaluate to default if VARIABLE is unset or empty in the environment.
- ${VARIABLE-default} will evaluate to default only if VARIABLE is unset in the environment.
```
web:
  build: .
  ports:
    - "${EXTERNAL_PORT}:5000"

$ unset EXTERNAL_PORT
$ echo "EXTERNAL_PORT=6000" > .env
$ docker-compose up          # EXTERNAL_PORT will be 6000
$ export EXTERNAL_PORT=7000
$ docker-compose up          # EXTERNAL_PORT will be 7000
```
