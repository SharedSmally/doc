# REDIS [https://redis.io/]

## Features
- key-value NoSQL and memory based (faster, for small amount of data; dump to file as [RDB](https://github.com/sripathikrishnan/redis-rdb-tools/wiki/Redis-RDB-Dump-File-Format) )

## [Documents](https://redis.io/documentation)
### [Full Commands](https://redis.io/commands)
### [CLI Commands](https://redis.io/topics/rediscli):
 - [tutorial](https://www.tutorialspoint.com/redis/redis_environment.htm) 
 - Sample Commands
     - redis-cli [-a xxxx] [-h redis15.localnet.org] [-p 6390] ping
     - redis-cli ping
     - redis-cli CONFIG GET loglevel
     - redis-cli CONFIG GET *config-name*
     - redis-cli CONFIG SET *config-name* *config-value*
     - redis-cli SET *name* *value*
     - redis-cli GET *name* // string: maxlen=512
     - redis-cli HMSET *key:value key value * / HGETALL *key:value*   // Hashes
     - redis-cli LPUSH *key value* / LRANGE *lower upper*   // List
     - redis-cli SADD *key value* / SMEMBERS *key*   // Set
     - redis-cli ZADD *key value* / ZRANGEBYSCOPE *key lower upper*   // Sorted Set
     - redis-cli DEL *key value* / SMEMBERS *key*   // Set
 - [Server Commands](https://www.tutorialspoint.com/redis/redis_server.htm): redis-server
 - [Client Connect Commands](https://www.tutorialspoint.com/redis/redis_client_connection.htm)
 - [Connect Commands](https://www.tutorialspoint.com/redis/redis_connection.htm): 
 - [Key Commands](https://www.tutorialspoint.com/redis/redis_keys.htm)
 - [String Commands](https://www.tutorialspoint.com/redis/redis_strings.htm)
 - [Hash Commands](https://www.tutorialspoint.com/redis/redis_hashes.htm)
 - [List Commands](https://www.tutorialspoint.com/redis/redis_lists.htm)
 - [Set Commands](https://www.tutorialspoint.com/redis/redis_sets.htm)
 - [Sorted Set Commands](https://www.tutorialspoint.com/redis/redis_sorted_sets.htm)
 - [PubSub Commands](https://www.tutorialspoint.com/redis/redis_pub_sub.htm)
 - [Script Commands](https://www.tutorialspoint.com/redis/redis_scripting.htm)

### [Java - redis] (https://www.tutorialspoint.com/redis/redis_java.htm)
 - [redis basic types](https://www.tutorialspoint.com/redis/redis_quick_guide.htm)
      - string
      - Hash
      - List
      - Set
      - Sorted Set
 
 - [Spring ](https://projects.spring.io/spring-data-redis/) supports REDIS-Client Impl
      - Jedis
      - Lettuce
      
 - [Dependencies](https://dzone.com/articles/intro-to-redis-with-spring-boot)
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```
 - Config: Use RedosTemplate to Connect to server
```
@Bean
JedisConnectionFactory jedisConnectionFactory() {
    return new JedisConnectionFactory();
}
@Bean
public RedisTemplate<String, Object> redisTemplate() {
    final RedisTemplate<String, Object> template = new RedisTemplate<String, Object>();
    template.setConnectionFactory(jedisConnectionFactory());
    template.setValueSerializer(new GenericToStringSerializer<Object>(Object.class));
    return template;
}
@Bean
MessagePublisher redisPublisher() {
    return new MessagePublisherImpl(redisTemplate(), topic());
}
@Bean
MessageListenerAdapter messageListener() {
    return new MessageListenerAdapter(new MessageSubscriber());
}
```
- Repository: Provides Data process interfaces (Impl uses RedisTemplate to interact with Server)
```
public Movie {
   private String id;
   private String name;
   //standard getters and setters
}

public interface RedisRepository {
    Map<Object, Object> findAllMovies();
    void add(Movie movie);
    void delete(String id);
    Movie findMovie(String id);
}

// Use Template to access data
@Repository
public class RedisRepositoryImpl implements RedisRepository {
    private static final String KEY = "Movie";
    private RedisTemplate<String, Object> redisTemplate;
    private HashOperations hashOperations;
    @Autowired
    public RedisRepositoryImpl(RedisTemplate<String, Object> redisTemplate){
        this.redisTemplate = redisTemplate;
    }
    @PostConstruct
    private void init(){
        hashOperations = redisTemplate.opsForHash();
    }
    public void add(final Movie movie) {
        hashOperations.put(KEY, movie.getId(), movie.getName());
    }
    public void delete(final String id) {
        hashOperations.delete(KEY, id);
    }
    public Movie findMovie(final String id){
        return (Movie) hashOperations.get(KEY, id);
    }
    public Map<Object, Object> findAllMovies(){
        return hashOperations.entries(KEY);
    }
}
```
   - Service: Use Repository to access data in Redis or RedisTemplate to interact with Server directly.
```
public interface MessagePublisher {
    void publish(final String message);
}
@Service
public class MessagePublisherImpl implements MessagePublisher {
    @Autowired
    private RedisTemplate<String, Object> redisTemplate;
    @Autowired
    private ChannelTopic topic;
    public MessagePublisherImpl() {
    }
    public MessagePublisherImpl(final RedisTemplate<String, Object> redisTemplate, final ChannelTopic topic) {
        this.redisTemplate = redisTemplate;
        this.topic = topic;
    }
    public void publish(final String message) {
        redisTemplate.convertAndSend(topic.getTopic(), message);
    }
}

@Service
public class MessageSubscriber implements MessageListener {
    public static List<String> messageList = new ArrayList<String>();
    public void onMessage(final Message message, final byte[] pattern) {
        messageList.add(message.toString());
        System.out.println("Message received: " + new String(message.getBody()));
    }
}
```

  - Web Service: Use Repository or Service
```
```
### Config
- Config file:  redis.conf:   redis-server *config*     
- docker: 
```
FROM redis
COPY redis.conf /usr/local/etc/redis/redis.conf
CMD [ "redis-server", "/usr/local/etc/redis/redis.conf" ]
```
  - access:
  - password:
