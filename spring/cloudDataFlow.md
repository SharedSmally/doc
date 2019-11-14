# Spring Cloud Data Flow
The Spring Cloud Data Flow server uses Spring Cloud Deployer, to deploy data pipelines made of Spring Cloud Stream or Spring Cloud Task applications onto modern platforms such as Cloud Foundry and Kubernetes.
- [Project](https://spring.io/projects/spring-cloud-dataflow)
- [Spring Cloud Data Flow Microsite](https://dataflow.spring.io/getting-started/)
- [Reference](https://docs.spring.io/spring-cloud-dataflow/docs/current/reference/htmlsingle/)
- [API Doc](https://docs.spring.io/spring-cloud-dataflow/docs/current/api/)

## [Components](https://dataflow.spring.io/docs/concepts/architecture/)
- Data Flow Server: Launch short-lived applications
- [Skipper Server] (https://spring.io/projects/spring-cloud-skipper): Launch long-lived applications; discover Spring Boot applications and manage their lifecycle on multiple Cloud Platforms.
- Shell: 
- Dashboard

## Deploy Platforms
- [Local Machine](https://dataflow.spring.io/docs/installation/local/): Based on docker-compose
    - install docker
    ```
    sudo yum install java-1.8.0-openjdk
    sudo yum install wget
    sudo yum install docker
    sudo systemctl enable docker
    sudo systemctl start docker
    sudo systemctl status docker
    sudo docker info
    ```
    - install docker-compose: See the [latest release](https://github.com/docker/compose/releases)
    ```
    sudo curl -L https://github.com/docker/compose/releases/download/1.25.0-rc4/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
    sudo chmod +x /usr/local/bin/docker-compose
    ```
    - Downloading the Docker Compose File
    ```
    wget https://raw.githubusercontent.com/spring-cloud/spring-cloud-dataflow/v2.2.1.RELEASE/spring-cloud-dataflow-server/docker-compose.yml    
    ```
    - Start Docker Compose
```
sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
sudo DATAFLOW_VERSION=2.2.1.RELEASE SKIPPER_VERSION=2.1.2.RELEASE docker-compose up
```

   The Docker Compose file starts instances of the following products:
        - Spring Cloud Data Flow Server
        - Spring Cloud Skipper Server
        - MySQL
        - Apache Kafka
        - Prometheus
        - Grafana

    - Stop Docker Compose
```
sudo DATAFLOW_VERSION=2.2.1.RELEASE SKIPPER_VERSION=2.1.2.RELEASE docker-compose down
```
    - Cloud Data Flow Shell: included in springcloud/spring-cloud-dataflow-server 
```
wget https://repo.spring.io/release/org/springframework/cloud/spring-cloud-dataflow-shell/2.2.1.RELEASE/spring-cloud-dataflow-shell-2.2.1.RELEASE.jar
docker exec -it dataflow-server java -jar shell.jar
```
- [Cloud Foundry](https://dataflow.spring.io/docs/installation/cloudfoundry/): 
- [Kubernetes](https://dataflow.spring.io/docs/installation/kubernetes/)

## Applications/DSL
- Long-lived Applications: stream with sources, process, and sink
    - [Stream Developer Guides](https://dataflow.spring.io/docs/stream-developer-guides/)
    - [Spring Cloud Stream](https://spring.io/projects/spring-cloud-stream)
    - [Spring Cloud Stream Reference](https://cloud.spring.io/spring-cloud-static/spring-cloud-stream/2.2.1.RELEASE/home.html)
    - [Spring Cloud Stream App Starters](https://cloud.spring.io/spring-cloud-stream-app-starters/):  Spring Boot based Spring Integration applications that provide integration with external systems    
- Short-lived Applications: task with batch
    - [Batch Developer Guides](https://dataflow.spring.io/docs/batch-developer-guides/)
    - [Spring Cloud Task](https://spring.io/projects/spring-cloud-task)
    - [Spring Cloud Task Reference](https://docs.spring.io/spring-cloud-task/docs/2.1.3.RELEASE/reference/htmlsingle/)
    - [Spring Cloud Task App Starters](https://cloud.spring.io/spring-cloud-task-app-starters/): standalone executable applications that can be used for on-demand use-cases such as database migration, machine learning, and scheduled operations.
    
