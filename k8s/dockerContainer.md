# docker Container management
/var/lib/docker:
```
docker container COMMAND
Commands:
  create      Create a new container
  rm          Remove one or more containers

  start       Start one or more stopped containers
  restart     Restart one or more containers  
  stop        Stop one or more running containers
  kill        Kill one or more running containers
  
  run         Run a command in a new container  
  exec        Run a command in a running container
  
  prune       Remove all stopped containers
  rename      Rename a container

  pause       Pause all processes within one or more containers
  unpause     Unpause all processes within one or more containers
  
  update      Update configuration of one or more containers
  wait        Block until one or more containers stop, then print their exit codes

  inspect     Display detailed information on one or more containers
  stats       Display a live stream of container(s) resource usage statistics
  
  attach      Attach local standard input, output, and error streams to a running container
  commit      Create a new image from a container's changes
  cp          Copy files/folders between a container and the local filesystem
  
  diff        Inspect changes to files or directories on a container's filesystem

  export      Export a container's filesystem as a tar archive
  
  logs        Fetch the logs of a container
  ls          List containers
  port        List port mappings or a specific mapping for the container
  top         Display the running processes of a container
```

## [docker run](https://docs.docker.com/engine/reference/commandline/run/)
 docker containers exit if there is no running application in the container.
- Start container with login: 
```
docker run -it --name NAME IMAGE
```
    - -it: --interactive --tty
    - --attach , -a 		Attach to STDIN, STDOUT or STDERR
    - --detach , -d     Run container in background and print container ID
    - --rm              Automatically remove the container when it exits
    - --publish , -p 		Publish a container’s port(s) to the host
    - --network 		    Connect a container to a network
    - --mount 		      Attach a filesystem mount to the container
    - --volume , -v 		Bind mount a volume
    - --ipc 	        	IPC mode to use
    - --net 		        Connect a container to a network
    - --pid 		        PID namespace to use
    - --userns 		      User namespace to use
    - --uts 		        UTS namespace to use
- [ create a set of containers running in a single set of namespaces](https://www.ianlewis.org/en/what-are-kubernetes-pods-anyway) 
    
## Common commands
- Show containers in running state: ```docker ps```
- Show containers in all states: ```docker ps -a```
- Execute command without exited:```docker run -t -d <image-name>```.  -d for detached mode, it means that a Docker container runs in the background of your terminal. It does not receive input or display output. can use -dit.
- [Run alpine](https://stackoverflow.com/questions/45638784/how-to-retain-docker-alpine-container-after-exit-is-used/51133128#51133128):```docker run -d --name alpine alpine tail -f /dev/null```
- sh into the alpine container: ```docker exec -it alpine sh```. -it ensures that bash or sh can be allocated to a pseudo terminal.
- Specify port: ```docker run -t -d -p <port-no> <image-name>```
- Log in to the container shell:```docker exec -it <container id> /bin/bash```
- Add the ENTRYPOINT in docker file:
```
while true
do
    echo "Press [CTRL+C] to stop.."
    sleep 1
done
```
- Execute a command in a running container:```docker exec [OPTIONS] CONTAINER COMMAND [ARG...]```  

## [Container Details](https://www.ianlewis.org/en/what-are-kubernetes-pods-anyway)
Containers are normal processes that are executed using two features of the Linux kernel called namespaces and cgroups. Namespaces allow you to provide a "view" to the process that hides everything outside of those namespaces, thus giving it its own environment to run in. This makes it so processes can't see or interfere with other processes. The Namespaces include:

    - Hostname
    - Process IDs
    - File System
    - Network interfaces
    - Inter-Process Communication (IPC)

A process can use all the resources on the physical machine it runs on, thus starving other processes for resources. In order to limit that, Linux has a feature called cgroups. Processes can be run in a cgroup much like a namespace but the cgroup limits the resources that the process can use. These resources include CPU, RAM, block I/O, network I/O etc. CPU can be limited by milli-cores (a 1000th of a core), and/or bytes of RAM. The process itself can run as normal but it will only be able to use as much CPU as allowed by the cgroup and will get out-of-memory errors if it exceeds the memory limit set on the cgroup.
![containers](https://storage.googleapis.com/static.ianlewis.org/prod/img/766/containers.png)

```
$ docker run -d --name ghost --net=container:nginx --ipc=container:nginx --pid=container:nginx ghost
```
![nginx container can proxy requests directly on localhost to our container](https://storage.googleapis.com/static.ianlewis.org/prod/img/766/ghost_.png)
 Multiple processes can be combined with the same namespaces and cgroups. Pods can specify the multiple containers to run and Kubernetes automates setting up the namespaces and cgroups in the right way.
 
When the pod containers are set up, each process "feels" like it's running on the same machine. They can talk to each other on localhost, they can use shared volumes. They can even use IPC or send each other signals like HUP or TERM (With shared PID namespaces):
![pod containers](https://storage.googleapis.com/static.ianlewis.org/prod/img/766/pods.png)

- [Pause Container](https://www.ianlewis.org/en/almighty-pause-container) in K8s cluster
Deploy a group of applications that are partially isolated and partially share an environment. In Linux, a new process process inherits its namespaces from the parent process. The way that running a process in a new namespace is by "unsharing" the namespace with the parent process thus creating a new namespace. In Kubernetes, the pause container serves as the "parent container" for all of the containers in the pod. The pause container has two core responsibilities. First, it serves as the basis of Linux namespace sharing in the pod. And second, with PID (process ID) namespace sharing enabled, it serves as PID 1 for each pod and reaps zombie processes:
```
docker run -d --name pause -p 8080:80 gcr.io/google_containers/pause-amd64:3.0   # parent container
$ docker run -d --name nginx -v `pwd`/nginx.conf:/etc/nginx/nginx.conf --net=container:pause --ipc=container:pause --pid=container:pause nginx    # child ngix container
$ docker run -d --name ghost --net=container:pause --ipc=container:pause --pid=container:pause ghost #child ghost container
```
The pause container is used as the container whose namespaces to join. When access http://localhost:8080/, it is able to see ghost running through an nginx proxy because the network namespace is shared among the pause, nginx, and ghost containers.

## gcc compile:
```
$ docker run --rm  -t -d --name gcc -v ~/test:/test gcc:latest
$ docker exec -it gcc bash   # login container
$ docker exec gcc g++ -o /test/test1 /test/test1.cc
$ docker exec gcc test/test1 
```

