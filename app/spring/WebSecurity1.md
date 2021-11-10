# [Web Security](https://docs.spring.io/spring-security/site/docs/current/reference/html5/)

## Cross Site Request Forgery (CSRF)
```
<form method="post"    action="/transfer">
  <input type="hidden"  name="_csrf"  value="4bfd1575-3ad1-4d21-96c7-4ef2d9f86721"/>
  <input type="text"  name="amount"/>
  <input type="text"  name="routingNumber"/>
  <input type="hidden"  name="account"/>
  <input type="submit"  value="Transfer"/>
</form>
```
The Request:
```
POST /transfer HTTP/1.1
Host: bank.example.com
Cookie: JSESSIONID=randomid
Content-Type: application/x-www-form-urlencoded

amount=100.00&routingNumber=1234&account=9876&_csrf=4bfd1575-3ad1-4d21-96c7-4ef2d9f86721
```
## Security Headers
- Default Security HTTP Response Headers
```
Cache-Control: no-cache, no-store, max-age=0, must-revalidate
Pragma: no-cache
Expires: 0
X-Content-Type-Options: nosniff
Strict-Transport-Security: max-age=31536000 ; includeSubDomains
X-Frame-Options: DENY
X-XSS-Protection: 1; mode=block
```
- Content Security Policy (CSP)
```
Content-Security-Policy: script-src https://trustedscripts.example.com; report-uri /csp-report-endpoint/
Content-Security-Policy-Report-Only: script-src 'self' https://trustedscripts.example.com; report-uri /csp-report-endpoint/
Referrer-Policy: same-origin
Feature-Policy: geolocation 'self'
Permissions-Policy: geolocation=(self)
Clear-Site-Data: "cache", "cookies", "storage", "executionContexts"
```

## Modules
-  Core — spring-security-core.jar: 
    -  org.springframework.security.core
    -  org.springframework.security.access
    -  org.springframework.security.authentication
    -  org.springframework.security.provisioning
- Remoting — spring-security-remoting.jar
    -  org.springframework.security.remotin
- Web — spring-security-web.jar
    - org.springframework.security.web
- Config — spring-security-config.jar
    - org.springframework.security.config
- LDAP — spring-security-ldap.jar
    - org.springframework.security.ldap.
- OAuth 2.0 Core — spring-security-oauth2-core.jar
    - org.springframework.security.oauth2.core
- OAuth 2.0 Client — spring-security-oauth2-client.jar
    - org.springframework.security.oauth2.client
- OAuth 2.0 JOSE — spring-security-oauth2-jose.jar
    - org.springframework.security.oauth2.jwt
    - org.springframework.security.oauth2.jose
- OAuth 2.0 Resource Server — spring-security-oauth2-resource-server.jar
    - org.springframework.security.oauth2.server.resource
- ACL — spring-security-acl.jar
    - org.springframework.security.acls
- CAS — spring-security-cas.jar
    - org.springframework.security.cas
- OpenID — spring-security-openid.jar
    - org.springframework.security.openid
- Test — spring-security-test.jar
- Taglibs — spring-secuity-taglibs.jar

Spring Boot Auto Configuration

## Spring Boot automatically:
- Enables Spring Security’s default configuration, which creates a servlet Filter as a bean named springSecurityFilterChain. This bean is responsible for all the security (protecting the application URLs, validating submitted username and passwords, redirecting to the log in form, and so on) within your application.
- Creates a UserDetailsService bean with a username of user and a randomly generated password that is logged to the console.
- Registers the Filter with a bean named springSecurityFilterChain with the Servlet container for every request.

## Authentication
```
SecurityContext context = SecurityContextHolder.getContext();
Authentication authentication = context.getAuthentication();
String username = authentication.getName();
Object principal = authentication.getPrincipal();
Collection<? extends GrantedAuthority> authorities = authentication.getAuthorities();
```

