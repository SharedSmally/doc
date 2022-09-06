# [JPA Repository](https://docs.spring.io/spring-data/data-jpa/docs/current/reference/html/#jpa.repositories)

## Query Methods

## Stored Procedures

## Locking

## Auditing
- Annotation-based Auditing Metadata
- @CreatedBy/@LastModifiedBy: capture the user who created or modified the entity
- @CreatedDate/@LastModifiedDate: capture when the change happened, with properties of type Joda-Time, DateTime, Date, Calendar, JDK8 date and time types, and long or Long.
```
class Customer {
  @CreatedBy
  private User user;

  @CreatedDate
  private Instant createdDate;

  // … further properties omitted
}
```
- Audit metadata in embedded entity
```
class Customer {
  private AuditMetadata auditingMetadata;
  // … further properties omitted
}

class AuditMetadata {
  @CreatedBy
  private User user;

  @CreatedDate
  private Instant createdDate;
}
```
