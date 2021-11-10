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


