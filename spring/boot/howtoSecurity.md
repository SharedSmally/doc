# [Spring Web Security](https://spring.io/projects/spring-security)

## Boot Security
- If define a @Configuration with a WebSecurityConfigurerAdapter in application, it switches off the default webapp security settings in Spring Boot.
- If provide a @Bean of type AuthenticationManager, AuthenticationProvider, or UserDetailsService, the default @Bean for InMemoryUserDetailsManager is not created. Your application has the full feature set of Spring Security available
- Enable HTTPS When Running behind a Proxy Server: Switch on the valve by adding some entries to application.properties for tomcat server:
```
server.tomcat.remote-ip-header=x-forwarded-for
server.tomcat.protocol-header=x-forwarded-proto
```
- To configure Spring Security to require a secure channel for all (or some) requests, consider adding your own WebSecurityConfigurerAdapter that adds the following HttpSecurity configuration:
```
@Configuration(proxyBeanMethods = false)
public class SslWebSecurityConfigurerAdapter extends WebSecurityConfigurerAdapter {

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // Customize the application security
        http.requiresChannel().anyRequest().requiresSecure();
    }
}
```
