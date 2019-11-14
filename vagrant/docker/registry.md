# Docker Image Registry
The contents of the /var/lib/docker directory vary depending on the driver Docker is using for storage. By default this will be aufs but can fall back to overlay, overlay2, btrfs, devicemapper or zfs depending on your kernel support. 

Actually, Docker images are stored in two files as shown by following command
```
$ docker info
```
- Data file: /var/lib/docker/devicemapper/devicemapper/data
- Metadata file: /var/lib/docker/devicemapper/devicemapper/metadata

## [Deploy image Registry] (https://docs.docker.com/registry/deploying/)
### Docker Images operations: ls; import; pull/push;  build/prune/save/rm; load/save; history/inspect/tag
- List images
```
docker image ls
```
### Run a local registry
```
$ docker run -d -p 5000:5000 --restart=always --name registry registry:2
```
The registry is now ready to use.

### Copy an image from Docker Hub to your registry
- Pull the ubuntu:16.04 image from Docker Hub.
```
$ docker pull ubuntu:16.04
```
- Tag the image as localhost:5000/my-ubuntu. This creates an additional tag for the existing image. When the first part of the tag is a hostname and port, Docker interprets this as the location of a registry, when pushing.
```
$ docker tag ubuntu:16.04 localhost:5000/my-ubuntu
```

- Push the image to the local registry running at localhost:5000:
```
$ docker push localhost:5000/my-ubuntu
```
- Remove the locally-cached ubuntu:16.04 and localhost:5000/my-ubuntu images, so that you can test pulling the image from your registry. This does not remove the localhost:5000/my-ubuntu image from your registry.
```
$ docker image remove ubuntu:16.04
$ docker image remove localhost:5000/my-ubuntu
```
- Pull the localhost:5000/my-ubuntu image from your local registry.
```
$ docker pull localhost:5000/my-ubuntu
```

### Stop a local registry
- To stop the registry, use the same docker container stop command as with any other container.
```
$ docker container stop registry
```
- To remove the container, use docker container rm.
```
$ docker container stop registry && docker container rm -v registry
```

## Build docker image
```
docker build -t webapp .
```
