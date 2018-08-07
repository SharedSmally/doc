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
