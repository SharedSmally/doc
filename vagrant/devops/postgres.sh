#!/bin/bash -e

# https://www.linode.com/docs/databases/postgresql/how-to-install-postgresql-relational-databases-on-centos-7/
#install postgres
# install from the CentOS repositories
sudo yum install -y postgresql-server postgresql-contrib

#Initialize Postgres database and start PostgreSQL:
sudo postgresql-setup initdb
sudo systemctl start postgresql

#Optional: Configure PostgreSQL to start on boot:
sudo systemctl enable postgresql

#Access the PostgreSQL Shell as the postgres Linux user
# login postgres
sudo su - postgres
# access postgresql shell
-bash$ psql postgres
-bash$ psql -U postgres
postgres=#\d
postgres=#\q
-bash$ psql -U postgres -f postgres.sql
```
create database wchendb;
create user wchen with password 'password';
grant all privileges on database wchendb to wchen;
```
# update configuration in /var/lib/pgsql/data:
-bash$ vi data/pg_hba.conf
Add the following lines:
host    all             all             192.168.250.1/24        password
host    all             all             127.0.0.1/32            password

-bash$ vi data/postgresql.conf
Add the following line for the IP address to listen on
listen_addresses = '192.168.250.10'             # 127.0.0.1 is disabled
listen_addresses = '127.0.0.1,192.168.250.10'   # enable both 127.0.0.1 and 192.168.250.10

-bash$ exit

$ sudo systemctl restart postgresql
#psql -h 127.0.0.1 -W wchendb wchen
#outside vm
$ psql -h 192.168.250.10 -W wchendb wchen

#################################################
# Configure PostgreSQLPermalink
# Secure the Postgres UsersPermalink
# By default, PostgreSQL will create a Linux user named
#   postgres to access the database software.
# Change the postgres user’s Linux password:

#sudo passwd postgres

# set a password for the postgres database user.
# replace newpassword with a strong password
#su - postgres
#psql -d template1 -c "ALTER USER postgres WITH PASSWORD 'newpassword';"

# Add the following line to  pg_hba.conf
#host    all             all             10.2.32.0/24          password
