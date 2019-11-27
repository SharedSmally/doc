# [docker Compose](https://docs.docker.com/compose/)

Compose is a tool to define and run multi-container Docker applications: use a YAML file to configure your application’s services. 
With a single command to create and start all the services from the configuration.

Using Compose is basically a three-step process:
- Define the app’s environment with a Dockerfile 
- Define the services that make up app in ```docker-compose.yml``` so they can be run together in an isolated environment.
- Run ```docker-compose up``` and Compose starts and runs the entire app.
```
version: '3'
services:
  web:
    build: .
    ports:
    - "5000:5000"
    volumes:
    - .:/code
    - logvolume01:/var/log
    links:
    - redis
  redis:
    image: redis
volumes:
  logvolume01: {}
```
## [compose file format](https://docs.docker.com/compose/compose-file/)
The Compose file is a YAML file defining services, networks and volumes. The default path for a Compose file is ./docker-compose.yml.
