# redis

## Java Clients
- jedis (simple, lack features like thread safety, transparent reconnection handling and an asynchronous API)
- lettuce
- Redisson

## jedis Documents
- [jedis git](https://github.com/xetorthio/jedis)
- [Java Doc](https://javadoc.io/doc/redis.clients/jedis/latest/overview-summary.html)
- [jedis Wiki](https://github.com/xetorthio/jedis/wiki)
- [Tutorial](https://www.baeldung.com/jedis-java-redis-client-library)

## jedis Samples
### Maven
```
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
    <version>3.3.0</version>
</dependency>
```
### Data Structures
- String
```
jedis.set("events/city/rome", "32,15,223,828");
String cachedResponse = jedis.get("events/city/rome");
```
- List
```
jedis.lpush("queue#tasks", "firstTask");
jedis.lpush("queue#tasks", "secondTask");
String task = jedis.rpop("queue#tasks");
```
- Set
```
jedis.sadd("nicknames", "nickname#1");
jedis.sadd("nicknames", "nickname#2");
jedis.sadd("nicknames", "nickname#1");
Set<String> nicknames = jedis.smembers("nicknames");
boolean exists = jedis.sismember("nicknames", "nickname#1");
```
- Sorted Set
```
Map<String, Double> scores = new HashMap<>();
scores.put("PlayerOne", 3000.0);
scores.put("PlayerTwo", 1500.0);
scores.put("PlayerThree", 8200.0);
 
scores.entrySet().forEach(playerScore -> {
    jedis.zadd(key, playerScore.getValue(), playerScore.getKey());
});
		
String player = jedis.zrevrange("ranking", 0, 1).iterator().next();
long rank = jedis.zrevrank("ranking", "PlayerOne");
```
- Hash
```
jedis.hset("user#1", "name", "Peter");
jedis.hset("user#1", "job", "politician");
String name = jedis.hget("user#1", "name");
Map<String, String> fields = jedis.hgetAll("user#1");
String job = fields.get("job");
```

### Advanced Features
- Transactions:  guarantee atomicity and thread safety operations
```
```
- Pool

- Cluster
