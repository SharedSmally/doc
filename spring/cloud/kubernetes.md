# [Spring Cloud Kubernetes](https://spring.io/projects/spring-cloud-kubernetes)
- [Reference](https://spring.io/projects/spring-cloud-kubernetes#learn)
- [K8s Deploy](https://docs.spring.io/spring-boot/docs/current/reference/htmlsingle/#cloud-deployment-kubernetes)
- [workshop](https://hackmd.io/@ryanjbaxter/spring-on-k8s-workshop)

## Starters
- kubernetes: Discovery Client implementation that resolves service names to Kubernetes Services.

In application class:
```
@SpringBootApplication
@EnableDiscoveryClient
public class Application {
  public static void main(String[] args) {
    SpringApplication.run(Application.class, args);
  }
}
```
In client classes:
```
@Autowired
private DiscoveryClient discoveryClient;
```
In application.properties for configuration:
```
spring.cloud.kubernetes.discovery.all-namespaces=true
spring.cloud.kubernetes.discovery.enabled=false   # disable the DiscoveryClien
```

spring.application.name has no effect as far as the name registered for the application within Kubernet


- kubernetes-config: Load application properties from Kubernetes ConfigMaps and Secrets. Reload application properties when a ConfigMap or Secret changes
Kubernetes itself is capable of (server side) service discovery. The caller service then need only refer to names resolvable 
in a particular Kubernetes cluster. A simple implementation might use a spring RestTemplate that refers to a fully qualified
domain name (FQDN), such as {service-name}.{namespace}.svc.{cluster}.local:{service-port}


Also can use Hystrix for:
    - Circuit breaker implementation on the caller side, by annotating the spring boot application class with @EnableCircuitBreaker
    - Fallback functionality, by annotating the respective method with @HystrixCommand(fallbackMethod=
    
## Kubernetes PropertySource implementations
Kubernetes provides a resource named ConfigMap to externalize the parameters to pass to your application in the form of key-value pairs 
or embedded application.properties or application.yaml files. 

## 

## Deploy
- Building A Container
```
./mvnw spring-boot:build-image
docker images  # list built container 
```
- Run the container
```
$ docker run --name k8s-demo-app -p 8080:8080 k8s-demo-app:0.0.1-SNAPSHOT
```
- Putting The Container In A Registry
```
$ ./mvnw spring-boot:build-image -Dspring-boot.build-image.imageName=localhost:5000/apps/demo
$ docker push localhost:5000/apps/demo
```
- Create Deployment Descriptor
```
$ mkdir k8s
$ kubectl create deployment k8s-demo-app --image localhost:5000/apps/demo -o yaml --dry-run=client > k8s/deployment.yaml
```
- Create Service Descriptor
```
$ kubectl create service clusterip k8s-demo-app --tcp 80:8080 -o yaml --dry-run=client > k8s/service.yaml
```
- Tools to deploy: Skaffold + Kustomize
    - Skaffold: facilitates continuous development for Kubernetes applications
    - Kustomize: ustomize deployments to different environments
