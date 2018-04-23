## [MySQL](https://hub.docker.com/r/mysql/mysql-server/)
- [color xterm](http://vim.wikia.com/wiki/256_colors_in_vim)
- Connect to MySQL:

```
docker exec -it NAME bash

docker exec -it NAME mysql -uUSER -pPASSWORD
mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'newpassword';
mysql> show databases;  create/drop database DBNAME;
mysql> use mysql;
mysql> show tables;   create/drop table TBLNAME;  drop table if exists TBLNAME;

mysql -u username -p database_name < file.sql

docker start mysql1     #start
docker restart mysql1   #restart
docker stop mysql1      #stop
docker rm mysql1        #delete

docker cp users.sql NAME:/
docker exec -it NAMR "mysql -uroot -pPASSWROD < /users.sql"
```
- Sample mysql Docker 
```
# ROOT PASSWORD
ENV MYSQL_ROOT_PASSWORD=mypassword

#ENV MYSQL_DATABASE=sampledb
ENV MYSQL_USER=sample-username
ENV MYSQL_PASSWORD=sapassword

ENV MYSQL_DATA_DIR=/var/lib/mysql \
    MYSQL_RUN_DIR=/run/mysqld \
    MYSQL_LOG_DIR=/var/log/mysql

ADD ["db_dump.sql", "/tmp/dump.sql"]

RUN /etc/init.d/mysql start && \
        mysql -u root -p$MYSQL_ROOT_PASSWORD  -e "GRANT ALL PRIVILEGES ON *.* TO 'comeon'@'%' IDENTIFIED BY 'password';FLUSH PRIVILEGES;" && \
        mysql -u root -p${MYSQL_ROOT_PASSWORD}  < /tmp/dump.sql

#PORT
EXPOSE 3306
```

## Postgres
- 
env POSTGRES_PASSWORD xxx

docker exec -it NAME bash

docker exec -it NAME postgres -h localhost -U postgres

        sudo su - postgres
        psql -U postgres
        psql -u test -d testdb

# Create users
create database testdb;
create user test with password 'test1234';
grant all privileges on database testdb to test;


## Docker run vs exec
- run
Use this to run a command in a new container. It suits the situation where you do not have a container running, and you want to create one, start it and then run a process on it.
```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```

- exec
exec
This is for when you want to run a command in an existing container. This is better if you already have a container running and want to change it or obtain something from it. For example, if you are using docker-compose you will probably spin-up multiple containers and you may want to access one or more of them once they are created.
```
docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
```
