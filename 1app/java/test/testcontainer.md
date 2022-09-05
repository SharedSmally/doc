# testcontainer
- [site](https://www.testcontainers.org)
- [javadoc API](https://javadoc.io/doc/org.testcontainers/testcontainers/latest/index.html)
    - GenericContainer
    - DockerImageName
    - Network
    - DockerClient
    - Images.builder
- [testcontainers modules](https://javadoc.io/doc/org.testcontainers)
    - junit-jupiter: org.testcontainers.junit.jupiter@Container/@Testcontainers(autatic start/stop containers)
    - postgresql: withDatabaseName/Username/Password
    - cassandra
    - jdbc/db2/mssqlserver/mysql/mariadb/oracle-xe
    - elasticsearch    
    - kafka: withEmbeddedZookeeper()/withExternalZookeeper(java.lang.String connectString) 
    - localstack:  A fully functional local AWS cloud stack with S3, ..., service
    - mockserver: MockServerContainer(getEndpoint()/getServerPort())
    - mongodb
    - neo4j
    - nginx: NginxContainer<SELF extends NginxContainer<SELF>>  (getBaseUrl: set/withCustomContent) 
    - rabbitmq
    - selenium
    - spock
    - testcontainers
    - toxiproxy

## org.testcontainers.containers.GenericContainer<>
- GenericContainer(@NonNull RemoteDockerImage image) 
- GenericContainer(@NonNull DockerImageName dockerImageName) 
- GenericContainer(@NonNull java.lang.String dockerImageName) 
- get/set/withCommand/execInContainer/Env/Labels/LogConsumer/CopyFile/Volume/TmpFS/WorkingDirectory/
- get/set/withNetwork(--network <name>)/NetworkAlias(--network-alias <my-service>)/NetworkMode(--net <name>)
- start/stop/waiingFor

## org.testcontainers.utility.MountableFile
- static MountableFile 	forClasspathResource(String resourceName, int mode)
- static MountableFile 	forHostPath(java.nio.file.Path path, int mode)
- java.lang.String 	getFilesystemPath() 
- int 	getFileMode()
- long 	getSize()


## Networking
Host and Container Comminications
  ```
  GenericContainer<?> container = new GenericContainer<>(
         DockerImageName.parse("testcontainers/helloworld:1.1.0"))
    .withExposedPorts(8080, 8081) // from container perspective
    .withEnv("MAGIC_NUMBER", "42")
    .withCommand("/bin/sh", "-c", "while true; do echo \"$MAGIC_NUMBER\" | nc -l -p 80; done");
    .withLogConsumer(new Slf4jLogConsumer(log));
  
String ipAddress = container.getHost();
Integer firstMappedPort = container.getMappedPort(8080); // from host perspective

// exposing host ports to the container
Testcontainers.exposeHostPorts(localServerPort);

// now can access this port from any containers that are launched. 
// From a container's perspective, the hostname will be host.testcontainers.internal 
// and the port will be the same value as localServerPort.
final String rootUrl = String.format("http://host.testcontainers.internal:%d/", localServerPort);
final RemoteWebDriver webDriver = browser.getWebDriver();
webDriver.get(rootUrl);
  ```

Advanced Networking
Docker can create custom networks and place containers on one or more networks. 
Then, communication can occur between networked containers without the need of exposing ports through the host.

```
try (
    Network network = Network.newNetwork();
    GenericContainer<?> foo = new GenericContainer<>(TestImages.TINY_IMAGE)
        .withNetwork(network)
        .withNetworkAliases("foo")
        .withCommand("/bin/sh", "-c", "while true ; do printf 'HTTP/1.1 200 OK\\n\\nyay' | nc -l -p 8080; done"
        );
    GenericContainer<?> bar = new GenericContainer<>(TestImages.TINY_IMAGE)
        .withNetwork(network)
        .withCommand("top")
) {
    foo.start();
    bar.start();

    String response = bar.execInContainer("wget", "-O", "-", "http://foo:8080").getStdout();
    assertThat(response).as("received response").isEqualTo("yay");
}
```

## Execute commands
- Container startup command: **withCommand** override the default command specified in Dockerfile
```
GenericContainer redisWithCustomPort = new GenericContainer(DockerImageName.parse("redis:5.0"))
    .withCommand("redis-server --port 7777")
```
- Executing a command in container(docker exec):
```
Container.ExecResult lsResult = container.execInContainer("ls", "-al", "/");
```
- Set Environment variables:
```
new GenericContainer(...).withEnv("API_TOKEN", "foo")
```

## File and Volumes
- File mapping: map a file or directory from host FS into the container as a volume:
```
String pathToFile = System.getProperty("user.home") + "/.aws";
new GenericContainer(...)
        .withFileSystemBind(pathToFile, "/home/user/.aws", BindMode.READ_ONLY)
```
- Volume mapping: map a file or directory on the classpath into the container as a volume 
```
new GenericContainer(...)
        .withClasspathResourceMapping("redis.conf","/etc/redis.conf",BindMode.READ_ONLY)
```
## Wait for container to be ready
- Wait Strategies: withStartupTimeout() 
- Http Wait strategy: 
```
   .waitingFor(Wait.forHttp("/")); //wait for 200 OK
Wait.forHttp("/").forStatusCode(200).forStatusCode(301);
Wait.forHttp("/all").forStatusCodeMatching(it -> it >= 200 && it < 300 || it == 401);
Wait.forHttp("/all").usingTls();
Wait.forHealthcheck();
   .waitingFor(Wait.forLogMessage(".*Ready to accept connections.*\\n", 1)); //wait for log output
   .waitingFor(new WaitStrategy())
```
- Startup cjeck Strategies: check that the container has reached the running state and has not exited
```
    .withStartupCheckStrategy( // StartupCheckStrategy  subclasses 
        new IsRunningStartupCheckStrategy() // default, just checks if container is running
        new OneShotStartupCheckStrategy().withTimeout(Duration.ofSeconds(3))  //only run briefly and exit of their own accord.
        new IndefiniteWaitOneShotStartupCheckStrategy() //no timeout, such as a long running task forms part of container startup
        new MinimumDurationRunningStartupCheckStrategy(Duration.ofSeconds(1)) //has been running for a defined minimum period of time.
    );
```
- Depending on another container: another container should be ready before starting
```
public GenericContainer<?> redis = new GenericContainer<>("redis:3.0.2").withExposedPorts(6379);
@Rule
public GenericContainer<?> nginx = new GenericContainer<>("nginx:1.9.4").dependsOn(redis).withExposedPorts(80);
```
## Access containter logs
- getLogs(): returns a String snapshot of a container's entire log output
- followOutput(): Consumer and STDOUT, STDERR, or both to follow
    - BaseConsumer
    - Slf4jLogConsumer
    - ToStringConsumer
    - WaitingConsumer

## Create image on-the-fly: ImageFromDockerfile().withXxx

## [Modules]()
### MockServer module with [MockServer](https://www.mock-server.com/)
MockServer mocks any server or service via HTTP or HTTPS, such as a REST or RPC service. 
- [mockserver javadoc API](https://javadoc.io/doc/org.mock-server)
- [MockServerClient](https://www.mock-server.com/mock_server/mockserver_clients.html)
```
public MockServerContainer mockServer = new MockServerContainer(MOCKSERVER_IMAGE);

new MockServerClient(mockServer.getHost(), mockServer.getServerPort())
    .when(request()
        .withPath("/person")
        .withQueryStringParameter("name", "peter"))
    .respond(response()
        .withBody("Peter the person!"));
```
