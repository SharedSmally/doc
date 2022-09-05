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
   
