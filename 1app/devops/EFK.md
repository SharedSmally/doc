# EFK Stack
- ElasticSearch: Search Engine
- FluentD: Logging Collector
- Kibana: Visualization

## Logging Collector
- FluentD: Memory Efficient; Good for docker logging
- LogStash: Use filebeat to push logging to LogStash; Good with ES and Kibana.

## Visualization
- Kibana: With ElasticSearch as DataSource
- Grafana: Mostly used by InfluxDB, Graphite, and Elasticsearch. Good for time series analytics
Commeicial Software
- Splunk
- Knowi: connects to Elasticsearch and other NoSQL, SQL, and REST-API data sources