The Authentication contains:
- principal - identifies the user. When authenticating with a username/password this is often an instance of UserDetails.
- credentials - Often a password. In many cases this will be cleared after the user is authenticated to ensure it is not leaked.
- authorities - the GrantedAuthoritys are high level permissions the user is granted. A few examples are roles or scopes.
![authentication](https://docs.spring.io/spring-security/site/docs/current/reference/html5/images/servlet/authentication/architecture/abstractauthenticationprocessingfilter.png)

## Username/Password Authentication
- Form Login: GET /login
```
protected void configure(HttpSecurity http) throws Exception {
    http
        // ...
        .formLogin(form -> form
            .loginPage("/login")
            .permitAll()
        );
}
```
login.html:
```
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xmlns:th="https://www.thymeleaf.org">
    <head>
        <title>Please Log In</title>
    </head>
    <body>
        <h1>Please Log In</h1>
        <div th:if="${param.error}">
            Invalid username and password.</div>
        <div th:if="${param.logout}">
            You have been logged out.</div>
        <form th:action="@{/login}" method="post">
            <div>
            <input type="text" name="username" placeholder="Username"/>
            </div>
            <div>
            <input type="password" name="password" placeholder="Password"/>
            </div>
            <input type="submit" value="Log in" />
        </form>
    </body>
</html>
```
LoginController.java
```
@Controller
class LoginController {
    @GetMapping("/login")
    String login() {
        return "login";
    }
}
```
- Basic Authentication: WWW-Authenticate header => retry with user and password
```
protected void configure(HttpSecurity http) {
    http
        // ...
        .httpBasic(withDefaults());
}
```
- Digest Authentication
```
@Autowired
UserDetailsService userDetailsService;

DigestAuthenticationEntryPoint entryPoint() {
    DigestAuthenticationEntryPoint result = new DigestAuthenticationEntryPoint();
    result.setRealmName("My App Relam");
    result.setKey("3028472b-da34-4501-bfd8-a355c42bdf92");
}

DigestAuthenticationFilter digestAuthenticationFilter() {
    DigestAuthenticationFilter result = new DigestAuthenticationFilter();
    result.setUserDetailsService(userDetailsService);
    result.setAuthenticationEntryPoint(entryPoint());
}

protected void configure(HttpSecurity http) throws Exception {
    http
        // ...
        .exceptionHandling(e -> e.authenticationEntryPoint(authenticationEntryPoint()))
        .addFilterBefore(digestFilter());
}
```
- In-Memory Authentication: use InMemoryUserDetailsManager implementing UserDetailsService
```
@Bean
public UserDetailsService users() {
    UserDetails user = User.builder()
        .username("user")
        .password("{bcrypt}$2a$10$GRLdNijSQMUvl/au9ofL.eDwmoohzzS7.rmNSJZ.0FxO/BTk76klW")
        .roles("USER")
        .build();
    UserDetails admin = User.builder()
        .username("admin")
        .password("{bcrypt}$2a$10$GRLdNijSQMUvl/au9ofL.eDwmoohzzS7.rmNSJZ.0FxO/BTk76klW")
        .roles("USER", "ADMIN")
        .build();

    // The builder will ensure the passwords are encoded before saving in memory
    UserBuilder users = User.withDefaultPasswordEncoder();
    UserDetails user = users
        .username("user")
        .password("password")
        .roles("USER")
        .build();
        
    return new InMemoryUserDetailsManager(user, admin);
}
```
- JDBC Authentication

User Schema
```
create table users(
    username varchar_ignorecase(50) not null primary key,
    password varchar_ignorecase(500) not null,
    enabled boolean not null
);

create table authorities (
    username varchar_ignorecase(50) not null,
    authority varchar_ignorecase(50) not null,
    constraint fk_authorities_users foreign key(username) references users(username)
);
create unique index ix_auth_username on authorities (username,authority);
```
Group Schema
```
create table groups (
    id bigint generated by default as identity(start with 0) primary key,
    group_name varchar_ignorecase(50) not null
);

create table group_authorities (
    group_id bigint not null,
    authority varchar(50) not null,
    constraint fk_group_authorities_group foreign key(group_id) references groups(id)
);

create table group_members (
    id bigint generated by default as identity(start with 0) primary key,
    username varchar(50) not null,
    group_id bigint not null,
    constraint fk_group_members_group foreign key(group_id) references groups(id)
);
```
Setup DataSource: used for JdbcUserDetailsManager
```
@Bean
DataSource dataSource() {
    return new EmbeddedDatabaseBuilder()
        .setType(H2)
        .addScript("classpath:org/springframework/security/core/userdetails/jdbc/users.ddl")
        .build();
}
@Bean
UserDetailsManager users(DataSource dataSource) {
    UserDetails user = User.builder()
        .username("user")
        .password("{bcrypt}$2a$10$GRLdNijSQMUvl/au9ofL.eDwmoohzzS7.rmNSJZ.0FxO/BTk76klW")
        .roles("USER")
        .build();
    UserDetails admin = User.builder()
        .username("admin")
        .password("{bcrypt}$2a$10$GRLdNijSQMUvl/au9ofL.eDwmoohzzS7.rmNSJZ.0FxO/BTk76klW")
        .roles("USER", "ADMIN")
        .build();
    JdbcUserDetailsManager users = new JdbcUserDetailsManager(dataSource);
    users.createUser(user);
    users.createUser(admin);
    return users;
}
```
    - UserDetails

UserDetails is returned by the UserDetailsService. The DaoAuthenticationProvider validates the UserDetails and then returns an Authentication that has a principal that is the UserDetails returned by the configured UserDetailsService.

    - UserDetailsService

UserDetailsService is used by DaoAuthenticationProvider for retrieving a username, password, and other attributes for authenticating with a username and password. Spring Security provides in-memory and JDBC implementations of UserDetailsService.
```
@Bean
CustomUserDetailsService customUserDetailsService() {
    return new CustomUserDetailsService();
}
```
    - PasswordEncoder

Spring Security’s servlet support storing passwords securely by integrating with PasswordEncoder. Customizing the PasswordEncoder implementation used by Spring Security can be done by exposing a PasswordEncoder Bean.

    - DaoAuthenticationProvider

DaoAuthenticationProvider is an AuthenticationProvider implementation that leverages a UserDetailsService and PasswordEncoder to authenticate a username and password.


- LDAP Authentication
    - Setting up an Embedded LDAP Server: Embedded UnboundID or ApacheDS Server
    
users.ldif
```
dn: ou=groups,dc=springframework,dc=org
objectclass: top
objectclass: organizationalUnit
ou: groups

dn: ou=people,dc=springframework,dc=org
objectclass: top
objectclass: organizationalUnit
ou: people

dn: uid=admin,ou=people,dc=springframework,dc=org
objectclass: top
objectclass: person
objectclass: organizationalPerson
objectclass: inetOrgPerson
cn: Rod Johnson
sn: Johnson
uid: admin
userPassword: password

dn: uid=user,ou=people,dc=springframework,dc=org
objectclass: top
objectclass: person
objectclass: organizationalPerson
objectclass: inetOrgPerson
cn: Dianne Emu
sn: Emu
uid: user
userPassword: password

dn: cn=user,ou=groups,dc=springframework,dc=org
objectclass: top
objectclass: groupOfNames
cn: user
uniqueMember: uid=admin,ou=people,dc=springframework,dc=org
uniqueMember: uid=user,ou=people,dc=springframework,dc=org

dn: cn=admin,ou=groups,dc=springframework,dc=org
objectclass: top
objectclass: groupOfNames
cn: admin
uniqueMember: uid=admin,ou=people,dc=springframework,dc=org
```
Embedded UnboundID Server
```
<dependency>
    <groupId>com.unboundid</groupId>
    <artifactId>unboundid-ldapsdk</artifactId>
    <version>4.0.14</version>
    <scope>runtime</scope>
</dependency>

@Bean
UnboundIdContainer ldapContainer() {
    return new UnboundIdContainer("dc=springframework,dc=org", "classpath:users.ldif");
}
```
Embedded ApacheDS Server
```
<dependency>
    <groupId>org.apache.directory.server</groupId>
    <artifactId>apacheds-core</artifactId>
    <version>1.5.5</version>
    <scope>runtime</scope>
</dependency>
<dependency>
    <groupId>org.apache.directory.server</groupId>
    <artifactId>apacheds-server-jndi</artifactId>
    <version>1.5.5</version>
    <scope>runtime</scope>
</dependency>

@Bean
ApacheDSContainer ldapContainer() {
    return new ApacheDSContainer("dc=springframework,dc=org","classpath:users.ldif");
}
```
LDAP ContextSource: similar to JDBC DataSource
```
ContextSource contextSource(UnboundIdContainer container) {
    return new DefaultSpringSecurityContextSource("ldap://localhost:53389/dc=springframework,dc=org");
}
```
Using Bind Authentication
```
@Bean
BindAuthenticator authenticator(BaseLdapPathContextSource contextSource) {
    BindAuthenticator authenticator = new BindAuthenticator(contextSource);
    authenticator.setUserDnPatterns(new String[] { "uid={0},ou=people" });
    return authenticator;
}

@Bean
LdapAuthenticationProvider authenticationProvider(LdapAuthenticator authenticator) {
    return new LdapAuthenticationProvider(authenticator);
}
```
