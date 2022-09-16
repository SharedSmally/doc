# Application Deployment

## Kubernetes Cluster
- Master Node (1)
- Worker Node (2)

## HA Platform
- keepalived: master/backup
- haproxy: http://www.haproxy.org/

Global parameters

Proxy configuration can be located in a set of sections :
- defaults [<name>] [ from <defaults_name> ]
- frontend <name>   [ from <defaults_name> ]
- backend  <name>   [ from <defaults_name> ]
- listen   <name>   [ from <defaults_name> ]
  
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
