# Spring WebFlux
2 types of Publishers:
- Mono

Specialized Publisher that emits at most one item and then optionally terminates 
with an onComplete signal or an onError signal. In short, it returns 0 or 1 element.

![Mono](https://i0.wp.com/blog.knoldus.com/wp-content/uploads/2019/05/mono.png?w=903&ssl=1)
```
Mono noData = Mono.empty();
Mono data = Mono.just(“rishi”);
```
- Flux

Standard Publisher representing an asynchronous sequence of 0 to N emitted items, 
optionally terminated by either a completion signal or an error. These three types of signal 
translate to calls to a downstream subscriber’s onNext, onComplete, or onError methods.

![Flux](https://i1.wp.com/blog.knoldus.com/wp-content/uploads/2019/05/flux.png?w=833&ssl=1)
```
Flux flux1 = Flux.just(“foo”, “bar”, “foobar”);
Flux flux2 = Flux.fromIterable(Arrays.asList(“A”, “B”, “C”));
Flux flux3 = Flux.range(5, 3);

// subscribe
flux.subscribe();
```
Need to call the subscribe method on Flux to subscribe. 

##  Spring WebFlux
- Dependencies:
```
<parent>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-parent</artifactId>
  <version>2.1.5.RELEASE</version>
</parent>
<dependencies>
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-webflux</artifactId>
  </dependency>
<dependencies>
```
- Main Application
```
@SpringBootApplication
public class MainApplication {   
    public static void main(String[] args) {
        SpringApplication.run(MainApplication.class, args);
    }
}
```
- Annotation-Based WebFlux
```
@RestController
public class UserRestController {
  @Autowired
  private UserRepository userRepository;
  @GetMapping("/users")
  public Flux getUsers() {
        return userRepository.findAll();
  }
    
  @GetMapping("/users/{id}")
  public Mono getUserById(@PathVariable String id) {
        return userRepository.findById(id);
  }
    
  @PostMapping("/users")
  public Mono addUser(@RequestBody User user) {
        return userRepository.save(user);
  }
}
```
- Functional WebFlux:
UserRouter: defining routes
```
@Configuration
public class UserRouter {   
    @Bean
    public RouterFunction userRoutes(UserHandler userHandler) {        
        return RouterFunctions
                .route(RequestPredicates.POST("/users").and(accept(MediaType.APPLICATION_JSON)), userHandler::addUser)
                .andRoute(RequestPredicates.GET("/users").and(accept(MediaType.APPLICATION_JSON)), userHandler::getUsers)
                .andRoute(RequestPredicates.GET("/users/{id}").and(accept(MediaType.APPLICATION_JSON)), userHandler::getUserById);
    }
}
```
UserHandler: handle the request
```
@Component
public class UserHandler {    
    @Autowired
    private UserRepository userRepository;
    
    public Mono addUser(ServerRequest request) {
        Mono userMono = request.bodyToMono(User.class);
        return ServerResponse.ok().contentType(MediaType.APPLICATION_JSON)
                .body(fromPublisher(userMono.flatMap(userRepository::save), User.class));
    }
    
    public Mono getUsers(ServerRequest request) {
        return ServerResponse.ok().contentType(MediaType.APPLICATION_JSON)
                .body(userRepository.findAll(), User.class)
                .switchIfEmpty(ServerResponse.notFound().build());
    }
      
    public Mono getUserById(ServerRequest request) {
        String id = request.pathVariable("id");
        return ServerResponse.ok().contentType(MediaType.APPLICATION_JSON)
                .body(userRepository.findById(id), User.class)
                .switchIfEmpty(ServerResponse.notFound().build());
    }
}
```
