# Spring Web Security
## Reference
- [Site](https://spring.io/projects/spring-security)
- [Quick Start](https://docs.spring.io/spring-security/reference/getting-spring-security.html)
- [Reference](https://docs.spring.io/spring-security/reference/index.html)
- [API Javadoc](https://docs.spring.io/spring-security/site/docs/current/api/)

## Tutorial
- [Getting started with Spring Security and Spring Boot](https://reflectoring.io/spring-security/)
- [Spring Security without the WebSecurityConfigurerAdapter](https://spring.io/blog/2022/02/21/spring-security-without-the-websecurityconfigureradapter)

## Web Security
- Added Web Security dependency
- In application.yml, the default configs (default username **user** and the default password from the logs):
```
spring:
  security:
    user:
      name: admin
      password: passw@rd
```

The Security Components:
- Servlet Filters
- Authentication
- Authorization

### Servlet Filters
**DefaultSecurityFilterChain** triggers a chain of filters before the request reaches the **DispatcherServlet** that handles incoming web requests and dispatches them to the appropriate handler for processing.

![FilterChain](https://reflectoring.io/images/posts/getting-started-with-spring-security/filterChain_hu6933403b7320f6f893a41150b2491685_82682_1079x0_resize_q90_box.JPG)

- DelegatingFilterProxy It is a servlet filter provided by Spring that acts as a bridge between the Servlet container and the Spring Application Context. The DelegatingFilterProxy class is responsible for wiring any class that implements javax.servlet.Filter into the filter chain.
 - FilterChainProxy Spring security internally creates a FilterChainProxy bean named springSecurityFilterChain wrapped in DelegatingFilterProxy. The FilterChainProxy is a filter that chains multiple filters based on the security configuration. Thus, the DelegatingFilterProxy delegates request to the FilterChainProxy which determines the filters to be invoked.
 - SecurityFilterChain: The security filters in the SecurityFilterChain are beans registered with FilterChainProxy. An application can have multiple SecurityFilterChain. FilterChainProxy uses the RequestMatcher interface on HttpServletRequest to determine which SecurityFilterChain needs to be called.

 Spring Security provides a default filter chain that calls a set of predefined and ordered filters (in org.springframework.security.web):
- csrf.CsrfFilter : This filter applies CSRF protection by default to all REST endpoints.
- authentication.logout.LogoutFilter : This filter gets called when the user logs out of the application. The default registered instances of LogoutHandler are called that are responsible for invalidating the session and clearing the SecurityContext. Next, the default implementation of LogoutSuccessHandler redirects the user to a new page (/login?logout).
- authentication.UsernamePasswordAuthenticationFilter : Validates the username and password for the URL (/login) with the default credentials provided at startup.
- authentication.ui.DefaultLoginPageGeneratingFilter : Generates the default login page html at /login
- authentication.ui.DefaultLogoutPageGeneratingFilter : Generates the default logout page html at /login?logout
- authentication.www.BasicAuthenticationFilter : This filter is responsible for processing any request that has an HTTP request header of Authorization, Basic Authentication scheme, Base64 encoded username-password. On successful authentication, the Authentication object will be placed in the SecurityContextHolder.
- authentication.AnonymousAuthenticationFilter : If no Authentication object is found in the SecurityContext, it creates one with the principal anonymousUser and role ROLE_ANONYMOUS.
- access.ExceptionTranslationFilter : Handles AccessDeniedException and AuthenticationException thrown within the filter chain. For AuthenticationException instances of AuthenticationEntryPoint are required to handle responses. For AccessDeniedException, this filter will delegate to AccessDeniedHandler whose default implementation is AccessDeniedHandlerImpl.
- access.intercept.FilterSecurityInterceptor : This filter is responsible for authorising every request that passes through the filter chain before the request hits the controller.

### Authentication
Authentication is the process of verifying a user’s credentials and ensuring their validity. 
- UsernamePasswordAuthenticationFilter gets called as a part of the security filter chain when FormLogin is enabled i.e when the request is made to the URL /login. This class is a specific implementation of the base AbstractAuthenticationProcessingFilter. When an authentication attempt is made, the filter forwards the request to an AuthenticationManager.
- UsernamePasswordAuthenticationToken is an implementation of Authentication interface. This class specifies that the authentication mechanism must be via username-password.
- With the authentication details obtained, an AuthenticationManager tries to authenticate the request with the help of an appropriate implementation of AuthenticationProvider and a fully authenticated Authentication object is returned. The default implementation is the DaoAuthenticationProvider which retrieves user details from UserDetailsService. If authentication fails, AuthenticationException is thrown.
- The loadUserByUsername(username) method of the UserDetailsService returns UserDetails object that contains user data. If no user is found with the given username, UsernameNotFoundException is thrown.
- On successful authentication, SecurityContext is updated with the currently authenticated user.

The ProviderManager is the most common implementation of AuthenticationManager. As seen in the diagram, the ProviderManager delegates the request to a list of configured AuthenticationProvider each of which is queried to see if it can perform the authentication. If the authentication fails with ProviderNotFoundException, which is a special type of AuthenticationException, it indicates that the ProviderManager does not support the type of Authentication passed. This architecture allows us to configure multiple authentication types within the same application.
![ProviderManager](https://reflectoring.io/images/posts/getting-started-with-spring-security/providerManager_hu6933403b7320f6f893a41150b2491685_64311_1210x0_resize_q90_box.JPG)

### Authorization

Authorization is a process of ensuring that the user or a system accessing a resource has valid permissions.

In the Spring security filter chain, the FilterSecurityInterceptor triggers the authorization check. Authentication runs before authorization. This filter checks for valid permissions after the user has been successfully authenticated. In case authorization fails, AccessDeniedException is thrown.

Every user instance holds a list of GrantedAuthority objects. GrantedAuthority is an interface that has a single method:
```
public interface GrantedAuthority extends Serializable {
    String getAuthority();
}
```

Spring Security provides authorization support via both granted authorities and roles using the hasAuthority() and hasRole() methods respectively. These methods are used for expression-based security and are a part of the interface SecurityExpressionOperations. For most cases, both methods can be interchangeably used, the most notable difference being the hasRole() need not specify the ROLE prefix while the hasAuthority() needs the complete string to be explicitly specified. For instance, hasAuthority("ROLE_ADMIN") and hasRole("ADMIN") perform the same task.

## Security Configuration
The SpringBootWebSecurityConfiguration class from the org.springframework.boot.autoconfigure.security.servlet package provides a default set of spring security configurations for spring boot applications. 

```
class SpringBootWebSecurityConfiguration {
    @ConditionalOnDefaultWebSecurity
    static class SecurityFilterChainConfiguration {
        SecurityFilterChainConfiguration() {
        }

        @Bean
        @Order(2147483642)
        SecurityFilterChain defaultSecurityFilterChain(HttpSecurity http) throws Exception {
            ((AuthorizedUrl) http.authorizeRequests().anyRequest()).authenticated();
            http.formLogin();
            http.httpBasic();
            return (SecurityFilterChain) http.build();
        }
    }
}
```
### Customize default configuration
Customize formLogin, Logout, SessionManagement, 
```
@Configuration
@EnableWebSecurity
public class SecurityConfiguration {
   @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http.authorizeRequests(request -> 
                request.antMatchers(ENDPOINTS_WHITELIST).permitAll()
                        .anyRequest().authenticated())
                .csrf().disable()
                .formLogin(form -> form
                        .loginPage(LOGIN_URL)
                        .loginProcessingUrl(LOGIN_URL)
                        .failureUrl(LOGIN_FAIL_URL)
                        .usernameParameter(USERNAME)
                        .passwordParameter(PASSWORD)
                        .defaultSuccessUrl(DEFAULT_SUCCESS_URL));
        return http.build();
    }
}
```
- Configure Multiple Filter Chains
Spring Security allows us to have more than one co-existing security configuration giving us more control over the application. (Multiple SecurityFilterChain Beans with different Order)
```
    @Bean
    @Order(1)
    public SecurityFilterChain bookFilterChain(HttpSecurity http) throws Exception {
        ...
    }
    @Bean
    public UserDetailsService userDetailsService() {
        return new InMemoryUserDetailsManager(props.getUserDetails());
    }

    @Bean
    public AuthenticationEntryPoint userAuthenticationErrorHandler() {
        UserAuthenticationErrorHandler userAuthenticationErrorHandler =
                new UserAuthenticationErrorHandler();
        userAuthenticationErrorHandler.setRealmName("Basic Authentication");
        return userAuthenticationErrorHandler;
    }
    @Bean
    @Order(2)
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {

        ...
    }

    @Bean
    public WebSecurityCustomizer webSecurityCustomizer() {
        return (web) -> web.ignoring().antMatchers("/library/info");
    }
```

