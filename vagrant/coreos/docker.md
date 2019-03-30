## run docker in centos:
- dockers: https://hub.docker.com/
```
$ docker logs nexus
# docker ps -a  # list containers
$ docker exec -it <container_name> /bin/sh  #login container
```

- [Nexus OSS 3](https://hub.docker.com/r/sonatype/nexus3):

To run, binding the exposed port 8081 to the host.
```
$ docker run -d -p 8081:8081 --name nexus sonatype/nexus3
```
To test:
```
$ curl -u admin:admin123 http://localhost:8081/service/metrics/ping
```
Default credentials are: *admin / admin123*. In web browser, use http://192.168.33.11:8081/.

- [Jenkins](https://hub.docker.com/_/jenkins):

Store the workspace in /var/jenkins_home or /var/jenkins_home is mapped to /your/home:
```
docker run -p 8080:8080 -p 50000:50000 jenkins
docker run -p 8080:8080 -p 50000:50000 -v /your/home:/var/jenkins_home jenkins
docker run -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins --name myjenkins 
```
Ensure that /your/home is accessible by the jenkins user in container (jenkins user - uid 1000) or use -u some_other_user parameter with docker run.

- [nginx](https://hub.docker.com/_/nginx)
```
$ docker run -p 192.168.33.11:80:8080 nginx
```
