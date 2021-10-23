
# [Deploy Victoria](https://docs.openstack.org/victoria/install/) 

## minimum depolyment
- Identity service – keystone installation
- Image service – glance installation
- Placement service – placement installation
- Compute service – nova installation
- Networking service – neutron installation
- Dashboard – horizon installation
- Block Storage service – cinder installation 

## [Identity service](https://docs.openstack.org/keystone/victoria/install/index-rdo.html) – keystone 
For authentication, authorization, and a catalog of services
1. Create a keystone database
```
$ mysql -u root -p
>  CREATE DATABASE keystone;
> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'localhost' IDENTIFIED BY 'KEYSTONE_DBPASS';
> GRANT ALL PRIVILEGES ON keystone.* TO 'keystone'@'%' IDENTIFIED BY 'KEYSTONE_DBPASS';
```
2. Install the servicec
```
# yum install openstack-keystone httpd python3-mod_wsgi
```
3. Edit /etc/keystone/keystone.conf:
```
[database]
# ...
connection = mysql+pymysql://keystone:KEYSTONE_DBPASS@controller/keystone

[token]
# ...
provider = fernet
```
4. Populate the Identity service database:
```
sudo /bin/sh -c "keystone-manage db_sync" keystone
```
5. Initialize Fernet key repositories:
```
# keystone-manage fernet_setup --keystone-user keystone --keystone-group keystone
# keystone-manage credential_setup --keystone-user keystone --keystone-group keystone
```
6. Boostrap the service
```
# keystone-manage bootstrap --bootstrap-password ADMIN_PASS \
  --bootstrap-admin-url http://controller:5000/v3/ \
  --bootstrap-internal-url http://controller:5000/v3/ \
  --bootstrap-public-url http://controller:5000/v3/ \
  --bootstrap-region-id RegionOne
```
7. Configure the Apache HTTP server
```
# vi /etc/httpd/conf/httpd.conf 

ServerName controller

# ln -s /usr/share/keystone/wsgi-keystone.conf /etc/httpd/conf.d/

# systemctl enable httpd.service
# systemctl start httpd.service
```
8. Disable SELinux if httpd fails
- Disable SELinux temporarily
```
sudo setenforce 0
```
- Restart httpd service
```
service httpd restart
```
- Disable SELinux persistently (after reboot)
```
vi /etc/selinux/config
```
- Add line and save
```
SELINUX=disabled
```
8. Set the proper environmental variables from keystone-manage bootstrap.
```
$ export OS_USERNAME=admin
$ export OS_PASSWORD=ADMIN_PASS
$ export OS_PROJECT_NAME=admin
$ export OS_USER_DOMAIN_NAME=Default
$ export OS_PROJECT_DOMAIN_NAME=Default
$ export OS_AUTH_URL=http://controller:5000/v3
$ export OS_IDENTITY_API_VERSION=3
```
10. Create a domain, projects, users, and roles
```
$ openstack domain create --description "An Example Domain" example
$ openstack project create --domain default \
  --description "Service Project" service
$  openstack project create --domain default \
  --description "Demo Project" myproject
$ openstack user create --domain default \
  --password-prompt myuser
$ openstack role create myrole
$ openstack role add --project myproject --user myuser myrole
```
11. [Verify operation](https://docs.openstack.org/keystone/victoria/install/keystone-verify-rdo.html)

## [Image service](https://docs.openstack.org/glance/victoria/install/install-rdo.html) – glance 

## [Placement service](https://docs.openstack.org/placement/victoria/install/) – placement 
Provides a placement-api WSGI script for running the service with Apache, nginx or other WSGI-capable web servers

## [Compute service](https://docs.openstack.org/nova/victoria/install/) – nova 

## [Networking service](https://docs.openstack.org/neutron/victoria/install/) – neutron 

## [Dashboard Service](https://docs.openstack.org/horizon/victoria/install/) – horizon 

## [Block Storage service](https://docs.openstack.org/cinder/victoria/install/) – cinder 


