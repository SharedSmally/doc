#  Spring Data REST
Spring Data REST builds on top of the Spring Data repositories and automatically exports those as REST resources. It builds hypermedia-driven REST web services that connect to Spring Data repositories using HAL as the driving hypermedia type.

- [Reference](https://docs.spring.io/spring-data/rest/docs/current/reference/html/)
- [Tutorial](https://www.baeldung.com/spring-data-rest-intro)

## Configurations
Spring Data REST Properties in application.properties:
- basePath: the root URI for Spring Data REST. Default is /
- defaultPageSize: change the default for the number of items served in a single page
- maxPageSize: change the maximum number of items in a single page
- pageParamName: change the name of the query parameter for selecting pages
- limitParamName: change the name of the query parameter for the number of items to show in a page
- sortParamName: change the name of the query parameter for sorting
- defaultMediaType: change the default media type to use when none is specified
- returnBodyOnCreate: change whether a body should be returned when creating a new entity
- returnBodyOnUpdate: change whether a body should be returned when updating an entity
```
spring.data.rest.basePath=/api
```

## Repository resources
```
public interface OrderRepository extends CrudRepository<Order, Long> 
{ }

public interface OrderRepository extends PagingAndSortingRepository<T, ID>
{
   @RestResource(path = "nameStartsWith", rel = "nameStartsWith")
   public Page findByNameStartsWith(@Param("name") String name, Pageable p);
}

$ curl http://localhost:8080/people/?size=5
$ curl "http://localhost:8080/persons?page=1&size=5"
$ curl -v "http://localhost:8080/people/search/nameStartsWith?name=K&sort=name,desc"
```
For this repository, Spring Data REST exposes a collection resource at /orders. 
It also exposes an item resource for each of the items managed by the repository under the URI template /orders/{id}.

By default the HTTP methods to interact with these resources map to the according methods of CrudRepository

Supported Media Types
- application/hal+json
- application/json

### The Collection Resource: GET, HEAD, PUT
Spring Data REST exposes a collection resource named after the uncapitalized, pluralized version of the 
domain class the exported repository is handling. Both the name of the resource and the path can be 
customized by using @RepositoryRestResource on the repository interface.

#### GET method
Returns all entities the repository servers through its findAll(…) method. The following methods are used if present (decending order):
```
findAll(Pageable)
findAll(Sort)
findAll()
```
The resource takes the following parameters:
- page: The page number to access (0 indexed, defaults to 0).
- size: The page size requested (defaults to 20).
- sort: A collection of sort directives in the format ($propertyname,)+[asc|desc]?.

#### HEAD method
The HEAD method returns whether the collection resource is available. It has no status codes, media types, or related resources.
The following methods are used if present (decending order):
- findAll(Pageable)
- findAll(Sort)
- findAll()

#### POST method
The POST method creates a new entity from the given request body. The following methods are used if present (decending order):
- save(…)

### The Item Resource: GET, PUT, PATCH, DELETE
Spring Data REST exposes a resource for individual collection items as sub-resources of the collection resource.
#### GET: returns a single entity
- findById(…)

#### HEAD:  whether the item resource is available
- findById(…)

#### PUT: replaces the state of the target resource with the supplied request body
- save(…)

#### PATCH: similar to PUT, but partially updates the resources state.
- save(…)

Supported additioanl application/patch+json and application/merge-patch+json.

#### DELETE: deletes the resource exposed.
- delete(T)
- delete(ID)
- delete(Iterable)


### The Association Resource: GET, PUT, POST, DELETE
Spring Data REST exposes sub-resources of every item resource for each of the associations the item resource has.
The name and path of the resource defaults to the name of the association property and can be customized by using @RestResource on the association property.


### The Search Resource: GET, HEAD
The search resource returns links for all query methods exposed by a repository. The path and name of the query method resources can be modified using @RestResource on the method declaration

### The Query Method Resource: GET, HEAD
The query method resource runs the exposed query through an individual query method on the repository interface.

Parameters:
- page: The page number to access (0 indexed, defaults to 0).
- size: The page size requested (defaults to 20).
- sort: A collection of sort directives in the format ($propertyname,)+[asc|desc]?.


## Events
- BeforeCreateEvent
- BeforeCreateEvent
- BeforeCreateEvent
- AfterCreateEvent
- BeforeSaveEvent
- AfterSaveEvent
- BeforeLinkSaveEvent
- AfterLinkSaveEvent
- BeforeDeleteEvent
- AfterDeleteEvent

### Writing an ApplicationListener
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
### Writing an Annotated Handler
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
## Conditional Operations with Headers
- ETag(tag resources), If-Match, and If-None-Match Headers
```
import org.springframework.data.annotation.Version;

public class Sample {
	@Version Long version; 
	Sample(Long version) {
		this.version = version;
	}
}
```
This POJO has an ETag header with the value of the version field when served up as a REST resource by Spring Data REST.
Can conditionally PUT, PATCH, or DELETE that resource if supply a If-Match header such as the following:
```
curl -v -X PATCH -H 'If-Match: <value of previous ETag>' ...
```
Only if the resource’s current ETag state matches the If-Match header is the operation carried out

The If-None-Match header provides an alternative. Instead of conditional updates, If-None-Match allows conditional queries:
```
curl -v -H 'If-None-Match: <value of previous etag>' ...
```
- If-Modified-Since header
The If-Modified-Since header provides a way to check whether a resource has been updated since the last request, which lets applications avoid resending the same data:
```
@Document
public class Receipt {

	public @Id String id;
	public @Version Long version;
	public @LastModifiedDate Date date;  

	public String saleItem;
	public BigDecimal amount;
}

curl -H "If-Modified-Since: Wed, 24 Jun 2015 20:28:15 GMT" ...
```

## Integration

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
- entityLinks.linkToCollectionResource(Person.class)  Provide a link to the collection resource of the specified type (Person, in this case).
- entityLinks.linkToSingleResource(Person.class, 1)    Provide a link to a single resource.
- entityLinks.linkToPagedResource(Person.class, new PageRequest(…​))    Provide a link to a paged resource.
- entityLinks.linksToSearchResources(Person.class)     Provides a list of links for all the finder methods exposed by the corresponding repository.
- entityLinks.linkToSearchResource(Person.class, "findByLastName")  Provide a finder link by rel (that is, the name of the finder).

## Metadata: Application-Level Profile Semantics (ALPS)
Spring Data REST provides an ALPS document for every exported repository. It contains information about both the RESTful transitions and the attributes of each repository.
```
$ curl localhost:8080/profile
$ curl -H 'Accept:application/schema+json' http://localhost:8080/profile/persons   # get JSON schema
```
- Adding Custom Details to Your ALPS Descriptions
```
rest.description.person=A collection of people
rest.description.person.id=primary key used internally to store a person (not for RESTful usage)
rest.description.person.firstName=Person's first name
rest.description.person.lastName=Person's last name
rest.description.person.address=Person's address
```

## Security
- @Pre and @Post Security
```
@PreAuthorize("hasRole('ROLE_USER')") 
public interface PreAuthorizedOrderRepository extends CrudRepository<Order, UUID> {
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
- @Secured security: Older role-based security
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

## Tool: The HAL Browser:  data-rest-hal-browser

## Customizing Spring Data REST
- Customizing Item Resource URIs for Java 8
```
@Component
public class SpringDataRestCustomization implements RepositoryRestConfigurer {
  @Override
  public void configureRepositoryRestConfiguration(RepositoryRestConfiguration config) {
    config.withEntityLookup()
      .forRepository(UserRepository.class)
      .withIdMapping(User::getUsername)
      .withLookup(UserRepository::findByUsername);
  }
}
```
- Customizing Item Resource URIs for Java non-8
```
@Component
public class UserEntityLookup extends EntityLookupSupport<User> {

    private final UserRepository repository;

    public UserEntityLookup(UserRepository repository) {
        this.repository = repository;
    }

    @Override
    public Serializable getResourceIdentifier(User entity) {
        return entity.getUsername();
    }

    @Override
    public Object lookupEntity(Serializable id) {
        return repository.findByUsername(id.toString());
    }
}
```

- Customizing repository exposure
This can be customized by explicitly setting a RepositoryDetectionStrategy (usually through the enum RepositoryDetectionStrategies) on RepositoryRestConfiguration
- ALL — exposes all Spring Data repositories regardless of their Java visibility or annotation configuration.
- DEFAULT — exposes public Spring Data repositories or ones explicitly annotated with @RepositoryRestResource and its exported attribute not set to false.
- VISIBILITY — exposes only public Spring Data repositories regardless of annotation configuration.
- ANNOTATED — only exposes Spring Data repositories explicitly annotated with @RepositoryRestResource and its exported attribute not set to false.

- Customizing supported HTTP methods

- Hiding Certain Repositories, Query Methods, or Fields: exported = false
```
@RepositoryRestResource(exported = false)
interface PersonRepository extends CrudRepository<Person, Long> {}

@RepositoryRestResource(path = "people", rel = "people")
interface PersonRepository extends CrudRepository<Person, Long> {
  @RestResource(exported = false)
  List<Person> findByName(String name);
}

@Entity
public class Person {
  @Id @GeneratedValue private Long id;

  @OneToMany
  @RestResource(exported = false)
  private Map<String, Profile> profiles;
}
```
- Hiding Repository CRUD Methods
```
@RepositoryRestResource(path = "people", rel = "people")
interface PersonRepository extends CrudRepository<Person, Long> {
  @Override
  @RestResource(exported = false)
  void delete(Long id);

  @Override
  @RestResource(exported = false)
  void delete(Person entity);
}
```
- Overriding Spring Data REST Response Handlers: @RepositoryRestController
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
        Resources<String> resources = new Resources<String>(producers); 
        resources.add(linkTo(methodOn(ScannerController.class).getProducers()).withSelfRel()); 
        // add other links as needed
        return ResponseEntity.ok(resources); 
    }
}
```

- Configuring CORS
```
@CrossOrigin
interface PersonRepository extends CrudRepository<Person, Long> {}

@CrossOrigin(origins = "http://domain2.example",  methods = { RequestMethod.GET, RequestMethod.POST, RequestMethod.DELETE },  maxAge = 3600)
interface PersonRepository extends CrudRepository<Person, Long> {}
```
- Repository REST Controller Method CORS Configuration
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

-  Global CORS Configuration
```
@Component
public class SpringDataRestCustomization extends RepositoryRestConfigurerAdapter {
  @Override
  public void configureRepositoryRestConfiguration(RepositoryRestConfiguration config) {
    config.getCorsRegistry().addMapping("/person/**")
      .allowedOrigins("http://domain2.example")
      .allowedMethods("PUT", "DELETE")
      .allowedHeaders("header1", "header2", "header3")
      .exposedHeaders("header1", "header2")
      .allowCredentials(false).maxAge(3600);
  }
}
```

## Sample
- Dependencies: data-rest, data-jpa, database; HATEOAS
- Define Entity model
```
@Entity
public class WebsiteUser {
 
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
 
    private String name;
    private String email;
 
    // standard getters and setters
}
```
- Define Repository to customize the REST endpoin
```
@RepositoryRestResource(collectionResourceRel = "users", path = "users")
public interface UserRepository extends PagingAndSortingRepository<WebsiteUser, Long> {
    List<WebsiteUser> findByName(@Param("name") String name);
}
```
- Start Application:
```
@SpringBootApplication
public class SpringDataRestApplication {
    public static void main(String[] args) {
        SpringApplication.run(SpringDataRestApplication.class, args);
    }
}
```
- Access the REST API: CRUD operations
```
$ curl http://localhost:8080/ 

$ curl -i -X POST -H "Content-Type:application/json" -d '{  "name" : "Test", \ 
"email" : "test@test.com" }' http://localhost:8080/users

$ curl http://localhost:8080/users/1

$ curl http://localhost:8080/users/search/findByName?name=test
```
