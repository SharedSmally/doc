# Logging: ELK Stack
![BELK Stack](https://www.elastic.co/guide/en/beats/libbeat/current/images/beats-platform.png)
- [Beats](https://www.elastic.co/guide/en/beats/libbeat/current/index.html): Lightweight data Collector
- [Logstash](https://www.elastic.co/logstash/) or FluentD: parse and processing with plugin Inputs, Filters and Outputs.
- [ElasticSearch](https://www.elastic.co/start): NoSQL database storage
- [Kibana](https://www.elastic.co/guide/en/kibana/current/index.html) or Grafana(mainly for metrics) : for visualization

# Install Kibana 
## [Install in docker](https://www.elastic.co/guide/en/kibana/current/docker.html)
- To start an Elasticsearch container for development or testing, run:
```
docker network create elastic
docker pull docker.elastic.co/elasticsearch/elasticsearch:7.15.1
docker run --name es01-test --net elastic -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" docker.elastic.co/elasticsearch/elasticsearch:7.15.1
```
- To start Kibana and connect it to your Elasticsearch container, run the following commands in a new terminal session:
```
docker pull docker.elastic.co/kibana/kibana:7.15.1
docker run --name kib01-test --net elastic -p 5601:5601 -e "ELASTICSEARCH_HOSTS=http://es01-test:9200" docker.elastic.co/kibana/kibana:7.15.1
```
- To access Kibana, go to http://localhost:5601.

- To stop your containers, run:
```
docker stop es01-test
docker stop kib01-test
```
- To remove the containers and their network, run:
```
docker network rm elastic
docker rm es01-test
docker rm kib01-test
```
## [Install in k8s](https://www.elastic.co/downloads/elastic-cloud-kubernetes)
- Install ECK:
```
kubectl create -f https://download.elastic.co/downloads/eck/1.8.0/crds.yaml
kubectl apply -f https://download.elastic.co/downloads/eck/1.8.0/operator.yaml
```
- Monitor the operator logs:
```
kubectl -n elastic-system logs -f statefulset.apps/elastic-operator
```
- [Quick Start](https://www.elastic.co/guide/en/cloud-on-k8s/current/k8s-quickstart.html)


## Data Collector
Elastic provides two main ways to send data to Elasticsearch:
- **Beats**: lightweight data shippers that send operational data to Elasticsearch. Elastic provides separate Beats for different types of data, such as logs, metrics, and uptime.
- **Elastic Agent**: a single agent for logs, metrics, security data, and threat prevention. The Elastic Agent can be deployed in two different modes:
    - **Managed by Fleet** — easily deploy services with the Fleet UI. Once installed, the Elastic Agent lifecycle and policy/configuration is managed from a central point.
    - **Standalone mode** — once installed, all configuration is applied to the Elastic Agent manually. 

### Setup auditbeat
```
$ curl -L -O https://artifacts.elastic.co/downloads/beats/auditbeat/auditbeat-7.15.1-linux-x86_64.tar.gz
$ vi itbeat.yaml
$ sudo ./auditbeat setup
$ sudo chown 0:0 autitbeat.yaml
$ sudo ./auditbeat run
```
### [Develop Beat](https://www.elastic.co/guide/en/beats/devguide/current/newbeat-overview.html)
Using GO language

![Beat](https://www.elastic.co/guide/en/beats/devguide/current/images/beat_overview.png)

At the high level, a simple Beat has two main components:
- a component that collects the actual data, and
- a publisher(libbeat) that sends the data to the specified output, such as Elasticsearch or Logstash.

[Interface implementation Guide](https://www.elastic.co/guide/en/beats/devguide/current/beater-interface.html)
