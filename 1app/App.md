# Application Deployment

## Kubernetes Cluster
- Master Node (1)
- Worker Node (2)

## HA Platform
- keepalived: master/backup
- haproxy

## Application Platform
- Postgresql for database
- Redis for Cache
- Kafka for Trace/Record (multiple instance)
- ActiveMQ Armtis/RabbitQ for JMS
- Monitor System
- Logging: EFK(Elasticsearch/search, FluentD/Collect and Kibana/Visualization) 
https://www.digitalocean.com/community/tutorials/how-to-set-up-an-elasticsearch-fluentd-and-kibana-efk-logging-stack-on-kubernetes
(namespace kube-logging/)

## Application
