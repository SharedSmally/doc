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

## gcc compile:
```
$ docker run --rm  -t -d --name gcc -v ~/test:/test gcc:latest
$ docker exec -it gcc bash   # login container
$ docker exec gcc g++ -o /test/test1 /test/test1.cc
$ docker exec gcc test/test1 
```

