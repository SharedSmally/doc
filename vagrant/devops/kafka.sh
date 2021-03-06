
#https://www.digitalocean.com/community/tutorials/how-to-install-apache-kafka-on-centos-7: full-complicated
#https://www.vultr.com/docs/how-to-install-apache-kafka-on-centos-7: simple

sudo yum update -y && sudo reboot
sudo yum install java-1.8.0-openjdk.x86_64
sudo vi /etc/profile
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk
export JRE_HOME=/usr/lib/jvm/jre
source /etc/profile

# download kafka
cd ~
wget http://www-us.apache.org/dist/kafka/2.2.0/kafka_2.12-2.2.0.tgz

sudp tar -xvf kafka_2.12-2.2.0.tgz -C /opt
sudo ln -s /opt/kafka_2.12-2.2.0/ /opt/kafka

# create kafka user
sudo adduser kafka
sudo chown -R kafka:kafka /opt/kafka

#sudo useradd kafka -m
#sudo passwd kafka
#sudo usermod -aG wheel kafka

# run zookeeper as a service
sudo vi /etc/systemd/system/zookeeper.service
```
[Unit]
Requires=network.target remote-fs.target
After=network.target remote-fs.target

[Service]
Type=simple
User=kafka
ExecStart=/opt/kafka/bin/zookeeper-server-start.sh /opt/kafka/config/zookeeper.properties
ExecStop=/opt/kafka/bin/zookeeper-server-stop.sh
Restart=on-abnormal

[Install]
WantedBy=multi-user.target
```
#
sudo vi /etc/systemd/system/kafka.service
```
[Unit]
Requires=zookeeper.service
After=zookeeper.service

[Service]
Type=simple
User=kafka
ExecStart=/bin/sh -c '/opt/kafka/bin/kafka-server-start.sh /opt/kafka/config/server.properties > /tmp/kafka.log 2>&1'
ExecStop=/opt/kafka/bin/kafka-server-stop.sh
Restart=on-abnormal

[Install]
WantedBy=multi-user.target
```
# Modify the configuration of your Kafka server
sudo vi /opt/kafka/bin/kafka-server-start.sh
  export KAFKA_HEAP_OPTS="-Xmx256M -Xms128M"
  
# start kafka service
sudo systemctl start kafka
# check kafka status
sudo journalctl -u kafka
# enable kafka service
sudo systemctl enable kafka

#test kafka
# /opt/kafka/bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic TutorialTopic
# echo "Hello, World" | /opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9092 --topic TutorialTopic > /dev/null
# /opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic TutorialTopic --from-beginning


#######################################
# Get into the Kafka directory
cd /opt/kafka

# Start the Zookeeper server
bin/zookeeper-server-start.sh -daemon config/zookeeper.properties



#Start the Kafka server
bin/kafka-server-start.sh config/server.properties

# create test topic
cd /opt/kafka_2.12-2.2.0
bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
bin/kafka-topics.sh --list --zookeeper localhost:2181

# Produce messages using the topic "test"
cd /opt/kafka_2.12-2.2.0
bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test

# Display messages
cd /opt/kafka_2.12-2.2.0
bin/kafka-console-consumer.sh --zookeeper localhost:2181 --topic test --from-beginning







