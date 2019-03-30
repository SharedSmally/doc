#
#
# https://www.digitalocean.com/community/tutorials/how-to-install-secure-redis-centos-7
#
sudo yum install epel-release -y
sudo yum install redis -y
sudo systemctl start redis.service
sudo systemctl enable redis
sudo systemctl status redis.service
    
 # test
 redis-cli ping
