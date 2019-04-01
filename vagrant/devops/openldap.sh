#
# install openldap on centos/7
# https://linuxhostsupport.com/blog/how-to-install-ldap-on-centos-7/
# install
sudo yum -y install openldap compat-openldap openldap-clients openldap-servers openldap-servers-sql openldap-devel
sudo systemctl start slapd.service
sudo systemctl enable slapd.service

#Run the slappasswd command to set a LDAP root password and save the output to configure OpenLDAP:
slappasswd

# config
#
# https://www.tecmint.com/install-openldap-server-for-centralized-authentication/
