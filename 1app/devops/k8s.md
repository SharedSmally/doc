# K8S
- etcd: Shared data
- Control Plane Node
- Working Nodes

## Deployment
- Postgresql: Zolando; 1 service (3 pods)
- Redis: Bitnami (Each group: app/dashboard/trace/sys has one: 3 pods: master/; )
- Kafka/ZooKeeper (3 pods)
    - 2 Set of Kafka/ZooKeeper: One for Application; and one for Tracing
