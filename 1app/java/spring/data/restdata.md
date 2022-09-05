# [Data REST](https://docs.spring.io/spring-data/rest/docs/current/reference/html/)
- [Reference]
- [javadoc API](https://docs.spring.io/spring-data/rest/docs/current/api/)

## Set up
Spring Data REST builds on top of Spring Data repositories, analyzes the application’s domain model and exposes 
hypermedia-driven HTTP resources for aggregates contained in the model.

- Dependencies
For Spring Boot project:
```
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-rest</artifactId>
  </dependency>
```
For Maven project:
```
  <dependency>
    <groupId>org.springframework.data</groupId>
    <artifactId>spring-data-rest-webmvc</artifactId>
  </dependency>
```

Spring Data REST builds on top of Spring MVC. It creates a collection of Spring MVC controllers, JSON converters, and other beans to provide a RESTful front end. These components link up to the Spring Data JPA backend. This is all autoconfigured when using Spring Boot. 

Spring Data REST configuration is defined in a class called **RepositoryRestMvcConfiguration**.
To customize the configuration, register a **RepositoryRestConfigurer** and implement/override the configure()methods

Data REST supports repositories for:
    - Spring Data JPA
    - Spring Data MongoDB
    - Spring Data Neo4j
    - Spring Data GemFire
    - Spring Data Cassandra

- Repository Detection Strategy (cfg.setRepositoryDetectionStrategy())

Spring Data REST uses a RepositoryDetectionStrategy to determine whether a repository is exported as a REST resource:

| Strategy | Description |
|----------|-------------|
|ALL | Considers all repositories.|
|ANNOTATED|Considers repositories that are annotated with RepositoryRestResource or RestResource and don't have the exported flag not set to false.|
|DEFAULT|Exposes public interfaces or ones explicitly annotated with RepositoryRestResource.|
|VISIBILITY|Considers the repository interface's visibility, which means only public interfaces will be exposed.|

- spring.data.rest Properties

| Property | Description |
|----------|-------------|
|basePath|the root URI for Spring Data REST: default is "/"|
|defaultPageSize|change the default for the number of items served in a single page|
|maxPageSize|change the maximum number of items in a single page|
|pageParamName|change the name of the query parameter for selecting pages|
|limitParamName|change the name of the query parameter for the number of items to show in a page|
|sortParamName|change the name of the query parameter for sorting|
|defaultMediaType|change the default media type to use when none is specified|
|returnBodyOnCreate|change whether a body should be returned when creating a new entity|
|returnBodyOnUpdate|change whether a body should be returned when updating an entity|

- HATEOAS (resources is discoverable through the publication of links that point to the available resources).
        - links:
        - profile link:  Application-Level Profile Semantics (ALPS). 
        - Content-Type: application/hal+json or application/json

## [Accessing JPA Data with REST](https://spring.io/guides/gs/accessing-data-rest/)
- Entity
```
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Person {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private long id;

  private String firstName;
  private String lastName;

  public String getFirstName() {
    return firstName;
  }

  public void setFirstName(String firstName) {
    this.firstName = firstName;
  }

  public String getLastName() {
    return lastName;
  }

  public void setLastName(String lastName) {
    this.lastName = lastName;
  }
}
```
- Repository
```
import java.util.List;

import org.springframework.data.repository.query.Param;
import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

//@PreAuthorize("hasRole('ROLE_USER')")
@RepositoryRestResource(collectionResourceRel = "people", path = "people")
public interface PersonRepository extends PagingAndSortingRepository<Person, Long> {
  //@PreAuthorize("hasRole('ROLE_ADMIN')")
  List<Person> findByLastName(@Param("name") String name);
}
```
For MongoDB, the model class should have @Id:
```
import org.springframework.data.annotation.Id;
public class Person {
  @Id private String id;
  private String firstName;
  private String lastName;
}
```
and the Repository:
```
import java.util.List;
import org.springframework.data.repository.query.Param;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "people", path = "people")
public interface PersonRepository extends MongoRepository<Person, String> {
  List<Person> findByLastName(@Param("name") String name);
}
```
For Neo4j Data, need to setup connection to Neo4j, and the model class:
```
import org.springframework.data.neo4j.core.schema.Id;
import org.springframework.data.neo4j.core.schema.Node;
import org.springframework.data.neo4j.core.schema.GeneratedValue;

@Node
public class Person {
  @Id @GeneratedValue private Long id;
  private String firstName;
  private String lastName;
```
and the Repository:
```
import java.util.List;
import org.springframework.data.repository.query.Param;
import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "people", path = "people")
public interface PersonRepository extends PagingAndSortingRepository<Person, Long> {
  List<Person> findByLastName(@Param("name") String name);
}
```
the application needs to use @EnableTransactionManagement and @EnableNeo4jRepositories.

- Test the Application
```
$ curl http://localhost:8080
$ curl http://localhost:8080/people
```

## Repository Resources
Annotations in org.springframework.data.rest.core.annotation: 
- @RepositoryRestResource: for Repository class
- @RestResource: for Repository method
- @RepositoryEventHandler
- @Handle[Before|After][Create|Deleta|Save|LinkSave|LinkDelete]
- @Project
- @RepositoryRestController in org.springframework.data.rest.webmvc

### Fundamentals
The core functionality of Spring Data REST is to export resources for Spring Data repositories:
```
public interface OrderRepository extends CrudRepository<Order, Long> { }
```
Spring Data REST exposes a collection resource at */orders*. The path is derived from the uncapitalized, pluralized, simple class name of the domain class being managed. It also exposes an item resource for each of the items managed by the repository under the URI template */orders/{id}*.

## Repository Resources
### The Collection Resource
#### GET: 
Returns all entities the repository servers through its findAll() method:y
- findAll(Pageable): page(0 indexed, defaults to 0); size(defaults to 20)
- findAll(Sort): $propertyname,)+[asc|desc]?.
- findAll()
- /search:

