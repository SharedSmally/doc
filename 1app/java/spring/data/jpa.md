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
   
