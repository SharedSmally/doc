## [Kafka](https://kafka.apache.org)
### Concepts:
- Producer
- Consumer
- Stream
- Connector

### Topic Partition/Replicate
A topic is a category or feed name to which records are published. Topics in Kafka are always multi-subscriber; that is, a topic can have zero, one, or many consumers that subscribe to the data written to it.

- Topics are partitioned across multiple nodes so a topic can grow beyond the limits of a node. Partitions are replicated for fault tolerance. Replication and leader takeover is one of the biggest difference between Kafka and other brokers/Flume. 

- Each partition has one server which acts as the "leader" and zero or more servers which act as "followers". The leader handles all read and write requests for the partition while the followers passively replicate the leader. If the leader fails, one of the followers will automatically become the new leader. Each server acts as a leader for some of its partitions and a follower for others so load is well balanced within the cluster.

### Consumer Group
Consumers label themselves with a consumer group name, and each record published to a topic is delivered to **one consumer instance** within each subscribing consumer group. Consumer instances can be in separate processes or on separate machines.
- If all the consumer instances have the same consumer group, then the records will effectively be load balanced over the consumer instances.
- If all the consumer instances have different consumer groups, then each record will be broadcast to all the consumer processes.

### Topics
Each topic is partitioned into several partitions, and one of the service is the leader of the partition, and the rest kafka services are the followers. The message is sent to the leader service, while the followers get the replicated messages from the leader. When the leader service is down, the followers will select a new leader, that may needs about several seconds. During that selection periodid, the message sending to the first follower will throw Exception: This server is not the leader for that topic-partition. Adding the config may solve the issue:
```
 props.put(ProducerConfig.RETRIES_CONFIG, 10);  //increase to 10 from default of 0
  props.put(ConsumerConfig.MAX_POLL_INTERVAL_MS_CONFIG,   
    Integer.toString(Integer.MAX_VALUE)); // increase to infinity from default of 300 s
```
### Commands:  /opt/kafka/bin:
- zookeeper: /etc/zookeeper/zoo.cfg:/var/log/zookeeper:    kafka1.local:2181,kafka2.local:2181,kafka3.local:2181
- kafka:  etc/kafka/\*.properties:/var/log/kafka/kafkaServer-gc.log:  kafka1.local:9092,kafka2.local:9092,kafka3.local:9092
- kafka-topics.sh --zookeeper ${zk_urls}  --list | --describe | --describe --topic LDR 

- kafka-consumer-groups.sh --bootstrap-server ${kafkas}--list     : List consumer groups
- kafka-consumer-groups.sh --bootstrap-server ${kafkas} --describe --group ${group} # desc of group