#### HEAD
Returns whether the collection resource is available. findAll() methods are involved

#### POST
Creates a new entity from the given request body.
- save()

### The Item Resource: individual collection items 
#### GET
Returns a single entity:
- findById(...)
#### HEAD
 Rturns whether the item resource is available.
- findById(...)
#### PUT
Replaces the state of the target resource with the supplied request body.
- save(...)
#### PATCH
Partially updates the resources state.
- save(...)
#### DELETE
Deletes the resource exposed.
- delete(T)
- delete(ID)
- delete(Iterable)

### The Association Resource
Spring Data REST exposes sub-resources of every item resource for each of the associations the item resource has. The name and path of the resource defaults to the name of the association property and can be customized by using @RestResource on the association property.
- GET
- PUT
- POST
- DELETE

### The Search Resource
The search resource returns links for all query methods exposed by a repository. The path and name of the query method resources can be modified using @RestResource on the method declaration.
- GET: returns a list of links pointing to the individual query method resources
- HEAD: returns whether the search resource is available.

### The Query Resource
- GET: query individual resource with the parameters:
    - age: The page number to access (0 indexed, defaults to 0).
    - size: The page size requested (defaults to 20).
    - sort: A collection of sort directives in the format ($propertyname,)+[asc|desc]?.
- HAED: whether a query method resource is available.

### Paging and Sorting
To use paging in custom query methods, the method should accept an additional Pageable parameter and return a Page rather than a List:
```
@RestResource(path = "nameStartsWith", rel = "nameStartsWith")
public Page findByNameStartsWith(@Param("name") String name, Pageable p);
```
Spring Data REST recognizes sorting parameters that use the repository sorting support:
```
curl -v "http://localhost:8080/people/search/nameStartsWith?name=K&sort=name,desc"
```
