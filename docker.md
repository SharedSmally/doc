docker
======

## VM
- VM operations:

**docker-machine _create | rm | start | stop | restart | kill_**

- VM status:

**docker-machine _active | config | env | ip | url | status | ls | inspect_**

- VM setup:

**docker-machine _upgrade | regenerate-cert | provision_**

- VM interaction:

**docker-machine _ssh|scp_**

## Container
- image operations:

**docker _build | rmi | tag_**

- images:

**docker _images | history_**

- container operations:

**docker _create | start | stop | restart | kill | pause | unpause | update_**

- containers status:

**docker _ps | top | logs | stats | load | export_**

- container config:

**docker _port | network | service | volume | cp_**

- container interaction:

**docker _run | exec_**

- Hub docker:

**docker _pull | push | login | logout | commit_**


## Docker File:  [Reference](https://docs.docker.com/engine/reference/builder/)

- Build Image from docker file:
```
$ docker build .
```
- Reference

  - FROM:

  - Run

  - Expose

  -

```
    FROM ubuntu:14.04
    RUN apt-get update
    RUN apt-get install -y curl
    EXPOSE <port> [<port>...]
    ENV PATH /usr/local/postgres-$PG_MAJOR/bin:$PATH
```
