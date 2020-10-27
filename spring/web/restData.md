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
