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
- [PooledObjectFactory]():

provides a generic interface for managing the lifecycle of a pooled object:
```
public interface PooledObjectFactory<T> {
    PooledObject<T> makeObject();
    void activateObject(PooledObject<T> obj);
    void passivateObject(PooledObject<T> obj);
    boolean validateObject(PooledObject<T> obj);
    void destroyObject(PooledObject<T> obj);
}
```
Implementing Classes: [BasePooledObjectFactory](https://commons.apache.org/proper/commons-pool/apidocs/org/apache/commons/pool2/BasePooledObjectFactory.html)

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
