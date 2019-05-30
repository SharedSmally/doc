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

 ### Consumer Group Experience
In Apache Kafka, the consumer group concept is a way of achieving two things:
- Having consumers as part of the same consumer group means providing the“competing consumers” pattern with whom the messages from topic partitions are spread across the members of the group. Each consumer receives messages from one or more partitions (“automatically” assigned to it) and the same messages won’t be received by the other consumers (assigned to different partitions). In this way, we can scale the number of the consumers up to the number of the partitions (having one consumer reading only one partition); in this case, a new consumer joining the group will be in an idle state without being assigned to any partition.
- Having consumers as part of different consumer groups means providing the “publish/subscribe” pattern where the messages from topic partitions are sent to all the consumers across the different groups. It means that inside the same consumer group, we’ll have the rules explained above, but across different groups, the consumers will receive the same messages. It’s useful when the messages inside a topic are of interest for different applications that will process them in different ways. We want all the interested applications to receive all the same messages from the topic.

Another great advantage of consumers grouping is the rebalancing feature. When a consumer joins a group, if there are still enough partitions available (i.e. we haven’t reached the limit of one consumer per partition), a re-balancing starts and the partitions will be reassigned to the current consumers, plus the new one. In the same way, if a consumer leaves a group, the partitions will be reassigned to the remaining consumers.

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
