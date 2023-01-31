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

### MetricBeat:


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
