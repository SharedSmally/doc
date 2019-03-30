
#https://drmanalo.github.io/blog/2017/installing-nexus-centos7.html
#
# Download and extract nexus
wget http://download.sonatype.com/nexus/3/latest-unix.tar.gz
sudo tar xvf latest-unix.tar.gz -C /opt
sudo ln -s /opt/nexus-3.15.2-01/ /opt/nexus

# Setup nexus user
sudo adduser nexus
sudo chown -R nexus:nexus /opt/nexus

#Running as nexus user
#sudo vim /opt/nexus/bin/nexus.rc
#run_as_user="nexus"   
#:wq

# Running nexus as Linux service
sudo ln -s /opt/nexus/bin/nexus /etc/init.d/nexus
sudo systemctl enable nexus
# nexus.service is not a native service, redirecting to /sbin/chkconfig.
# Executing /sbin/chkconfig nexus on

#Starting nexus
sudo systemctl start nexus

# To check, point your browser to http://localhost:8081. 
# Default username is admin with password admin123.
# Running behind reverse proxy

# vim /opt/sonatype-work/nexus3/etc/nexus.properties
#nexus-context-path=/nexus
#:wq

#Add nexus.conf to existing /etc/httpd/conf.d. Here's what the file should contain.
#ProxyRequests Off
#ProxyPreserveHost On
#
#<VirtualHost 127.0.0.1:80>
#    ServerName centos.dev
#    ServerAdmin admin@centos.dev
#    ProxyPass /nexus http://localhost:8081/nexus
#    ProxyPassReverse /nexus http://localhost:8081/nexus
#    ErrorLog /var/log/nexus/error.log
#    CustomLog /var/log/nexus/access.log common
#</VirtualHost>
#
#Make the log folder as define on ErrorLog and CustomLog directives then test the configuration.
#sudo mkdir /var/log/nexus
#apachectl configtest
#Syntax OK
#sudo systemctl httpd restart





