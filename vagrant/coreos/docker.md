## run docker in centos:
- Nexus OSS 3:

To run, binding the exposed port 8081 to the host.
```
$ docker run -d -p 8081:8081 --name nexus sonatype/nexus3
```
To test:
```
$ curl -u admin:admin123 http://localhost:8081/service/metrics/ping
```
