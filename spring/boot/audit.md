# Spring Audit

## JPA Audit
- {Tutorial](https://www.baeldung.com/database-auditing-jpa)
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
