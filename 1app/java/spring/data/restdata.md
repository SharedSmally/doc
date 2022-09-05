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

## Object Mapping
Currently only supports JSON using Jackson’s ObjectMapper. can configure Jackson’s ObjectMapper with custom mappings, serializers, and deserializers:

- Abstract Class Registration
```
@Override
protected void configureJacksonObjectMapper(ObjectMapper objectMapper) {
  objectMapper.registerModule(new SimpleModule("MyCustomModule") {
    @Override
    public void setupModule(SetupContext context) {
      context.addAbstractTypeResolver(
        new SimpleAbstractTypeResolver()
          .addMapping(MyInterface.class, MyInterfaceImpl.class));
    }
  });
}
```
- Adding Custom Serializers for Domain Types
```
@Override
public void setupModule(SetupContext context) {
  SimpleSerializers serializers = new SimpleSerializers();
  SimpleDeserializers deserializers = new SimpleDeserializers();

  serializers.addSerializer(MyEntity.class, new MyEntitySerializer());
  deserializers.addDeserializer(MyEntity.class, new MyEntityDeserializer());

  context.addSerializers(serializers);
  context.addDeserializers(deserializers);
}
```

##  Projections and Excerpts
### Projections
```
@Entity
public class Person {
  @Id @GeneratedValue
  private Long id;
  private String firstName, lastName;

  @OneToOne
  private Address address;
}
```
If Address has no Repositories, Spring Data REST exports all of its attributes (except the id). If don't expose the address:
```
//name of noAddresses and only apply for Person class
@Projection(name = "noAddresses", types = { Person.class })  
interface NoAddresses {   // Project is an Interface
  String getFirstName(); // exports only firstName
  String getLastName();  // exports only lastName
}
```
To view the projection to the resource, look up http://localhost:8080/persons/1?projection=noAddresses

The existing projections can be found in the ALPS profile.

### Hidden data using @JsonIgnore in JSON serialization
```
@Entity
public class User {
	@Id @GeneratedValue
	private Long id;
	private String name;

	@JsonIgnore private String password; 

private String[] roles;
```
Can create a projection that combines the two data fields:
```
@Projection(name = "virtual", types = { Person.class })
public interface VirtualProjection {
  @Value("#{target.firstName} #{target.lastName}")   //SpEL expression to render a read-only fullName
  String getFullName();
}
```

### Excerpts
An excerpt is a projection that is automatically applied to a resource collection.
```
@RepositoryRestResource(excerptProjection = NoAddresses.class)
interface PersonRepository extends CrudRepository<Person, Long> {}
```
 It directs Spring Data REST to use the NoAddresses projection when embedding Person resources into collections or related resources.
 
Normally the doamin objects are stored in different tables. The excerpt projection can put this extra piece of data inline to save an extra GET.
```
@Projection(name = "inlineAddress", types = { Person.class }) 
interface InlineAddress {
  String getFirstName();
  String getLastName();
  Address getAddress();   //included inline in Http GET request
}

@RepositoryRestResource(excerptProjection = InlineAddress.class)
interface PersonRepository extends CrudRepository<Person, Long> {}
```

## Conditional Operations with Headers
- ETag, If-Match, and If-None-Match Headers
The ETag header provides a way to tag resources to prevent overriding and reduce unnecessary calls:
```
class Sample {
	@Version Long version;  // in org.springframework.data.annotation
	Sample(Long version) {
		this.version = version;
	}
}
```
This REST resource has an ETag header with the value of the version field, can conditionally PUT, PATCH, or DELETE that resource if provide If-Match/If-None-Match header
```
curl -v -X PATCH -H 'If-Match: <value of previous ETag>' ...
```
- If-Modified-Since header to check whether a resource has been updated since the last request,
```
@Document
public class Receipt {
	public @Id String id;
	public @Version Long version;
  // DateTime,Date, Calendar, or long/Long
	public @LastModifiedDate Date date;  
	public String saleItem;
	public BigDecimal amount;
}
```

```
curl -H "If-Modified-Since: Wed, 24 Jun 2015 20:28:15 GMT" ...
```

## Validation
- Wire it by bean name : In order to tell Spring Data REST using a particular Validator assigned to a particular event, prefix the bean name with the event in question. For example, to validate instances of the Person class before new ones are saved into the repository, declare an instance of a **Validator<Person>** in  the ApplicationContext with a bean name of **beforeCreatePersonValidator**. 
  
- Assign validators manually:  register an validator instance to invoke validators after the correct event. In your configuration that implements RepositoryRestConfigurer, override the configureValidatingRepositoryEventListener method and call addValidator on the ValidatingRepositoryEventListener, passing the event on which this validator to be triggered and an instance of the validator:
```
@Override
void configureValidatingRepositoryEventListener(ValidatingRepositoryEventListener v) {
  v.addValidator("beforeSave", new BeforeSaveValidator());
}
```

## Events

The REST exporter emits eight different events throughout the process of working with an entity:
- BeforeCreateEvent/AfterCreateEvent
- BeforeSaveEvent/AfterSaveEvent
- BeforeLinkSaveEvent/AfterLinkSaveEvent
- BeforeDeleteEvent/AfterDeleteEvent

- Writing an ApplicationListener
```
  public class BeforeSaveEventListener extends AbstractRepositoryEventListener {
  @Override
  public void onBeforeSave(Object entity) {
    ... logic to handle inspecting the entity before the Repository saves it
  }

  @Override
  public void onAfterDelete(Object entity) {
    ... send a message that this entity has been deleted
  }
}
```
  
