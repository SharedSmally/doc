# [Spring Data Project](https://projects.spring.io/spring-data/)
## Main Concept:
- Entity: Data 
- Service/REST: Use Repository to access Entities (May use Template to interact with the Server)
- Repository: Interface to handling the Entities in the data storage (Normally via *Template to interact with the server)
- Template: Use Connetion (via ConnectionFactory) to provide Client Connection to the Server
- Connection: Client Connection Implementation to connect the Server.

## Main modules
- [Spring Data Commons](https://docs.spring.io/spring-data/commons/docs/current/reference/html/) - Core Spring concepts underpinning every Spring Data project. Define basic operations for Repositories.
     - Repository<T, ID extends Serializable>
     - CrudRepository<T, ID extends Serializable>
     - PagingAndSortingRepository<T, ID extends Serializable>     
- Spring Data JDBC - JDBC-based repositories. (SQL)
- [Spring Data JPA](https://projects.spring.io/spring-data-jpa/) - Makes it easy to implement JPA-based repositories. (SQL)
- [Spring Data KeyValue](https://github.com/spring-projects/spring-data-keyvalue) - Map-based repositories and SPIs to easily build a Spring Data module for key-value stores.
- [Spring Data LDAP](https://projects.spring.io/spring-data-ldap/) - Provides Spring Data repository support for Spring LDAP.
- [Spring Data MongoDB](https://projects.spring.io/spring-data-mongodb/) - Spring based, object-document support and repositories for MongoDB. (NoSQL)
- [Spring Data Redis](https://projects.spring.io/spring-data-redis/) - Provides easy configuration and access to Redis from Spring applications. (NoSQL)
- [Spring Data REST](https://projects.spring.io/spring-data-rest/) - Exports Spring Data repositories as hypermedia-driven RESTful resources.
- [Spring Data Gemfire](https://projects.spring.io/spring-data-gemfire/) - Provides easy configuration and access to GemFire from Spring applications.
- [Spring Data for Apache Cassandra](https://projects.spring.io/spring-data-cassandra/) - Spring Data module for Apache Cassandra.
- [Spring Data for Apache Solr](https://projects.spring.io/spring-data-solr/) - Spring Data module for Apache Solr.

## Community modules
- Spring Data Aerospike - Spring Data module for Aerospike.
- Spring Data ArangoDB - Spring Data module for ArangoDB.
- Spring Data Couchbase - Spring Data module for Couchbase.
- Spring Data DynamoDB - Spring Data module for DynamoDB.
- Spring Data Elasticsearch - Spring Data module for Elasticsearch.
- Spring Data Hazelcast - Provides Spring Data repository support for Hazelcast.
- Spring Data Jest - Spring Data for Elasticsearch based on the Jest REST client.
- Spring Data Neo4j - Spring based, object-graph support and repositories for Neo4j.
- Spring Data Vault - Vault repositories built on top of Spring Data KeyValue.

#
