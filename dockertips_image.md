# docker
Docker is based on so called images. These images are comparable to virtual machine images and 
contain files, configurations and installed programs. And just like virtual machine images you 
can start instances of them. A running instance of an image is called container. 
ou can make changes to a container (e.g. delete a file), but these changes will not affect the image. 
However, you can create a new image from a running container (and all it changes) 
using *docker commit <container-id> <image-name>*.

## Export
Export is used to persist a container (not a image). It need the container id:
```
docker ps -a
docker export <CONTAINER ID> > /home/exportImg.tar
cat /home/exportImg.tar | sudo docker import - busybox-1-export:latest    #import image
```
The result is a TAR-file. The file is a little smaller, it is flattened, and lost its history and meta-data.
The exported-imported image has lost all of its history. 

## Save
Save is used to persist an image (not a container). It needs the image name:
```
docker images
docker save busybox-1 > /home/saveImg.tar
docker load < /home/saveImg.tar
```
The result is a TAR-file. The saved-loaded image still have its history and layers.
