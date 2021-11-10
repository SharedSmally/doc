# [Web Security](https://spring.io/projects/spring-security#learn)
- [Reference](https://docs.spring.io/spring-security/site/docs/current/reference/html5/)
- [API doc](https://docs.spring.io/spring-security/site/docs/current/api/)

## [Architecture](https://spring.io/guides/topicals/spring-security-architecture)
![architecture](https://github.com/spring-guides/top-spring-security-architecture/raw/main/images/authentication.png)

- Authentication:  AuthenticationManager
```
public interface AuthenticationManager {
  Authentication authenticate(Authentication authentication) throws AuthenticationException;
}
```

     - Return an Authentication (normally with authenticated=true) if it can verify that the input represents a valid principal.
     - Throw an AuthenticationException if it believes that the input represents an invalid principal.
     - Return null if it cannot decide.

- ProviderManager: implementaion of AuthenticationManager to delegates to a chain of AuthenticationProvider instances
     - If not recognize a particular Authentication instance type, it is skipped.
     - Can has an optional parent, which it can consult if all providers return null. 
     - If the parent is not available, a null Authentication results in an AuthenticationException

    Sometimes, an application has logical groups of protected resources (for example, all web resources that match a path pattern, such as /api/\*\*),
    and each group can have its own dedicated AuthenticationManager. Often, each of those is a ProviderManager, and they share a parent. 

- AuthenticationProvider: similar to AuthenticationManager, but has to allow the caller to query whether it supports a given Authentication type:
```
public interface AuthenticationProvider {
	Authentication authenticate(Authentication authentication) throws AuthenticationException;
	boolean supports(Class<?  extends Authentication> authenticationCls);
}
```

## Customizing Authentication Managers
- AuthenticationManagerBuilder: commonly used for setting up in-memory, JDBC, LDAP or custom UserDetailsService.
```
@Configuration
public class ApplicationSecurity extends WebSecurityConfigurerAdapter {
  @Autowired
  DataSource dataSource;
   ... // web stuff here
  @Override
  public void configure(AuthenticationManagerBuilder builder) {
    builder.jdbcAuthentication().dataSource(dataSource).withUser("dave").password("secret").roles("USER");
  }
}
```
AuthenticationManagerBuilder is local to build a “local” AuthenticationManager, it is a child of the global one. Can @Autowired the global one into the bean.

Spring Boot provides a default global AuthenticationManager (with only one user) unless pre-empted by providing the own bean of type AuthenticationManager.

## Authorization or Access Control

Once authentication is successful, the next authorization is using AccessDecisionManager. The implementaion delegate to a chain of AccessDecisionVoter instances
```
boolean supports(ConfigAttribute attribute);
boolean supports(Class<?> clazz);
int vote(Authentication authentication, S object, Collection<ConfigAttribute> attributes);
```
- object:  anything that a user might want to access (a web resource or a method in a Java class are the two most common cases
- attributes: a decoration of the secure Object with some metadata that determines the level of permission required to access it.  A typical ConfigAttribute is the name of a user role (like ROLE_ADMIN or ROLE_AUDIT), they often have special formats (like the ROLE_ prefix) or represent expressions that need to be evaluated.

- Web Security Filter
![Security Filter](https://github.com/spring-guides/top-spring-security-architecture/raw/main/images/security-filters.png)
The order of Filters:
- @Beans of type Filter with an @Order 
- implement Ordered, part of a FilterRegistrationBean

There can be multiple filter chains all managed by Spring Security in the same top level FilterChainProxy and all are unknown to the container. The Spring Security filter contains a list of filter chains and dispatches a request to the first chain that matches it. 
![security filters](https://github.com/spring-guides/top-spring-security-architecture/raw/main/images/security-filters-dispatch.png)

## Creating and Customizing Filter Chains
Add a @Bean of type WebSecurityConfigurerAdapter (or WebSecurityConfigurer) and decorate the class with @Order
```
@Configuration
@Order(SecurityProperties.BASIC_AUTH_ORDER - 10)
public class ApplicationConfigurerAdapter extends WebSecurityConfigurerAdapter {
  @Override
  protected void configure(HttpSecurity http) throws Exception {
    http.antMatcher("/match1/**")
      .authorizeRequests()
        .antMatchers("/match1/user").hasRole("USER")
        .antMatchers("/match1/spam").hasRole("SPAM")
        .anyRequest().isAuthenticated();
     ...;
  }
}
```
The actuator endpoints has an order of ManagementServerProperties.BASIC_AUTH_ORDER. To apply application security rules to the actuator endpoints:
```
@Configuration
@Order(ManagementServerProperties.BASIC_AUTH_ORDER + 1)
public class ApplicationConfigurerAdapter extends WebSecurityConfigurerAdapter {
  @Override
  protected void configure(HttpSecurity http) throws Exception {
    http.antMatcher("/foo/**")
     ...;
  }
}
```

## Method Security
```
@SpringBootApplication
@EnableGlobalMethodSecurity(securedEnabled = true)
public class SampleSecureApplication {

}
```
or
```
@Service
public class MyService {
  @Secured("ROLE_USER")
  public String secure() {
    return "Hello Security";
  }
}
```
There are other annotations used on methods to enforce security constraints, notably @PreAuthorize and @PostAuthorize, which let you write expressions containing references to method parameters and return values, respectively.

## Access Security Context: ThreadLocal
```
SecurityContext context = SecurityContextHolder.getContext();
Authentication authentication = context.getAuthentication();
assert(authentication.isAuthenticated);
```
In web point:
```
@RequestMapping("/foo")
public String foo(@AuthenticationPrincipal User user) {
  ... // do stuff with user
}
```
or
```
@RequestMapping("/foo")
public String foo(Principal principal) {
  Authentication authentication = (Authentication) principal;
  User = (User) authentication.getPrincipal();
  ... // do stuff with user
}
```
Processing Secure Methods Asynchronously, it need to wrap the SecurityContext with the task to be executed in background:
```
@Configuration
public class ApplicationConfiguration extends AsyncConfigurerSupport {
  @Override
  public Executor getAsyncExecutor() {
    return new DelegatingSecurityContextExecutorService(Executors.newFixedThreadPool(5));
  }
}
```


