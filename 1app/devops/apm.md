# APM - Application Performance Monitoring
- EFK: ElasticSearch(JSON Search Engine)-FluentD(Collect,transform, and ship log data to Elasticsearch)-Kibana(Visualization) for log data
- Prometheus (Metrics collector with storage) - Grafana (Visualization): for metrics with time-series data
- [EFK Setup](https://www.digitalocean.com/community/tutorials/how-to-set-up-an-elasticsearch-fluentd-and-kibana-efk-logging-stack-on-kubernetes)

## [EFK](https://www.elastic.co/guide/index.html#viewall)
- Elasticsearch: Store, Search, and Analyze
- Kibana: Explore, Visualize, and Share
- Logstash: Collect, Enrich, and Transport
- Fleet: Install and Manage Elastic Agents
- Beats: Collect, Parse, and Ship (lightweight Logstash)
- APM Server


### [Beats](https://www.elastic.co/guide/en/beats/libbeat/current/beats-reference.html)
Beats can send data directly to Elasticsearch or via Logstash, where you can further process and enhance the data, before visualizing it in Kibana.
![Beats](https://www.elastic.co/guide/en/beats/libbeat/current/images/beats-platform.png)
- Audit data: Auditbeat
- Log files and journals: Filebeat
- Cloud data: Functionbeat
- Availability: Heartbeat
- Metrics: Metricbeat
- Network traffic: Packetbeat
- Windows event logs: Winlogbeat
- [Community Beats](https://www.elastic.co/guide/en/beats/libbeat/current/community-beats.html)

### [MetricBeat](https://www.elastic.co/guide/en/beats/metricbeat/current/index.html)
Metricbeat is a lightweight shipper that installed on the servers to periodically collect metrics from the operating system and from services running on the server. Metricbeat takes the metrics and statistics that it collects and ships them to the specified output, such as Elasticsearch or Logstash.
- [MetricBeat Modules](https://www.elastic.co/guide/en/beats/metricbeat/current/metricbeat-modules.html): including database, Prometheus, Linux,...

## [Prometheus](https://prometheus.io/)

### [docker image](https://hub.docker.com/u/prom)
- prometheus: prom/prometheus
- alertmanager:
- graphite
- blackbox_exporter
- haproxy_exporter
- mysqld_exporter
- node-exporter
- statsd_exporter


## [Grafana](https://grafana.com/oss/)
- Grafana Loki: Multi-tenant log aggregation system
- Grafana: Query, visualize, and alert on data
- Grafana Tempo: High-scale distributed tracing backend
- Grafana Mimir: Scalable and performant metrics backend
- Grafana OnCall: On-call management
- Grafana Phlare: Scalable continuous profiling backend
- Grafana Faro: Frontend application observability web SDK
- Grafana k6: Load testing for engineering teams
- Prometheus:  Monitor Kubernetes and cloud native
- OpenTelemetry: Instrument and collect telemetry data
- Graphite: Scalable monitoring for time series data
