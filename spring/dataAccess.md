# [Spring Data Access](https://spring.io/projects/spring-data)
- Spring [Data Commons](https://github.com/spring-projects/spring-data-commons): [Reference](https://docs.spring.io/spring-data/commons/docs/current/reference/html/)
- Spring [JDBC](https://spring.io/projects/spring-data-jdbc) and [JDBC Ext](https://spring.io/projects/spring-data-jdbc-ext)
- Spring [Data JPA](https://spring.io/projects/spring-data-jpa)
- Spring [Data KeyValue](https://github.com/spring-projects/spring-data-keyvalue)
- Spring [Data LDAP](https://spring.io/projects/spring-data-ldap)
- Spring [Data MongoDB](https://spring.io/projects/spring-data-mongodb)
- Spring [Data R2DBC](https://spring.io/projects/spring-data-r2dbc): create DatabaseClient from ConnectionFactory.
- Spring [Data Redis](https://spring.io/projects/spring-data-redis): [RedisTemplate](https://docs.spring.io/spring-data/data-redis/docs/current/reference/html/#redis:template)
- Spring [Data REST](https://spring.io/projects/spring-data-rest)
- Spring [Data for Apache Cassandra](https://spring.io/projects/spring-data-cassandra)
- Spring [Data for Apache Geode](https://spring.io/projects/spring-data-geode)
- Spring [Data for Apache Solr](https://spring.io/projects/spring-data-solr)
- Spring [Data for Pivotal GemFire](https://spring.io/projects/spring-data-gemfire)
- Spring [Data Couchbase](https://spring.io/projects/spring-data-couchbase)
- Spring [Data Elasticsearch](https://spring.io/projects/spring-data-elasticsearch) 
- Spring [Data Neo4j](https://spring.io/projects/spring-data-neo4j) 
......

## Data Common
- Object creation
Spring Data automatically tries to detect a persistent entity’s constructor to be used to materialize objects of that type:
    - If there’s a no-argument constructor, it will be used. Other constructors will be ignored.
    - If there’s a single constructor taking arguments, it will be used.
    - If there are multiple constructors taking arguments, the one to be used by Spring Data will have to be annotated with @PersistenceConstructor.
    - The value resolution assumes constructor argument names to match the property names of the entity
    
-  Property population    
    - If the property is immutable but exposes a with… method, we use the with… method to create a new entity instance with the new property value.
    - If property access (i.e. access through getters and setters) is defined, we’re invoking the setter method.
    - If the property is mutable we set the field directly.
    - If the property is immutable we’re using the constructor to be used by persistence operations (see Object creation) to create a copy of the instance.
    - By default, we set the field value directly.
    
- CrudRepository Interface
```
public interface CrudRepository<T, ID> extends Repository<T, ID> {
  <S extends T> S save(S entity);      
  Optional<T> findById(ID primaryKey); 
  Iterable<T> findAll();               
  long count();                        
  void delete(T entity);               
  boolean existsById(ID primaryKey);   
  //......
}
```

- PagingAndSortingRepository interface
```
public interface PagingAndSortingRepository<T, ID> extends CrudRepository<T, ID> {
  Iterable<T> findAll(Sort sort);
  Page<T> findAll(Pageable pageable);
}
```

- Audit metadata
Spring provides @CreatedBy and @LastModifiedBy to capture the user who created or modified the entity as well as @CreatedDate and @LastModifiedDate to capture when the change happened.
```
class Customer {
  @CreatedBy
  private User user;

  @CreatedDate
  private DateTime createdDate;

  // … further properties omitted
}
```
- Query keywords

| Logical keyword | Keyword expressions |
| AND   | And |
| OR    | Or   |
| AFTER |  After, IsAfter |
| BEFORE |  Before, IsBefore |
| CONTAINING |  Containing, IsContaining, Contains |
| BETWEEN |  Between, IsBetween |
| ENDING_WITH |  EndingWith, IsEndingWith, EndsWith |
| EXISTS |  Exists |
| FALSE |  False, IsFalse |
| GREATER_THAN |  GreaterThan, IsGreaterThan |
| GREATER_THAN_EQUALS |  GreaterThanEqual, IsGreaterThanEqual |
| IN |  In, IsIn |
| IS |  Is, Equals, (or no keyword) |
| IS_EMPTY |  IsEmpty, Empty |
| IS_NOT_EMPTY |  IsNotEmpty, NotEmpty |
| IS_NOT_NULL |  NotNull, IsNotNull |
| IS_NULL |  Null, IsNull |
| LESS_THAN |  LessThan, IsLessThan |
| LESS_THAN_EQUAL |  LessThanEqual, IsLessThanEqual |
| LIKE |  Like, IsLike |
| NEAR |  Near, IsNear |
| NOT |  Not, IsNot |
| NOT_IN |  NotIn, IsNotIn |
| NOT_LIKE |  NotLike, IsNotLike |
| REGEX |  Regex, MatchesRegex, Matches |
| STARTING_WITH |  StartingWith, IsStartingWith, StartsWith |
| TRUE |  True, IsTrue |
| WITHIN |  Within, IsWithin |


## Spring JPA
- Model/Domain: @Entity
```
```
- Repository: interface inherit from JpaRepository, PagingAndSortingRepository or CrudRepository 
```
```
- Service: Combine Repositories to provides servive
```
```
- Controller: Use Service to render view
```
```

## Spring MongoDB
- Model: @Document

- Repository: interface inherit from MongoRepository, PagingAndSortingRepository or CrudRepository 


## Spring 

## Spring 
