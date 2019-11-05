# Spring Audit

## JPA Audit
- [Tutorial](https://www.baeldung.com/database-auditing-jpa)
- Enabling JPA Auditing
```
@Configuration
@EnableTransactionManagement
@EnableJpaRepositories
@EnableJpaAuditing
public class PersistenceConfig { ... }
```

- Adding Spring's Entity Callback Listener
```
@Entity
@EntityListeners(AuditingEntityListener.class) 
// auditing information will be captured by the listener on persisting and updating the entity.
public class Bar {
    //Auditing the Author of Changes with Spring Security
    @Column(name = "created_by")
    @CreatedBy
    private String createdBy;
    
    @Column(name = "modified_by")
    @LastModifiedBy
    private String modifiedBy;
    
    //Tracking Created and Last Modified Dates
    @Column(name = "created_date", nullable = false, updatable = false)
    @CreatedDate
    private long createdDate;
 
    @Column(name = "modified_date")
    @LastModifiedDate
    private long modifiedDate;      
}
```
- Retrieving Audit Events
```
$ curl 'http://localhost:8080/actuator/auditevents?principal=alice&after=2019-10-
16T17%3A05%3A59.53Z&type=logout' -i -X GET
```


## Authentiation Audit 
- [Tutorial](https://www.baeldung.com/spring-boot-authentication-audit)
- [Tutorial](https://blog.codeleak.pl/2017/03/spring-boot-and-security-events-with-actuator.html)
- Listening for Authentication and Authorization Events
```
@Component
public class LoginAttemptsLogger {
    @EventListener
    public void auditEventHappened(AuditApplicationEvent auditApplicationEvent) {        
        AuditEvent auditEvent = auditApplicationEvent.getAuditEvent();
        System.out.println("Principal " + auditEvent.getPrincipal() + " - " + auditEvent.getType());
         WebAuthenticationDetails details = (WebAuthenticationDetails) auditEvent.getData().get("details");
        System.out.println("Remote IP address: " + details.getRemoteAddress());
        System.out.println("  Session Id: " + details.getSessionId());
    }
}
```
- Async events
The @EventListener is synchronous, but if asynchronous behavior is desired you can annotate event listener method with @Async and make sure that async is enabled (e.g. via @EnableAsync):
```
@Component
public class AuditApplicationEventListener {
    private static final Logger LOG = LoggerFactory.getLogger(AuditApplicationEventListener.class);

    @EventListener
    @Async
    public void onAuditEvent(AuditApplicationEvent event) {

    }
}
```
- Use Authentication Audit Listener to publish more information in AuditEvent
```
@Component
public class ExposeAttemptedPathAuthorizationAuditListener extends AbstractAuthorizationAuditListener {
     public static final String AUTHORIZATION_FAILURE = "AUTHORIZATION_FAILURE";
 
    @Override
    public void onApplicationEvent(AbstractAuthorizationEvent event) {
        if (event instanceof AuthorizationFailureEvent) {
            onAuthorizationFailureEvent((AuthorizationFailureEvent) event);
        }
    }
 
    private void onAuthorizationFailureEvent(AuthorizationFailureEvent event) {
        Map<String, Object> data = new HashMap<>();
        data.put("type", event.getAccessDeniedException().getClass().getName());
        data.put("message", event.getAccessDeniedException().getMessage());
        data.put("requestUrl", ((FilterInvocation)event.getSource()).getRequestUrl() );
         
        if (event.getAuthentication().getDetails() != null) {
            data.put("details", event.getAuthentication().getDetails());
        }
        publish(new AuditEvent(event.getAuthentication().getName(), AUTHORIZATION_FAILURE, data));
    }
}
```
The listener can get more infomation:
```
@Component
public class LoginAttemptsLogger {
    @EventListener
    public void auditEventHappened(AuditApplicationEvent auditApplicationEvent) {
        AuditEvent auditEvent = auditApplicationEvent.getAuditEvent();
          System.out.println("Principal " + auditEvent.getPrincipal() + " - " + auditEvent.getType());
         WebAuthenticationDetails details = (WebAuthenticationDetails) auditEvent.getData().get("details");
         System.out.println("  Remote IP address: " + details.getRemoteAddress());
        System.out.println("  Session Id: " + details.getSessionId());
        System.out.println("  Request URL: " + auditEvent.getData().get("requestUrl"));
    }
}
```
- 

- Storing Audit Events

By default, Spring Boot stores the audit events in an AuditEventRepository. If you don't create a bean with an own implementation, then an InMemoryAuditEventRepository will be wired for you.

The InMemoryAuditEventRepository is a kind of circular buffer that stores the last 4000 audit events in memory. Those events can then be accessed via the management endpoint http://localhost:8080/auditevents.

No events will be stored in the event repository if not published, hence /auditevents endpoint will always return an empty array. To fix this you can either inject audit repository or extend directly from org.springframework.boot.actuate.audit.listener.AuditListener:
```
@Component
public class AuditEventListener extends AbstractAuditListener {
    private static final Logger LOG = LoggerFactory.getLogger(AuditEventListener.class);
    @Autowired
    private AuditEventRepository auditEventRepository;

    @Override
    protected void onAuditEvent(AuditEvent event) {
        LOG.info("On audit event: timestamp: {}, principal: {}, type: {}, data: {}",
            event.getTimestamp(),
            event.getPrincipal(),
            event.getType(),
            event.getData()
        );
        auditEventRepository.add(event);
    }
}
```
## Audit Event Repository
- [Custom Audit Event Repository sample](https://github.com/sebasv89/spring-boot-examples/blob/master/src/main/java/co/svelez/springbootexample/repository/CustomAuditEventRepository.java)
