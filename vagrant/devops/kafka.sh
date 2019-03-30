
#https://www.digitalocean.com/community/tutorials/how-to-install-apache-kafka-on-centos-7: full-complicated
#https://www.vultr.com/docs/how-to-install-apache-kafka-on-centos-7: simple

sudo yum update -y && sudo reboot
sudo yum install java-1.8.0-openjdk.x86_64
sudo vi /etc/profile
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk
export JRE_HOME=/usr/lib/jvm/jre
source /etc/profile

cd ~
http://www-us.apache.org/dist/kafka/2.2.0/kafka_2.12-2.2.0.tgz

tar -xvf kafka_2.12-2.2.0.tgz
sudo mv kafka_2.12-2.2.0 /opt

# Get into the Kafka directory
cd /opt/kafka_2.12-2.2.0

# Start the Zookeeper server
bin/zookeeper-server-start.sh -daemon config/zookeeper.properties

# Modify the configuration of your Kafka server
vi bin/kafka-server-start.sh
  export KAFKA_HEAP_OPTS="-Xmx256M -Xms128M"

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







