# container
- [docker-engine](https://www.docker.com/products/docker-engine) is the higher level component which manages a bunch of things such as orchestration, managing volumes, networking, scaling and so o
- [containerd](https://containerd.io/) is a container runtime which can manage a complete container lifecycle - from image transfer/storage to container execution, supervision and networking.
- [container-shim]() handle headless containers, meaning once runc initializes the containers, it exits handing the containers over to the container-shim which acts as some middleman.
- [runc](https://github.com/opencontainers/runc) is lightweight universal run time container, which abides by the OCI specification. runc is used by containerd for spawning and running containers according to OCI spec. It is also the repackaging of libcontainer.
- [grpc](https://grpc.io/) used for communication between containerd and docker-engine.
- [OCI](https://www.opencontainers.org/) maintains the OCI specification for runtime and images. The current docker versions support OCI [image](https://github.com/opencontainers/image-spec) and [runtime](https://github.com/opencontainers/runtime-spec) specs.

## [docker components](http://alexander.holbreich.org/docker-components-explained/)

## docker Architecture:
Prior to the version 1.11, Docker engine was used to manage volumes, networks, containers, images etc.. Now, the Docker architecture is broken into four components: 
- Docker engine(dockerd): listens for Docker API requests and manages host's Container life-cycles by utilizing contanerd
- containerd: take main responsibilty of managing containers life-cycle
- containerd-shm: 
- runC

The binaries are respectively called docker, docker-containerd, docker-containerd-shim, and docker-runc.

To run a container, Docker engine creates the image, pass it to containerd. containerd calls containerd-shim that uses runC to run the container. Then, containerd-shim allows the runtime (runC in this case) to exit after it starts the container 

![containerd](https://containerd.io/img/architecture.png)
![architecture](https://i.stack.imgur.com/5aXF6.png)

