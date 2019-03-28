docker
======
## [docker] (https://github.com/wsargent/docker-cheat-sheet)

## [Docker Toolbox](https://www.docker.com/technologies/overview)
Docker Toolbox includes docker engine, docker-machine(connect to dock hosts), and docker-compose. For each docker host, the related files are stored in ~/.docker/machine/machines/xxx, which has ssh key id_rsa, and NAT network: (127.0.0.1:55420=>guest:22).
- cp id_rsa to ~/.ssh; 
- run **ssh docker@127.0.0.1 -p 55420** to login the docker host; 
- run **docker exec -it container_name bash** to login the docker container.
- Login as root: **docker exec -u 0 -it mycontainer bash**
- Install pkg: **apt-get update; apt-get install xxx**

## [Kitematic](https://kitematic.com/)
Kitematic is the GUI for dockers. It can be installed from Docker Toolbox.

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
```
services:
  proxy:
    build: ./proxy
    networks:
      - outside
      - default
  app:
    build: ./app
    networks:
      - default
```
A service definition contains configuration applied to each container started for that service, much like passing command-line parameters to **docker run**.

- Network configuration reference

A network definition is analogous to **docker network create**.
```
networks:
  outside:
    external: true
```

- driver: overlay  

Specify which driver should be used for this network. It will be **bridge** on a single host and **overlay** on a Swarm

- driver_opts: optional

Specify a list of options as key-value pairs to pass to the driver for this network

```
  driver_opts:
    foo: "bar"
    baz: 1
```

- enable_ipv6:

Enable IPv6 networking on this network.

 - ipam
 
Specify custom IPAM config. This is an object with several properties, each of which is optional:
    - driver: Custom IPAM driver, instead of the default.
    - config: A list with zero or more config blocks, each containing any of the following keys:
         - subnet: Subnet in CIDR format that represents a network segment
```
ipam:
  driver: default
  config:
    - subnet: 172.28.0.0/16
```

- internal

By default, Docker also connects a bridge network to it to provide external connectivity. If you want to create an externally isolated overlay network, you can set this option to true.

- external

If set to true, specifies that this network has been created outside of Compose. docker-compose up will not attempt to create it, and will raise an error if it doesn’t exist.


  
- Volume configuration reference

A volume definition is analogous to **docker volume create**.
```
volumes:
  data:
    external:
      name: actual-name-of-volume
```

- driver: 

Specify which volume driver should be used for this volume. Defaults to whatever driver the Docker Engine has been configured to use, which in most cases is local.


- driver_opts: optional

Specify a list of options as key-value pairs to pass to the driver for this network

```
  driver_opts:
    foo: "bar"
    baz: 1
```

- internal

By default, Docker also connects a bridge network to it to provide external connectivity. If you want to create an externally isolated overlay network, you can set this option to true.

- external

If set to true, specifies that this network has been created outside of Compose. docker-compose up will not attempt to create it, and will raise an error if it doesn’t exist.

      
- Variable substitution

Both **$VARIABLE** and **${VARIABLE}** syntax are supported:
- ${VARIABLE:-default} will evaluate to default if VARIABLE is unset or empty in the environment.
- ${VARIABLE-default} will evaluate to default only if VARIABLE is unset in the environment.

The default values for environment variables can be set using a .env file, which Compose will automatically look for. You can use a **$$ (double-dollar sign)** when your configuration needs a literal dollar sign.

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

## tips: 
### RUN vs CMD vs ENTRYPOINT in dockfile
- RUN executes command(s) in a new layer and creates a new image. E.g., it is often used for installing software packages.
- CMD sets default command and/or parameters, which can be overwritten from command line when docker container runs.
- ENTRYPOINT configures a container that will run as an executable.
