## [Postgresql]()

### [Install postgres in centos7](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-postgresql-on-centos-7)
- Installation
```
$ sudo yum install postgresql-server postgresql-contrib -y
$ sudo postgresql-setup initdb  #Create a new PostgreSQL database cluster
# By default, PostgreSQL does not allow password authentication. 
$ sudo vi /var/lib/pgsql/data/pg_hba.conf  # update to allow password authentication
   #replace "ident" with "md5" to allow password authentication
   host    all             all             127.0.0.1/32            md5
   host    all             all             ::1/128                 md5
$ sudo systemctl start postgresql    # start postgres
$ sudo systemctl enable postgresql   # enable postgres
```
- Create PostgreSQL Roles and Databases
```
$ sudo -i -u postgres   # login as postgres user created in installation

$ createuser --interactive  # create a new role
$ createdb test1  # create a new database. Postgres assume that a matching database will exist for the role to connect to.
# psql -d postgres  # login a different database, the default database is the same as role.

$ psql   # login postgreSQL shell
$ psql -f file.sql        # run a sql file
postgres=# \i basics.sql  # run a sql file
$ psql -U user_name -d database_name -h 127.0.0.1 -W
postgres=#\conninfo   # login in user and database

postgres=# \l or \list;   # list databases
postgres=# \l+;   # list databases with disk usage
postgres=#\c db_name
postgres=#\connect database_name;  #switch database
$psql -h localhost --username=pgadmin --list  # command to list all database

postgres=#\du  # list roles
postgres=# CREATE USER role_name;  # create role with login.
postgres=# CREATE ROLE new_role_name;  # create role or use command:  createuser --interactive
postgres=# CREATE ROLE role_name WITH optional_permissions;  # create role with privileges
postgres=# ALTER ROLE role_name WITH attribute_options;      # change privileges
postgres=# DROP ROLE role_name;
postgres=# GRANT permission_type ON table_name TO role_name;  #grant privileges to role
postgres=# \password test_user;   #give the "test_user" a password

postgres=# CREATE TABLE playground { ... };   # create a new table
CREATE TABLE playground (
    equip_id serial PRIMARY KEY,
    type varchar (50) NOT NULL,
    color varchar (25) NOT NULL,
    location varchar(25) check (location in ('north', 'south', 'west', 'east', 'northeast', 'southeast', 'southwest', 'northwest')),
    install_date date
);
postgres=#\d  # list tables and relationship;
postgres=#\dt  # list all tables in current database;
postgres=#\dt *. will list all tables in all schema

postgres=# INSERT INTO playground (type, color, location, install_date) VALUES ('slide', 'blue', 'south', '2014-04-28');
postgres=# UPDATE playground SET color = 'red' WHERE type = 'swing';
postgres=# SELECT * FROM playground;
postgres=#\q   # exit from postgreSQL shell

```
- Setup database and user in sql file
```
CREATE DATABASE yourdbname;
CREATE USER youruser WITH ENCRYPTED PASSWORD 'yourpass';
GRANT ALL PRIVILEGES ON DATABASE yourdbname TO youruser;
```
- Lists databases:
```
SELECT datname FROM pg_database
WHERE datistemplate = false;
```
- Lists tables in the current database
```
SELECT table_schema,table_name
FROM information_schema.tables
ORDER BY table_schema,table_name;
```

### Commands

### Install Postgres
- Install Postgres server from the CentOS Repositories
```
sudo yum install postgresql-server postgresql-contrib 
sudo postgresql-setup initdb     #initialize database
sudo systemctl start postgresql  #start postggres
sudo systemctl enable postgresql  #start on boot, optional
```

- Install Postgres Client (psql) only:
```
sudo yum install postgresql postgresql-contrib 
```
Both postgresql-server and postgresql depend on postgresql-libs package. 

By default, when PostgreSQL is installed, a postgres user is also added:
```cat /etc/passwd```
The postgres user is shown as:
```postgres:x:26:26:PostgreSQL Server:/var/lib/pgsql:/bin/bash```
The default authentication mode for PostgreSQL is set to ident in the following file:
```cat /var/lib/pgsql/data/pg_hba.conf```
The ident authentication method works by taking the OS username operating as, and comparing it with the allowed database username(s). There is optional username mapping.

This means that in order to connect to PostgreSQL you must be logged in as the correct OS user. If logged into the server as root and try to connect to PostgreSQL:
```psql```
The following error will be shown:
```psql: FATAL: role "root" does not exist```
When become the default PostgreSQL user, postgres:
```su – postgres or sudo su - postgres```
then attempt a connection to PostgreSQL:
```psql```
will get the correct, valid response!
```
psql (9.3.9)
Type "help" for help.

postgres=#
```

Postgres runs with the default port 5432, and data stored in /var/lib/pgsql/data:
```/usr/bin/postgres -D /var/lib/pgsql/data -p 5432```
Local IP:
 ```ipaddr=$(hostname -I)```

#### PostgreSQL Config for TCP/IP:
 - Added the below line in pg_hba.conf to enable password authentication from 10.32.86.*
```host    all             all             10.10.29.0/24          password```
- stop pgsql server :
  ```
  sudo su - postgres
  /bin/pg_ctl stop -D /var/lib/pgsql/data
  ```
- start pgsql server :
  ```
  sudo su - postgres
  /bin/pg_ctl start -D  /var/lib/pgsql/data
  ```
- Restart postgres server
```
# /etc/init.d/postgresql restart
  sudo service postgresql restart
```
- Allow TCP/IP socket:
Open PostgreSQL configuration file /var/lib/pgsql/data/postgresql.conf:
```
# vi /etc/postgresql/8.2/main/postgresql.conf
```
Find configuration line that read as follows:
```
listen_addresses='localhost'
```
Next set IP address(es) to listen on; you can use comma-separated list of addresses; defaults to ‘localhost’, and ‘*’ is all ip address:
```
listen_addresses='*'
```
Or just bind to 202.54.1.2 and 202.54.1.3 IP address
```
listen_addresses='202.54.1.2 202.54.1.3'
```
