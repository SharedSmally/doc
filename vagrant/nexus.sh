#
# Install nexus in centos
# http://www.sonatype.org/nexus/2017/01/25/how-to-install-latest-sonatype-nexus-3-on-linux/
#
NAME=nexus
VERSION=3.7.1-02
PACKAGE=latest-unix.tar.gz

if [ ! -f ${PACKAGE} ]; then
   wget https://download.sonatype.com/nexus/3/latest-unix.tar.gz -O ${PACKAGE}
fi

tar -xvf ${PACKAGE}
mv nexus-${VERSION} nexus
echo "run_as_user=\"vagrant\"" >  nexus-${VERSION}/bin/nexus.rc

sudo rm -rf /etc/profile.d/${NAME}.sh
sudo printf "export NEXUS_HOME=/home/vagrant/nexus-${VERSION}\nexport PATH=\$PATH:\$NEXUS_HOME/bin" > /etc/profile.d/${NAME}.sh

sudo chown -R vagrant:vagrant nexus/
sudo chown -R vagrant:vagrant sonatype-work/

#  Create a symbolic link for nexus service script to /etc/init.d folder.
sudo rm -rf /etc/init.d/nexus
sudo ln -s /home/vagrant/nexus-${VERSION}/bin/nexus /etc/init.d/nexus

# Execute the following commands to add nexus service to boot.
sudo chkconfig --add nexus
sudo chkconfig --levels 345 nexus on

# start nexus
sudo service nexus start
