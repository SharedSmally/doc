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
- [API Doc](https://docs.spring.io/spring-data/commons/docs/2.5.6/api/)

### Annotations in org.springframework.data.annotation:
| Annotation Type |	Description |
|-----------------|-------------|
|@CreatedBy | Declares a field as the one representing the principal that created the entity containing the field.|
|@CreatedDate | Declares a field as the one representing the date the entity containing the field was created.|
|@Id | Demarcates an identifier.|
|@LastModifiedBy  | Declares a field as the one representing the principal that recently modified the entity containing the field.|
|@LastModifiedDate |	Declares a field as the one representing the date the entity containing the field was recently modified.|
|@Version|Demarcates a property to be used as version field to implement optimistic locking on entities.|
|@Immutable |	Annotation for persistent entities to indicate the class is designed in immutable way.|
|@Transient |	Marks a field to be transient for the mapping framework.|
|@Persistent |	Annotation to generally identify persistent types, fields and parameters.|
|@AccessType |	Annotation to define how Spring Data shall access values of persistent properties.|
|@PersistenceConstructor|Constructor used for object creation|
|@QueryAnnotation |	Meta-Annotation to mark a store specific annotation as a query annotation.|
|@ReadOnlyProperty |	Marks a field to be read-only for the mapping framework and therefore will not be persisted.|
|@Reference |	Meta-annotation to be used to annotate annotations that mark references to other objects.|


### org.springframework.data.repository

#### Repository<T,ID>: with Reacive/RxJava2/RxJava3 for reactive interface
Central repository marker interface. Captures the domain type to manage as well as the domain type's id type. General purpose is to hold type information as well as being able to discover interfaces that extend this one during classpath scanning for easy Spring bean creation.

Domain repositories extending this interface can selectively expose CRUD methods by simply declaring methods of the same signature as those declared in CrudRepository.

#### CrudRepository<T,ID> extends Repository<T,ID>
Interface for generic CRUD operations on a repository for a specific type.
| Method | Description |
|--------|-------------|
|long 	count() | Returns the number of entities available.|
|void 	delete(T entity) |Deletes a given entity.|
|void 	deleteAll() |Deletes all entities managed by the repository.|
|void 	deleteAll(Iterable<? extends T> entities) |Deletes the given entities.|
|void 	deleteAllById(Iterable<? extends ID> ids) |Deletes all instances of the type T with the given IDs.|
|void 	deleteById(ID id) |Deletes the entity with the given id.|
|boolean 	existsById(ID id) |Returns whether an entity with the given id exists.|
|Iterable<T> 	findAll() |Returns all instances of the type.|
|Iterable<T> 	findAllById(Iterable<ID> ids) |Returns all instances of the type T with the given IDs.|
|Optional<T> 	findById(ID id) |Retrieves an entity by its id.|
|<S extends T> S	save(S entity) |Saves a given entity.|
|<S extends T> Iterable<S> saveAll(Iterable<S> entities) | Saves all given entities.|


#### PagingAndSortingRepository<T,ID> 	
Extension of CrudRepository to provide additional methods to retrieve entities using the pagination and sorting abstraction.
| Method | Description |
|--------|-------------|
|Page<T> 	findAll(Pageable pageable) | Returns a Page of entities meeting the paging restriction provided in the Pageable object.|
|Iterable<T> 	findAll(Sort sort) | Returns all entities sorted by the given options.|

#### Interface Pageable
| Method | Description |
|--------|-------------|
|static Pageable 	ofSize(int pageSize) | Creates a new Pageable for the first page (page number 0) given pageSize .|
|static Pageable 	unpaged()| Returns a Pageable instance representing no pagination setup.|
|Pageable 	first() |Returns the Pageable requesting the first page.|
|Pageable 	next() |Returns the Pageable requesting the next Page.|
|Pageable 	previousOrFirst() |Returns the previous Pageable or the first Pageable if the current one already is the first one.|
|Pageable 	withPage(int pageNumber) |Creates a new Pageable with pageNumber applied.|
|long 	getOffset() |Returns the offset to be taken according to the underlying page and page size.|
|int 	getPageNumber()| Returns the page to be returned.|
|int 	getPageSize()| Returns the number of items to be returned.|
|Sort 	getSort()| Returns the sorting parameters.|
|Sort 	getSortOr(Sort sort) |Returns the current Sort or the given one if the current one is unsorted.|
|boolean 	hasPrevious()| Returns whether there's a previous Pageable we can access from the current one.|
|boolean 	isPaged() |Returns whether the current Pageable contains pagination information.|
|boolean 	isUnpaged()| Returns whether the current Pageable does not contain pagination information.|
|Optional<Pageable> 	toOptional() |Returns an Optional so that it can easily be mapped on.|

#### Interface Page<T>
Superinterfaces: Iterable<T>, Slice<T>, Streamable<T>, Supplier<Stream<T>>
| Method | Description |
|--------|-------------|
|static <T> Page<T> 	empty() | Creates a new empty Page.|
|static <T> Page<T> 	empty(Pageable pageable) |Creates a new empty Page for the given Pageable.|
|long 	getTotalElements() |Returns the total amount of elements.|
|int 	getTotalPages() | Returns the number of total pages.|
|<U> Page<U> 	map(Function<? super T,? extends U> converter) | Returns a new Page with the content of the current one mapped by the given Function.|

## Sample 
- Define Repository interface with Query Methods: from Repository, CrudRepository, or PagingAndSortingRepository
```
@Repository
interface UserRepository extends CrudRepository<User, Long> {
  long deleteByLastname(String lastname);
  List<User> removeByLastname(String lastname);
}
```
- Set up Spring to create proxy instances for those interfaces,
```
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
@EnableJpaRepositories
class RepositoryConfig { … }
```
- Inject the repository instance and use it, 
```
class SomeClient {
  private final PersonRepository repository;

  SomeClient(PersonRepository repository) {
    this.repository = repository;
  }

  void doSomething() {
    List<Person> persons = repository.findByLastname("Matthews");
  }
}
```
- To distinguish the repository for different data module, use either module-specific repositories (such as @JpaRepository) or module-specific annotations(@Entity for JPA and @Document for MongoDB and Elasticsearch) in the domain classes, or use scoping repository base packages:
```
@EnableJpaRepositories(basePackages = "com.acme.repositories.jpa")
@EnableMongoRepositories(basePackages = "com.acme.repositories.mongo")
class Configuration { … }
```

## Defining Query Methods
The repository proxy has two ways to derive a store-specific query from the method name:
- By deriving the query from the method name directly.
- By using a manually defined query.

