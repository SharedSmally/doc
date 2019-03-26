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
