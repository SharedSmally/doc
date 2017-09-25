## [Kafka](https://kafka.apache.org)
### Concepts:
- Producer
- Consumer
- Stream
- Connector

### Partition/Replicate
- A topic is a category or feed name to which records are published. Topics in Kafka are always multi-subscriber; that is, a topic can have zero, one, or many consumers that subscribe to the data written to it.

- Topics are partitioned across multiple nodes so a topic can grow beyond the limits of a node. Partitions are replicated for fault tolerance. Replication and leader takeover is one of the biggest difference between Kafka and other brokers/Flume. From the Apache Kafka site:

- Each partition has one server which acts as the "leader" and zero or more servers which act as "followers". The leader handles all read and write requests for the partition while the followers passively replicate the leader. If the leader fails, one of the followers will automatically become the new leader. Each server acts as a leader for some of its partitions and a follower for others so load is well balanced within the cluster.

### Group
Consumers label themselves with a consumer group name, and each record published to a topic is delivered to one consumer instance within each subscribing consumer group. Consumer instances can be in separate processes or on separate machines.
- If all the consumer instances have the same consumer group, then the records will effectively be load balanced over the consumer instances.
- If all the consumer instances have different consumer groups, then each record will be broadcast to all the consumer processes.