- Writing an Annotated Handler
```
@RepositoryEventHandler 
public class PersonEventHandler {
  @HandleBeforeSave
  public void handlePersonSave(Person p) {
    // … you can now deal with Person in a type-safe way
  }

  @HandleBeforeSave
  public void handleProfileSave(Profile p) {
    // … you can now deal with Profile in a type-safe way
  }
}
```
  To register the event handler, using @Component or create one in @Configuration:
  ```
@Configuration
public class RepositoryConfiguration {
  @Bean
  PersonEventHandler personEventHandler() {
    return new PersonEventHandler();
  }
}
  ```

## Integration
Programmatic Links:
- Manually assembling links.
- Using Spring HATEOAS’s LinkBuilder with linkTo(), slash(), and so on.
- Using Spring Data REST’s implementation of RepositoryEntityLinks.
```
public class MyWebApp {
	private RepositoryEntityLinks entityLinks;

	@Autowired
	public MyWebApp(RepositoryEntityLinks entityLinks) {
		this.entityLinks = entityLinks;
	}
}
```  
  
| Method | 	Description| 
| -------| ------------| 
| entityLinks.linkToCollectionResource(Person.class)| Provide a link to the collection resource of the specified type (Person, in this case).| 
| entityLinks.linkToItemResource(Person.class, 1)| Provide a link to a single resource.| 
| entityLinks.linkToPagedResource(Person.class, new PageRequest(…​))| Provide a link to a paged resource.| 
| entityLinks.linksToSearchResources(Person.class)| Provides a list of links for all the finder methods exposed by the corresponding repository.| 
| entityLinks.linkToSearchResource(Person.class, "findByLastName")| Provide a finder link by rel (that is, the name of the finder).| 
  

##  Meta
- ALPS: with Accept header: application/alsp+json for profile. Custom profile using *rest-messages.properties*.
- JSON Schema: with Accept header: application/schema+json.
```
curl -H 'Accept:application/schema+json' http://localhost:8080/profile/persons
```
	
## Security
- @Pre and @Post Security
```
@PreAuthorize("hasRole('ROLE_USER')") 
public interface PreAuthorizedOrderRepository extends CrudRepository<Order, UUID> {
	@PreAuthorize("hasRole('ROLE_ADMIN')")
	@Override
	Optional<Order> findById(UUID id);

	@PreAuthorize("hasRole('ROLE_ADMIN')") 
	@Override
	void deleteById(UUID aLong);

	@PreAuthorize("hasRole('ROLE_ADMIN')")
	@Override
	void delete(Order order);

	@PreAuthorize("hasRole('ROLE_ADMIN')")
	@Override
	void deleteAll(Iterable<? extends Order> orders);

	@PreAuthorize("hasRole('ROLE_ADMIN')")
	@Override
	void deleteAll();
}
```
- @Secured security: older style
```
@Secured("ROLE_USER") 
@RepositoryRestResource(collectionResourceRel = "people", path = "people")
public interface SecuredPersonRepository extends CrudRepository<Person, UUID> {
	@Secured("ROLE_ADMIN") 
	@Override
	void deleteById(UUID aLong);

	@Secured("ROLE_ADMIN")
	@Override
	void delete(Person person);

	@Secured("ROLE_ADMIN")
	@Override
	void deleteAll(Iterable<? extends Person> persons);

	@Secured("ROLE_ADMIN")
	@Override
	void deleteAll();
}
```
-  Enabling Method-level Security
```
@Configuration 
@EnableWebSecurity
@EnableGlobalMethodSecurity(securedEnabled = true, prePostEnabled = true) 
class SecurityConfiguration extends WebSecurityConfigurerAdapter { 
}
```

## ToolsL HAL Explorer

## Customizing Spring Data REST
- Customizing Item Resource URIs
- Customizing repository exposure
- Customizing supported HTTP methods
- Configuring the REST URL Path
```
@RepositoryRestResource(path = "people", rel = "people")
interface PersonRepository extends CrudRepository<Person, Long> {
  @RestResource(path = "names", rel = "names")
  List<Person> findByName(String name);
}
```
- Hiding Certain Repositories, Query Methods, or Fields: 
```
@RepositoryRestResource(exported = false)
  @RestResource(exported = false)
```
- Overriding Spring Data REST Response Handlers
```
@RepositoryRestController
public class ScannerController {
    private final ScannerRepository repository;

    @Autowired
    public ScannerController(ScannerRepository repo) { 
        repository = repo;
    }

    @RequestMapping(method = GET, value = "/scanners/search/listProducers") 
    public @ResponseBody ResponseEntity<?> getProducers() {
        List<String> producers = repository.listProducers(); 
        // do some intermediate processing, logging, etc. with the producers
        CollectionModel<String> resources = CollectionModel.of(producers); 
        resources.add(linkTo(methodOn(ScannerController.class).getProducers()).withSelfRel()); 
        // add other links as needed
        return ResponseEntity.ok(resources); 
    }
}
```
-  Customizing the JSON Output
- CORS Support
For Repository:
```
@CrossOrigin(origins = "http://domain2.example",
  methods = { RequestMethod.GET, RequestMethod.POST, RequestMethod.DELETE },
  maxAge = 3600)
interface PersonRepository extends CrudRepository<Person, Long> {}
```
For Controller
```
@RepositoryRestController
public class PersonController {
  @CrossOrigin(maxAge = 3600)
  @RequestMapping(path = "/people/xml/{id}", method = RequestMethod.GET, produces = MediaType.APPLICATION_XML_VALUE)
  public Person retrieve(@PathVariable Long id) {
    // …
  }
}
```
