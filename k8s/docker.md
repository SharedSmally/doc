# [Docker](https://docs.docker.com)
- docker engine (Docker daemon: [dockerd](https://docs.docker.com/engine/reference/commandline/dockerd/))
- docker client ([docker](https://docs.docker.com/engine/reference/commandline/cli/))

Run docker without sudo:
```
$sudo usermod -a -G docker `whoami`
$newgrp docker
$docker ps
```

## [Reference](https://docs.docker.com/reference/)
- [Docker File Format](https://docs.docker.com/engine/reference/builder/)
- [docker CLI](https://docs.docker.com/engine/reference/commandline/cli/)
```
$ docker
Usage: docker [OPTIONS] COMMAND [ARG...]
       docker [ --help | -v | --version ]
```
         - VM
         - Images
         - Container
         ![container lifecycle]https://medium.com/@nagarwal/lifecycle-of-docker-container-d2da9f85959)
    
- [docker API](https://docs.docker.com/engine/api/v1.40/): in OpenAPI format
    - Errors
    - Versioning
    - Authentication
    - Containers      
         - List containers
         - Create/Kill/Remove/Delete a container
         - Start/Stop/Restart a container
         - Update/Rename/Resize a container
         - Pause/Unpause a container
         - Export/Wait for a container
         - Attach to a container or via a websocket
         - Inspect a container
         - List processes running inside a container
         - Get container logs
         - Get changes on a container’s filesystem          
         - Get container stats based on resource usage
         - Get information about files in a container
         - Get an archive of a filesystem resource in a container
         - Extract an archive of files or folders to a directory in a container
    - Images      
         - List Images
         - Build/Create/Remove/Delete/Delete cache
         - Push/Tag/Search an image
         - Inspect an image/Get the history of an image  
         - Export/Export/Import
    - Networks
         - List networks
         - Create/Remove/Delete/Inspect a network
         - Connect/Disconnect a container to a network
    - Volumes
         - List volumes
         - Create/Remove/Delete/Inspect a volume
    - Exec
         - Create/Start/Resize/Inspect an exec instance
    - Swarm
         - Initialize/Join/Leave/Update/Lock/Unlock/Inspect
    - Nodes
         - List/Inspect/Delete/Update a node
    - Services
         - List/Create/Inspect/Delete/Update/Get service logs
    - Tasks
         - List tasks/Inspect a task/ Get task logs
    - Secrets
         - List secrets/Create/Inspect/Delete/Update a secret
    - Configs
         - List configs/Create/Inspect/Delete/Update a Config
    - Plugins
         - List plugins
         - Get plugin privileges
         - Create/Install/Config/Inspect/Remove a plugin
         - Enable/Disable/Upgrade/Push a plugin
    - System    
         - Check auth configuration
         - Get system/data usage information
         - Monitor events
    - Distribution
         - Get image information from the registry
    - Session
