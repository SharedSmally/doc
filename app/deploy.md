# Applicaion Deployment

Deployment: Cloud + Ansible + Kubernates

K8s Cluster:
   - master: 1..n
   - worker: 2..m
   - network: calico
   - helm:
   - pvc: 

Basic Applications  
   - haproxy
   - 


Database:   
   - postgres:
   - liquibase:

Kafka/Zookeeper : bitnami   
   - kafka
   - zookeeper
   one set for generic purpse; kafka-0/1/2: $zookeeper-0/1/2; 
   multiple for needed app: $proj-kafka-0/1/2: $proj-zookeeper-0/1/2  
   
Redis:   bitnami
   - redis: multi-sets, $app-redis-0/1/2

Logging: EFK
   - Elasticsearch (E): a real-time, distributed, and scalable search engine which allows for full-text and structured search, as well as analytics.
   - FluentD (F): collect, transform, and ship log data to the Elasticsearch backend
   - Kibana (K): a powerful data visualization frontend and dashboard for Elasticsearch
   - prometheus: visualization frontend
