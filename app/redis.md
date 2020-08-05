# [REDIS](https://redis.io/)
Roles
- Masters: M1, M2, M3, ..., Mn.
- Slaves: SL1,SL2,...,SLn
- Replicas: R1, R2, R3, ..., Rn.
- Sentinels: S1, S2, S3, ..., Sn.
- Clients: C1, C2, C3, ..., Cn.

## Documents
- [Commands](https://redis.io/commands)
- [Clients](https://redis.io/clients)
- [Documents](https://redis.io/documentation)

## [Cluster](https://redis.io/topics/cluster-tutorial)
Run a Redis installation where data is automatically sharded across multiple Redis nodes.
- Redis Cluster data sharding
- Redis Cluster master-slave model
- Redis Cluster TCP ports

Every Redis Cluster node requires two TCP connections open. The normal Redis TCP port used to serve clients, for example 6379, plus the port obtained by adding 10000 to the data port, so 16379 in the example.

This second high port is used for the Cluster bus, that is a node-to-node communication channel using a binary protocol. The Cluster bus is used by nodes for failure detection, configuration update, failover authorization and so forth. Clients should never try to communicate with the cluster bus port, but always with the normal Redis command port, however ma

## [Sentinel](https://redis.io/topics/sentinel)
- SENTINEL masters:  Show a list of monitored masters and their state.
- SENTINEL master <master name>: Show the state and info of the specified master.
- SENTINEL replicas <master name>: Show a list of replicas for this master, and their state.
- SENTINEL sentinels <master name>: Show a list of sentinel instances for this master, and their state.


