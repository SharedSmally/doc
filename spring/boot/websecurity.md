# Spring Security
- [Security Architecture](https://spring.io/guides/topicals/spring-security-architecture)
    - Authentication: interface [Authentication](https://docs.spring.io/spring-security/site/docs/current/api/org/springframework/security/core/Authentication.html) and [AuthenticationManager](https://docs.spring.io/spring-security/site/docs/current/api/org/springframework/security/authentication/AuthenticationManager.html): The implementation is ProviderManager, which contains a list of AuthenticationProvider. There are list of authenticatoin providers(ldap,dao,jaas,jwt,oauth2,Oidc,openID,openSAML) that implement the interface of AuthenticationProvider.
    - Customizing Authentication Managers: use [AuthenticationManagerBuilder](https://docs.spring.io/spring-security/site/docs/current/api/org/springframework/security/config/annotation/authentication/builders/AuthenticationManagerBuilder.html) in  WebSecurityConfigurerAdapter::initialize(AuthenticationManagerBuilder builder, DataSource dataSource) or configure(AuthenticationManagerBuilder builder).
    - Access Control: interface [AccessDecisionManager](https://docs.spring.io/spring-security/site/docs/current/api/org/springframework/security/access/AccessDecisionManager.html). The implemented classes are  AffirmativeBased, ConsensusBased, UnanimousBased. They are inherited from AbstractAccessDecisionManager that contains a list of AccessDecisionVoter<?>. The implemented classes are AbstractAclVoter, AclEntryVoter, AuthenticatedVoter, Jsr250Voter, MessageExpressionVoter, PreInvocationAuthorizationAdviceVoter, RoleHierarchyVoter, RoleVoter, WebExpressionVoter.
    - Creating and Customizing Filter Chains: [WebSecurityConfigurerAdapter](https://docs.spring.io/spring-security/site/docs/current/api/org/springframework/security/config/annotation/web/configuration/WebSecurityConfigurerAdapter.html)::configure(HttpSecurity http).
- [Security Java API](https://docs.spring.io/spring-security/site/docs/current/api/)
- [Security Reference](https://docs.spring.io/spring-security/site/docs/5.2.2.BUILD-SNAPSHOT/reference/htmlsingle/)


## Dependencies
- Spring Boot: org.springframework.boot::spring-boot-starter-security starter
- Maven: org.springframework.security::spring-security-web and spring-security-config and in org.springframework:spring-framework-bom in dependencyManagement.
- For POST with Form:
```
<form method="post"    action="/transfer">
<input type="hidden" name="_csrf"   value="4bfd1575-3ad1-4d21-96c7-4ef2d9f86721"/>
<input type="text"  name="amount"/>
<input type="text"  name="routingNumber"/>
<input type="hidden" name="account"/>
<input type="submit" value="Transfer"/>
</form>

POST /transfer HTTP/1.1
Host: bank.example.com
Cookie: JSESSIONID=randomid
Content-Type: application/x-www-form-urlencoded

amount=100.00&routingNumber=1234&account=9876&_csrf=4bfd1575-3ad1-4d21-96c7-4ef2d9f86721
```

## Modules
- Core — spring-security-core.jar: include packages:
    - org.springframework.security.core
    - org.springframework.security.access
    - org.springframework.security.authentication
    - org.springframework.security.provisioning
- Remoting — spring-security-remoting.jar: provides integration with Spring Remoting. 
- Web — spring-security-web.jar: contains filters and related web-security infrastructure. 
- Config — spring-security-config.jar: contains the security namespace parsing code and Java configuration code to use Spring Security XML namespace for configuration or Spring Security’s Java Configuration support.
-  LDAP — spring-security-ldap.jar: provides LDAP authentication and provisioning.
-  OAuth 2.0 Core — spring-security-oauth2-core.jar: support for the OAuth 2.0 Authorization Framework and for OpenID Connect Core 1.0. including client, resource server, and authorization server. 
- OAuth 2.0 Client — spring-security-oauth2-client.jar: client support for OAuth 2.0 Authorization Framework and OpenID Connect Core 1.0. used for OAuth 2.0 Login or OAuth Client support. 
-  OAuth 2.0 JOSE — spring-security-oauth2-jose.jar: support for the JOSE (Javascript Object Signing and Encryption) framework to securely transfer claims between parties. It is built from a collection of specifications:
    - JSON Web Token (JWT): org.springframework.security.oauth2.jwt
    - JSON Web Signature (JWS): org.springframework.security.oauth2.jose
    - JSON Web Encryption (JWE)
    - JSON Web Key (JWK)
- OAuth 2.0 Resource Server — spring-security-oauth2-resource-server.jar: support for OAuth 2.0 Resource Servers via OAuth 2.0 Bearer Tokens. 
- ACL — spring-security-acl.jar: a specialized domain object ACL implementation. 
- CAS — spring-security-cas.jar: support CAS client integration for web authentication with a CAS single sign-on server.
- OpenID — spring-security-openid.jar: support OpenID web authentication against an external OpenID server.
- Test — spring-security-test.jar: support for testing with Spring Security.

## Spring Security Applications
### 1. Spring Boot Auto Configuration
- Enables Spring Security’s default configuration that creates a servlet Filter as a bean named springSecurityFilterChain. This bean is responsible for all the security (protecting the application URLs, validating submitted username and passwords, redirecting to the log in form, and so on) within your application.
- Creates a UserDetailsService bean with a username of user and a randomly generated password that is logged to the console.
- Registers the Filter with a bean named springSecurityFilterChain with the Servlet container for every request.
```
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
	@Override
	protected void configure(HttpSecurity http) throws Exception {
		http.authorizeRequests(authorizeRequests ->
					authorizeRequests
						.antMatchers("/css/**", "/index").permitAll()
						.antMatchers("/user/**").hasRole("USER")
				)
			.formLogin(formLogin ->
					formLogin
						.loginPage("/login")
						.failureUrl("/login-error")
				);
	}

	@Bean
	public UserDetailsService userDetailsService() {
		UserDetails userDetails = User.withDefaultPasswordEncoder()
				.username("user")
				.password("password")
				.roles("USER")
				.build();
		return new InMemoryUserDetailsManager(userDetails);
	}
}
```
### 2. Spring Java Configuration
- create a servlet Filter springSecurityFilterChain
```
import org.springframework.context.annotation.*;
import org.springframework.security.config.annotation.web.configuration.*;
import org.springframework.security.core.userdetails.*;
import org.springframework.security.provisioning.*;
@EnableWebSecurity
public class WebSecurityConfig {
    @Bean
    public UserDetailsService userDetailsService() {
        UserDetails user = User.withDefaultPasswordEncoder()
            .username("user")
            .password("password")
            .roles("USER")
            .build();
        return  new InMemoryUserDetailsManager(user);
    }
}

@Controller
public class MainController {
	@RequestMapping("/")
	public String root() {
		return "redirect:/index";
	}

	@RequestMapping("/index")
	public String index() {
		return "index";
	}

	@RequestMapping("/user/index")
	public String userIndex() {
		return "user/index";
	}

	@RequestMapping("/login")
	public String login() {
		return "login";
	}

	@RequestMapping("/login-error")
	public String loginError(Model model) {
		model.addAttribute("loginError", true);
		return "login";
	}
}
```

-  register the springSecurityFilterChain with the war from AbstractSecurityWebApplicationInitializer
```
import org.springframework.security.web.context.*;
public class SecurityInitializer extends AbstractSecurityWebApplicationInitializer {
    public SecurityInitializer() {
        super(WebSecurityConfig.class);
    }
}
```


