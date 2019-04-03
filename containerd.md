# container
- [containerd](https://containerd.io/) is a container runtime which can manage a complete container lifecycle - from image transfer/storage to container execution, supervision and networking.
- [container-shim]() handle headless containers, meaning once runc initializes the containers, it exits handing the containers over to the container-shim which acts as some middleman.
- [runc](https://github.com/opencontainers/runc) is lightweight universal run time container, which abides by the OCI specification. runc is used by containerd for spawning and running containers according to OCI spec. It is also the repackaging of libcontainer.
- [grpc](https://grpc.io/) used for communication between containerd and docker-engine.
- [OCI](https://www.opencontainers.org/) maintains the OCI specification for runtime and images. The current docker versions support OCI image and runtime specs.
## Architecture:
![architecture](https://i.stack.imgur.com/5aXF6.png)
