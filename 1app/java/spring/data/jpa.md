# Spring Data JPA
- [Reference](https://docs.spring.io/spring-data/data-jpa/docs/current/reference/html/)
- [javadoc API](https://docs.spring.io/spring-data/jpa/docs/current/api/)

## Repository
- Repository
```
public interface Repository<T,ID> {}
```
- CrudRepository
```
public interface CrudRepository<T,ID>
extends Repository<T,ID> {
   long 	count()
   void 	delete(T entity)
   void 	deleteAll()
   void 	deleteAll(Iterable<? extends T> entities)
   void 	deleteAllById(Iterable<? extends ID> ids)
   void 	deleteById(ID id)
   boolean 	existsById(ID id)
   Iterable<T> 	findAll()
   Iterable<T> 	findAllById(Iterable<ID> ids)
   Optional<T> 	findById(ID id)
   <S extends T> S 	save(S entity)
   <S extends T> Iterable<S> 	saveAll(Iterable<S> entities)
}
```
- PagingAndSortingRepository
```
public interface PagingAndSortingRepository<T,ID>
extends CrudRepository<T,ID> {
   Page<T> 	findAll(Pageable pageable)
   Iterable<T> 	findAll(Sort sort)
}
```
- JpaRepository<T,ID>;  (MongoRepository, ...)
```
public interface JpaRepository<T,ID>
extends PagingAndSortingRepository<T,ID>, QueryByExampleExecutor<T> {
   void 	deleteAllByIdInBatch(Iterable<ID> ids)
   void 	deleteAllInBatch()
   void 	deleteAllInBatch(Iterable<T> entities)
   List<T> 	findAll() 
   <S extends T> List<S> 	findAll(Example<S> example) 
   <S extends T> List<S> 	findAll(Example<S> example, Sort sort) 
   List<T> 	findAll(Sort sort) 
   List<T> 	findAllById(Iterable<ID> ids) 
   void 	flush()
   T 	getReferenceById(ID id)
   <S extends T> List<S> 	saveAll(Iterable<S> entities) 
   <S extends T> List<S> 	saveAllAndFlush(Iterable<S> entities)
   <S extends T> S 	saveAndFlush(S entity)
}
```

## Data JPA Usage
- Declare an interface extending Repository or subinterfaces
- Declare query methods on the interface.
```
interface PersonRepository extends Repository<Person, Long> {
  List<Person> findByLastname(String lastname);
}
```
- Set up Spring to create proxy instances for those interfaces:
```
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
@EnableJpaRepositories  // @Enable${store}Repositories for other store, such as mongo
           // use basePackage to scan the reposotories
class Config { … }
```
- Inject the repository instance and use it
```
class SomeClient {
  private final PersonRepository repository;
  SomeClient(PersonRepository repository) { this.repository = repository; }
  void doSomething() {
    List<Person> persons = repository.findByLastname("Matthews");
  }
}
```

## Defining Repository Interfaces
- Selectively exposing CRUD methods
```
@NoRepositoryBean   // only expose save() and findById
interface MyBaseRepository<T, ID> extends Repository<T, ID> {
  Optional<T> findById(ID id);
  <S extends T> S save(S entity);
}

interface UserRepository extends MyBaseRepository<User, Long> {
  User findByEmailAddress(EmailAddress emailAddress);
}
```
Using a unique Spring Data module, such as jpa, mongo, makes things simple, for all repository interfaces in the defined scope are bound to the Spring Data module. 

##  Defining Query Methods
- By deriving the query from the method name directly.
- By using a manually defined query.

### Query Creation
```
interface PersonRepository extends Repository<Person, Long> {
  List<Person> findByEmailAddressAndLastname(EmailAddress emailAddress, String lastname);

  // Enables the distinct flag for the query
  List<Person> findDistinctPeopleByLastnameOrFirstname(String lastname, String firstname);
  List<Person> findPeopleDistinctByLastnameOrFirstname(String lastname, String firstname);

  // Enabling ignoring case for an individual property
  List<Person> findByLastnameIgnoreCase(String lastname);
  // Enabling ignoring case for all suitable properties
  List<Person> findByLastnameAndFirstnameAllIgnoreCase(String lastname, String firstname);

  // Enabling static ORDER BY for a query
  List<Person> findByLastnameOrderByFirstnameAsc(String lastname);
  List<Person> findByLastnameOrderByFirstnameDesc(String lastname);
}
```
Parsing query method names is divided into subject and predicate. The first part (*find...By, exists...By*) defines the subject of the query, the second part forms the predicate. The subject can contain further expressions. Any text between *find* (or other subject keywords) and *By* is descriptive unless using one of the result-limiting keywords such as a Distinct to set a distinct flag on the query to be created or Top/First to limit query results. The first By acts as a delimiter to indicate the start of the actual criteria predicate

The actual result of parsing the method depends on the persistence store for which you create the query. Some general rules:
- The expressions are usually property traversals combined with operators that can be concatenated. Can combine property expressions with AND and OR. also support for operators such as Between, LessThan, GreaterThan, and Like for the property expressions.
- The method parser supports setting an IgnoreCase flag for individual properties (findByLastnameIgnoreCase(…)) or for all properties of a type that supports ignoring case (usually String instances — for example, findByLastnameAndFirstnameAllIgnoreCase(…)).
-can apply static ordering by appending an OrderBy clause to the query method that references a property and by providing a sorting direction (Asc or Desc). 

###  Property Expressions
Property expressions can refer only to a direct property of the managed entity, and the parsed property is a property of the managed domain class, but can also define constraints by traversing nested properties:
```
List<Person> findByAddressZipCode(ZipCode zipCode);  
//A Person has an Address with a ZipCode, and this creates the he x.address.zipCode property traversal, if not found, use x.addressZip.code.
List<Person> findByAddress_ZipCode(ZipCode zipCode); // use _ to  manually define traversal points.
```

### Special parameter handling
Data JPA can recognizes certain specific types like Pageable and Sort, to apply pagination and sorting to the queries dynamically:
```
Page<User> findByLastname(String lastname, Pageable pageable);
Slice<User> findByLastname(String lastname, Pageable pageable);
List<User> findByLastname(String lastname, Sort sort);
List<User> findByLastname(String lastname, Pageable pageable);
```
 - Paging and Sorting
 Define simple sorting expressions by using property names, concatenate expressions to collect multiple criteria into one expression.
 ```
 Sort sort = Sort.by("firstname").ascending().and(Sort.by("lastname").descending());
 ```
 For type-safe way to define sort expressions:
 ```
 TypedSort<Person> person = Sort.sort(Person.class);

Sort sort = person.by(Person::getFirstname).ascending().and(person.by(Person::getLastname).descending());
 ```
If the store implementation supports Querydsl, use the generated metamodel types to define sort expressions:
```
QSort sort = QSort.by(QPerson.firstname.asc()).and(QSort.by(QPerson.lastname.desc()));
```

### Limiting Query Results
Can limit the results of query methods by using the **first** or **top** keywords, which you can use interchangeably. You can append an optional numeric value to top or first to specify the maximum result size to be returned. If the number is left out, a result size of 1 is assumed. 
```
User findFirstByOrderByLastnameAsc();
User findTopByOrderByAgeDesc();
Page<User> queryFirst10ByLastname(String lastname, Pageable pageable);
Slice<User> findTop3ByLastname(String lastname, Pageable pageable);
List<User> findFirst10ByLastname(String lastname, Sort sort);
List<User> findTop10ByLastname(String lastname, Pageable pageable);
```
The limiting expressions also support the **Distinct** keyword for datastores that support distinct queries. Also, for the queries that limit the result set to one instance, wrapping the result into with the Optional keyword is supported.

###  Repository Methods Returning Collections or Iterables
Query methods that return multiple results can use standard Java Iterable, List, and Set. It also supports returning Spring Data’s Streamable, a custom extension of Iterable, as well as collection types provided by Vavr. 

- Using Streamable as Query Method Return Type
can use Streamable as alternative to Iterable or any collection type. It provides convenience methods to access a non-parallel Stream (missing from Iterable) and the ability to directly ….filter(…) and ….map(…) over the elements and concatenate the Streamable to other
```
interface PersonRepository extends Repository<Person, Long> {
  Streamable<Person> findByFirstnameContaining(String firstname);
  Streamable<Person> findByLastnameContaining(String lastname);
}

Streamable<Person> result = repository.findByFirstnameContaining("av")
  .and(repository.findByLastnameContaining("ea"));
```

- Returning Custom Streamable Wrapper Types

- Support for Vavr Collections

- Nullability Annotations
repository CRUD methods that return an individual aggregate instance use Java 8’s Optional to indicate the potential absence of a value.

    - @NonNullApi: Used on the package level to declare that the default behavior for parameters and return values is, respectively, neither to accept nor to produce null values.
    - @NonNull: Used on a parameter or return value that must not be null (not needed on a parameter and return value where @NonNullApi applies).
    - @Nullable: Used on a parameter or return value that can be null

### Streaming Query Results
can process the results of query methods incrementally by using a Java 8 Stream<T> as the return type:
```
@Query("select u from User u")
Stream<User> findAllByCustomQueryAndStream();

Stream<User> readAllByFirstnameNotNull();

@Query("select u from User u")
Stream<User> streamAllPaged(Pageable pageable);
```   

### Asynchronous Query Results
Can run repository queries asynchronously by using Spring’s asynchronous method running capability. This means the method returns immediately upon invocation while the actual query occurs in a task that has been submitted to a Spring TaskExecutor. Asynchronous queries differ from reactive queries.  
```
@Async
Future<User> findByFirstname(String firstname);               

@Async
CompletableFuture<User> findOneByFirstname(String firstname); 

@Async
ListenableFuture<User> findOneByLastname(String lastname);  
```   

### Create Repository Instances
Trigger the repository infrastructure by using a store-specific @Enable${store}Repositories annotation on a Java configuration class.  
```
@Configuration
@EnableJpaRepositories("com.acme.repositories")
class ApplicationConfiguration {
  @Bean
  EntityManagerFactory entityManagerFactory() {
    // …
  }
}
```
   
## Appendix
- query method subject keywords 

| Keyword | Description | 
|---------|-------------|
| find…By, read…By, get…By, query…By, search…By, stream…By| General query method returning typically the repository type, a Collection or Streamable subtype or a result wrapper such as Page, GeoResults or any other store-specific result wrapper. Can be used as findBy…, findMyDomainTypeBy… or in combination with additional keywords.| 
| exists…By| Exists projection, returning typically a boolean result.| 
| count…By| Count projection returning a numeric result.| 
| delete…By, remove…By| Delete query method returning either no result (void) or the delete count.| 
| …First<number>…, …Top<number>…| Limit the query results to the first <number> of results. This keyword can occur in any place of the subject between find (and the other keywords) and by.| 
| …Distinct…| Use a distinct query to return only unique results. Consult the store-specific documentation whether that feature is supported. This keyword can occur in any place of the subject between find (and the other keywords) and by.| 
   
- query method predicate keywords 

|   Logical keyword |	Keyword expressions |
|-------------------|-----------------------|
| AND| And| 
| OR| Or| 
| AFTER| After, IsAfter| 
| BEFORE| Before, IsBefore| 
| CONTAINING| Containing, IsContaining, Contains| 
| BETWEEN| Between, IsBetween| 
| ENDING_WITH| EndingWith, IsEndingWith, EndsWith| 
| EXISTS| Exists| 
| FALSE| False, IsFalse| 
| GREATER_THAN| GreaterThan, IsGreaterThan| 
| GREATER_THAN_EQUALS| GreaterThanEqual, IsGreaterThanEqual| 
| IN| In, IsIn| 
| IS| Is, Equals, (or no keyword)| 
| IS_EMPTY| IsEmpty, Empty| 
| IS_NOT_EMPTY| IsNotEmpty, NotEmpty| 
| IS_NOT_NULL| NotNull, IsNotNull| 
| IS_NULL| Null, IsNull| 
| LESS_THAN| LessThan, IsLessThan| 
| LESS_THAN_EQUAL| LessThanEqual, IsLessThanEqual| 
| LIKE| Like, IsLike| 
| NEAR| Near, IsNear| 
| NOT| Not, IsNot| 
| NOT_IN| NotIn, IsNotIn| 
| NOT_LIKE| NotLike, IsNotLike| 
| REGEX| Regex, MatchesRegex, Matches| 
| STARTING_WITH| StartingWith, IsStartingWith, StartsWith| 
| TRUE| True, IsTrue| 
| WITHIN| Within, IsWithin| 
   
- Query predicate modifier keywords Keyword 

| Keyword |	Description |
|---------|-------------|
|IgnoreCase, IgnoringCase|Used with a predicate keyword for case-insensitive comparison.|
|AllIgnoreCase, AllIgnoringCase|Ignore case for all suitable properties. Used somewhere in the query method predicate.|
|OrderBy…|Specify a static sorting order followed by the property path and direction (e. g. OrderByFirstnameAscLastnameDesc).|

- Supported Query Return Types

| Return type |	Description |
|-------------|---------------|
|void|Denotes no return value.|
|Primitives|Java primitives.|
|Wrapper types|Java wrapper types.|
|T|A unique entity. Expects the query method to return one result at most. If no result is found, null is returned. More than one result triggers an IncorrectResultSizeDataAccessException.|
|Iterator\<T\>|An Iterator.|
|Collection\<T\>|A Collection.|
|List\<T\>|A List.|
|Optional\<T\>|A Java 8 or Guava Optional. Expects the query method to return one result at most. If no result is found, Optional.empty() or Optional.absent() is returned. More than one result triggers an IncorrectResultSizeDataAccessException.|
|Option\<T\>|Either a Scala or Vavr Option type. Semantically the same behavior as Java 8’s Optional, described earlier.|
|Stream\<T\>|A Java 8 Stream.|
|Streamable\<T\>|A convenience extension of Iterable that directy exposes methods to stream, map and filter results, concatenate them etc.|
|Types that implement Streamable and take a Streamable constructor or factory method argument|Types that expose a constructor or ….of(…)/….valueOf(…) factory method taking a Streamable as argument. |
|Vavr Seq, List, Map, Set|Vavr collection types. |
|Future\<T\>|A Future. Expects a method to be annotated with @Async and requires Spring’s asynchronous method execution capability to be enabled.|
|CompletableFuture\<T\>|A Java 8 CompletableFuture. Expects a method to be annotated with @Async and requires Spring’s asynchronous method execution capability to be enabled.|
|ListenableFuture|A org.springframework.util.concurrent.ListenableFuture. Expects a method to be annotated with @Async and requires Spring’s asynchronous method execution capability to be enabled.|
|Slice\<T\>|A sized chunk of data with an indication of whether there is more data available. Requires a Pageable method parameter.|
|Page\<T\>|A Slice with additional information, such as the total number of results. Requires a Pageable method parameter.|
|GeoResult\<T\>|A result entry with additional information, such as the distance to a reference location.|
|GeoResults\<T\>|A list of GeoResult<T> with additional information, such as the average distance to a reference location.|
|GeoPage\<T\>|A Page with GeoResult<T>, such as the average distance to a reference location.|
|Mono\<T\>|A Project Reactor Mono emitting zero or one element using reactive repositories. Expects the query method to return one result at most. If no result is found, Mono.empty() is returned. More than one result triggers an IncorrectResultSizeDataAccessException.|
|Flux\<T\>|A Project Reactor Flux emitting zero, one, or many elements using reactive repositories. Queries returning Flux can emit also an infinite number of elements.|
|Single\<T\>|A RxJava Single emitting a single element using reactive repositories. Expects the query method to return one result at most. If no result is found, Mono.empty() is returned. More than one result triggers an IncorrectResultSizeDataAccessException.|
|Maybe\<T\>|A RxJava Maybe emitting zero or one element using reactive repositories. Expects the query method to return one result at most. If no result is found, Mono.empty() is returned. More than one result triggers an IncorrectResultSizeDataAccessException.|
|Flowable\<T\>|A RxJava Flowable emitting zero, one, or many elements using reactive repositories. Queries returning Flowable can emit also an infinite number of elements.|
   
