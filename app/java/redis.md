# redis

## Java Clients
- jedis (simple, lack features like thread safety, transparent reconnection handling and an asynchronous API)
- lettuce (Middle)
- Redisson (many advanced features, such as distributed objects, locks, ...). See [Redisson vs Lettus](https://redisson.org/feature-comparison-redisson-vs-lettuce.html) and [Reddisson vs jedis](https://redisson.org/feature-comparison-redisson-vs-jedis.html)

## jedis Documents
- [jedis git](https://github.com/xetorthio/jedis)
- [Java Doc](https://javadoc.io/doc/redis.clients/jedis/latest/overview-summary.html)
- [jedis Wiki](https://github.com/xetorthio/jedis/wiki)
- [Tutorial](https://www.baeldung.com/jedis-java-redis-client-library)

## jedis [Samples](https://www.baeldung.com/jedis-java-redis-client-library)
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
String friendsPrefix = "friends#";
String userOneId = "4352523";
String userTwoId = "5552321";
 
Transaction t = jedis.multi();
t.sadd(friendsPrefix + userOneId, userTwoId);
t.sadd(friendsPrefix + userTwoId, userOneId);
t.exec();
```

- Pipelining
Pack multiple commands together in one request and save connection overhead. The operations should be mutually independent:
```
String userOneId = "4352523";
String userTwoId = "4849888";
 
Pipeline p = jedis.pipelined();
p.sadd("searched#" + userOneId, "paris");
p.zadd("ranking", 126, userOneId);
p.zadd("ranking", 325, userTwoId);
Response<Boolean> pipeExists = p.sismember("searched#" + userOneId, "paris");
Response<Set<String>> pipeRanking = p.zrange("ranking", 0, -1);
p.sync();
 
String exists = pipeExists.get();
Set<String> ranking = pipeRanking.get();
```

- Publish/Subscribe
Use the Redis messaging broker functionality to send messages between the different components. Make sure the subscriber and publisher threads do not share the same Jedis connection.

Subscriber subscribes and listen to messages sent to a channel:
```
Jedis jSubscriber = new Jedis();
jSubscriber.subscribe(new JedisPubSub() {
    @Override
    public void onMessage(String channel, String message) {
        // handle message
    }
}, "channel");
```
Subscribe is a blocking method, you will need to unsubscribe from the JedisPubSub explicitly.

Publisher simply send messages to that same channel from the publisher's thread:
```
Jedis jPublisher = new Jedis();
jPublisher.publish("channel", "test message");
```

- Pool

Not use a single instance in a multi-threaded environment as a single instance is not thread-safe. Create a pool of connections to Redis for us to reuse on demand, a pool that is thread safe and reliable as long as you return the resource to the pool when you are done with it:

```
final JedisPoolConfig poolConfig = buildPoolConfig();
JedisPool jedisPool = new JedisPool(poolConfig, "localhost");
 
private JedisPoolConfig buildPoolConfig() {
    final JedisPoolConfig poolConfig = new JedisPoolConfig();
    poolConfig.setMaxTotal(128);
    poolConfig.setMaxIdle(128);
    poolConfig.setMinIdle(16);
    poolConfig.setTestOnBorrow(true);
    poolConfig.setTestOnReturn(true);
    poolConfig.setTestWhileIdle(true);
    poolConfig.setMinEvictableIdleTimeMillis(Duration.ofSeconds(60).toMillis());
    poolConfig.setTimeBetweenEvictionRunsMillis(Duration.ofSeconds(30).toMillis());
    poolConfig.setNumTestsPerEvictionRun(3);
    poolConfig.setBlockWhenExhausted(true);
    return poolConfig;
}
```

The pool instance is thread safe, it can be stored statically but should take care of destroying the pool to avoid leaks when the application is being shutdown.

Can make use of our pool from anywhere in the application when needed:

```
try (Jedis jedis = jedisPool.getResource()) {
    // do operations with jedis resource
}
```

Use the Java try-with-resources statement to avoid having to manually close the Jedis resource, but if cannot use this statement,  an also close the resource manually in the finally clause.

- Cluster
Only need to provide the host and port details from one of the master instances, it will auto-discover the rest of the instances in the cluster.
```
try (JedisCluster jedisCluster = new JedisCluster(new HostAndPort("localhost", 6379))) {
    // use the jedisCluster resource as if it was a normal Jedis resource
} catch (IOException e) {}
```

When using Redis Cluster you cannot perform transactions nor use pipelines, two important features on which many applications rely for ensuring data integrity.

Transactions are disabled because, in a clustered environment, keys will be persisted across multiple instances. Operation atomicity and thread safety cannot be guaranteed for operations that involve command execution in different instances.


- More Samples
```
public static void main(String[] args) throws InterruptedException {
        final JedisPool pool = new JedisPool();
        final JedisPubSub listener = new JedisPubSub() {
            @Override
            public void onMessage(String channel, String message) {
                super.onMessage(channel, message);
            }

            @Override
            public void onSubscribe(String channel, int subscribedChannels) {
                super.onSubscribe(channel, subscribedChannels);
            }
        };

        ExecutorService service = Executors.newFixedThreadPool(1);
        for (int i = 0; i <10 ; i++) {
            service.execute(new Runnable() {
                @Override
                public void run() {
                    Jedis jedis = pool.getResource();
                    try  {
                        System.out.println("Subscribed");
                        jedis.subscribe(listener, "TEST");
                    } finally{
                        System.out.println("Something happened thread will die");
                        jedis.close();
                    }
                }
            });
        }
    }
```
Reconnection
```
	private void open(final String... channels){
		Runnable run = new Runnable(){
			String[] subs = channels;
			@Override
			public void run() {
				/ / If the connection is abnormal, release the current connection object and re-apply for connection
				for(;;){/** Infinite loop, the thread is automatically closed at the end of the JVM */
					try{
						// Get the Jedis instance execution channel subscription
						getJedis().subscribe(jedisPubSub,subs);
						break;
					} catch (JedisConnectionException e) {
						// release the current connection and try again
						releaseJedis();
						logger.error("Subscribing failed. {}", e.getMessage());
						// Try again after the delay
						try {
							Thread.sleep(RECONNECT_DELAY_MILLS);
						} catch (InterruptedException e1) {
						}
						// Get all registered channels from channelSubs and re-register
						subs = channelSubs.keySet().toArray(new String[0]);
					}catch (Exception e) {
						logger.error("Subscribing failed.", e);
					}
				}
			}};
		// subscribeExecutor is a thread pool that automatically closes when the JVM ends
		subscribeExecutor.execute(run);
	}
```
```
import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPubSub;
public class KVStoreSubClient extends Thread{
    private Jedis jedis;
    private String channel;
    private JedisPubSub listener;
    public KVStoreSubClient(String host,int port, String password){
        jedis = new Jedis(host,port);
        String authString = jedis.auth(password); //password
        if (! authString.equals("OK"))
                {
                    System.err.println("AUTH Failed: " + authString);
                    return;
                }
    }
    public void setChannelAndListener(JedisPubSub listener,String channel){
        this.listener=listener;
        this.channel=channel;
    }
    private void subscribe(){
        if(listener==null || channel==null){
            System.err.println("Error:SubClient> listener or channel is null");
        }
        jedis.subscribe(listener, channel);
    }
    public void unsubscribe(String channel){
        listener.unsubscribe(channel);
    }
    @Override
    public void run() {
        try{
            subscribe();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}```

```
JedisPool pool = new JedisPool(...);
try {
    Jedis jedis = pool.getResource();
    // Is connected
} catch (JedisConnectionException e) {
    // Not connected
}
```
