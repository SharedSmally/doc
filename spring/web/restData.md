#  Spring Data REST
Build hypermedia-driven REST web services that connect to Spring Data repositories using HAL as the driving hypermedia type.

- [Reference](https://docs.spring.io/spring-data/rest/docs/current/reference/html/)
- [Tutorial](https://www.baeldung.com/spring-data-rest-intro)

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
