## Install Docker
- Install Docker for windows : https://docs.docker.com/docker-for-windows/install/
- set env for cygwin:(http://www.whiteboardcoder.com/2017/04/installing-docker-on-windows-and-cygwin.html)
```
$ ln -s  "/cygdrive/c/Program Files/Docker/Docker/resources/bin/docker.exe" bin/docker
$ docker container ls

Run in PowerShell:
$ docker run -it --link mysql:mysql --rm mysql sh -c 'exec mysql -h"$MYSQL_PORT_3306_TCP_ADDR" -P"$MYSQL_PORT_3306_TCP_PORT" -uroot -p"$MYSQL_ENV_MYSQL_ROOT_PASSWORD"'
```

### jenkins
- setup: http://192.168.99.100:32770/

### nexus repository [docker](https://github.com/sonatype/docker-nexus)
- http://192.168.99.100:32772/nexus:  The default administrator username and password combination is admin and admin123.

### git ssh server [docker](https://github.com/sonatype/docker-nexus)
- http://192.168.99.100:32772/nexus:  The default administrator username and password combination is admin and admin123.

### mysql docker
- start Mysql docker
In Kitematic/settings, add Environment Variables:
MYSQL_ROOT_PASSWORD xxxxxx

- connect to MySQL instance (mysqlName) from command line:
```
$ docker run -it --link mysqlName:mysql --rm mysql sh -c 'exec mysql -h"$MYSQL_PORT_3306_TCP_ADDR" -P"$MYSQL_PORT_3306_TCP_PORT" -uroot -p"$MYSQL_ENV_MYSQL_ROOT_PASSWORD"'
```
