# Spring Data
- Common
- JDBC
- JPA
- Redis
- Kafka
- LDAP
- ...

## Common
- [Reference](https://docs.spring.io/spring-data/commons/docs/2.5.6/reference/html/#reference)
- [API Doc](https://docs.spring.io/spring-data/commons/docs/2.5.6/api/): Annotations in org.springframework.data.annotation:
- 
| Annotation Type |	Description |
|-----------------|-------------|
|@CreatedBy | Declares a field as the one representing the principal that created the entity containing the field.|
|@CreatedDate | Declares a field as the one representing the date the entity containing the field was created.|
|@Id: Demarcates an identifier.|
|@LastModifiedBy  | Declares a field as the one representing the principal that recently modified the entity containing the field.|
|@LastModifiedDate |	Declares a field as the one representing the date the entity containing the field was recently modified.|
|@Immutable |	Annotation for persistent entities to indicate the class is designed in immutable way.|
|@Transient |	Marks a field to be transient for the mapping framework.|
|@Persistent |	Annotation to generally identify persistent types, fields and parameters.|
|@AccessType |	Annotation to define how Spring Data shall access values of persistent properties.|
|@PersistenceConstructor||
|@QueryAnnotation |	Meta-Annotation to mark a store specific annotation as a query annotation.|
|@ReadOnlyProperty |	Marks a field to be read-only for the mapping framework and therefore will not be persisted.|
|@Reference |	Meta-annotation to be used to annotate annotations that mark references to other objects.|
