# Spring Security

## [boot/autoconfigure/security])(https://github.com/spring-projects/spring-boot/tree/master/spring-boot-project/spring-boot-autoconfigure/src/main/java/org/springframework/boot/autoconfigure/security)
- [Security Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#security-properties): from SecurityProperties
   - spring.security.filter.dispatcher-types: Security filter chain dispatcher types. async, error, request
   - spring.security.filter.order: Security filter chain order. -100
   - spring.security.user.name: Default user name.
   - spring.security.user.password: Password for the default user name.
   - spring.security.user.roles: Granted roles for the default user name. 
- oauth2: 
   - Client: OAuth2ClientProperties for spring.security.oauth2.client, and ClientsConfiguredCondition extends SpringBootCondition.
         - Map<String, Provider>: spring.security.oauth2.client.provider.*: OAuth provider
         - Map<String, Registration>: spring.security.oauth2.client.registration.*: OAuth client registrations
         - OAuth2ClientPropertiesRegistrationAdapte: Adapter class to convert OAuth2ClientProperties} to ClientRegistration.
         - OAuth2ClientAutoConfiguration import OAuth2ClientRegistrationRepositoryConfiguration and OAuth2WebSecurityConfiguration before SecurityAutoConfiguration. OAuth2WebSecurityConfiguration configs beans WebSecurityConfigurerAdapter, authorizedClientRepository, authorizedClientService (@ConditionalOnMissingBean), and OAuth2ClientRegistrationRepositoryConfiguration for bean clientRegistrationRepository. 
   - Resource Server: 
   
- reactive
- rsocket	
- saml2	
- servlet

## [Samples](https://github.com/spring-projects/spring-security/tree/master/samples/boot/oauth2login)

## Tutorial
- [SSO-OAuth2](https://www.baeldung.com/sso-spring-security-oauth2)
