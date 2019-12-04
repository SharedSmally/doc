# [docker-machine](https://docs.docker.com/machine/get-started/)
Create and manage machines running docker
```
Usage: docker-machine.exe [OPTIONS] COMMAND [arg...]

Commands:
  active                Print which machine is active
  config                Print the connection config for machine
  create                Create a machine
  env                   Display the commands to set up the environment for the Docker client
  inspect               Inspect information about a machine
  ip                    Get the IP address of a machine
  kill                  Kill a machine
  ls                    List machines
  provision             Re-provision existing machines
  regenerate-certs      Regenerate TLS Certificates for a machine
  restart               Restart a machine
  rm                    Remove a machine
  ssh                   Log into or run a command on a machine with SSH.
  scp                   Copy files between machines
  mount                 Mount or unmount a directory from a machine with SSHFS.
  start                 Start a machine
  status                Get the status of a machine
  stop                  Stop a machine
  upgrade               Upgrade a machine to the latest version of Docker
  url                   Get the URL of a machine
  version               Show the Docker Machine version or a machine docker version
  help                  Shows a list of commands or help for one command
```

## Common Commands
```
docker-machine ls/active
docker-machine create
docker-machine start/restart
docker-machine inspect/status/env/config/ip
docker-machine provision/scp/mount
docker-machine scp
docker-machine ssh
docker-machine stop/kill
docker-machine rm
```
