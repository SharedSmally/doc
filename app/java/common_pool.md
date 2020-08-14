# [Apache Common Pool](https://commons.apache.org/proper/commons-pool/)

## mvn
```
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-pool2</artifactId>
    <version>2.8.1</version>
</dependency>
```
## Interfaces
- [ObjectPool<T>](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/ObjectPool.html)
```
T	borrowObject()
void	returnObject(T obj)
void	invalidateObject(T obj)
    
void	addObject()/addObjects(int count)
void	clear()/close()
int	getNumActive()/getNumIdle()
``` 

Example usage:
```
 Object obj = null;
 try {
     obj = pool.borrowObject();
     try {
         //...use the object...
     } catch(Exception e) {        
         pool.invalidateObject(obj);  // invalidate the object        
         obj = null; // do not return the object to the pool twice
     } finally {
         // make sure the object is returned to the pool
         if(null != obj) {
             pool.returnObject(obj);
        }
     }
 } catch(Exception e) {
       // failed to borrow an object
 }    
```
Implementing Classes: BaseObjectPool, GenericObjectPool, ProxiedObjectPool, SoftReferenceObjectPool
    
- [PooledObjectFactory]():

provides a generic interface for managing the lifecycle of a pooled object:
```
public interface PooledObjectFactory<T> {
void	activateObject(PooledObject<T> p);   // Reinitializes an instance to be returned by the pool.
void	destroyObject(PooledObject<T> p);    // Destroys an instance no longer needed by the pool.

PooledObject<T>	makeObject()                 // Creates an instance that can be served by the pool and wrap it in a PooledObject to be managed by the pool.
void passivateObject(PooledObject<T> p)      // Uninitializes (Reset) an instance to be returned to the idle object pool.
boolean	validateObject(PooledObject<T> p)    // Ensures that the instance is safe to be returned by the pool.
}
```
Implementing Classes: [BasePooledObjectFactory](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/BasePooledObjectFactory.html)
```
void  activateObject(PooledObject<T> p); // No-op.
void  destroyObject(PooledObject<T> p);  // No-op.
PooledObject<T>	makeObject() // Creates an instance that can be served by the pool and wrap it in a PooledObject to be managed by the pool.
void passivateObject(PooledObject<T> p); // No-op.
       // pooledObject.getObject().reset();
boolean	validateObject(PooledObject<T> p); // This implementation always returns true.
       // return pooledObject.getObject().isValid();
abstract T create()   // Creates an object instance, to be wrapped in a PooledObject:
       // return new T();
abstract PooledObject<T> wrap(T obj)  // Wrap the provided instance with an implementation of PooledObject.
       // return new DefaultPooledObject<StringBuffer>(buffer);
```
    
- KeyedPooledObjectFactory:

Defines a similar interface for KeyedObjectPools:
```
public interface KeyedPoolableObjectFactory<K,V> {
    PooledObject<V> makeObject(K key);
    void activateObject(K key, PooledObject<V> obj);
    void passivateObject(K key, PooledObject<V> obj);
    boolean validateObject(K key, PooledObject<V> obj);
    void destroyObject(K key, PooledObject<V> obj);
}
```
Implementing Classes: [BaseKeyedPooledObjectFactory](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/BaseKeyedPooledObjectFactory.html)

- [PooledObject](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/PooledObject)

Known Implementing Classes: DefaultPooledObject, PooledSoftReference

- [GenericObjectPool](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/impl/GenericObjectPool.html) / [GenericKeyedObjectPool](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/impl/GenericKeyedObjectPool.html):

provides a wide variety of configuration options, including the ability to cap the number of idle or active instances, to evict instances as they sit idle in the pool, etc. As of version 2, GenericObjectPool also provides abandoned instance tracking and removal.
```
public class GenericObjectPool<T>  extends BaseGenericObjectPool<T>
implements ObjectPool<T>, GenericObjectPoolMXBean, UsageTracking<T>

GenericObjectPool(PooledObjectFactory<T> factory)
GenericObjectPool(PooledObjectFactory<T> factory, GenericObjectPoolConfig<T> config)
GenericObjectPool(PooledObjectFactory<T> factory, GenericObjectPoolConfig<T> config, AbandonedConfig abandonedConfig)
```

```
public class GenericKeyedObjectPool<K,T>  extends BaseGenericObjectPool<T>
implements KeyedObjectPool<K,T>, GenericKeyedObjectPoolMXBean<K>

GenericKeyedObjectPool(KeyedPooledObjectFactory<K,T> factory)
GenericKeyedObjectPool(KeyedPooledObjectFactory<K,T> factory, GenericKeyedObjectPoolConfig<T> config)
```

- SoftReferenceObjectPool:

can grow as needed, but allows the garbage collector to evict idle instances from the pool as needed.
```
public class SoftReferenceObjectPool<T> extends BaseObjectPool<T>

SoftReferenceObjectPool(PooledObjectFactory<T> factory)
```
