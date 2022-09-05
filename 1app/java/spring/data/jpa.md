# Spring Data JPA
- [Reference](https://docs.spring.io/spring-data/data-jpa/docs/current/reference/html/)
- [javadoc API](https://docs.spring.io/spring-data/jpa/docs/current/api/)

## Repository
- Repository
```
public interface Repository<T,ID>
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
- JpaRepository<T,ID>
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
