# [Spring Data Project](https://projects.spring.io/spring-data/)
## Main Concept:
- Entity: Data 
- Service/REST: Use Repository to access Entities (May use Template to interact with the Server)
- Repository: Interface to handling the Entities in the data storage (Normally via *Template to interact with the server)
- Template: Use Connetion (via ConnectionFactory) to provide Client Connection to the Server
- Connection: Client Connection Implementation to connect the Server.

## Main modules
- Spring Data Commons - Core Spring concepts underpinning every Spring Data project.
- Spring Data JPA - Makes it easy to implement JPA-based repositories. (SQL)
- Spring Data JDBC - JDBC-based repositories. (SQL)
- Spring Data KeyValue - Map-based repositories and SPIs to easily build a Spring Data module for key-value stores.
- Spring Data LDAP - Provides Spring Data repository support for Spring LDAP.
- Spring Data MongoDB - Spring based, object-document support and repositories for MongoDB. (NoSQL)
- Spring Data Redis - Provides easy configuration and access to Redis from Spring applications. (NoSQL)
- Spring Data Gemfire - Provides easy configuration and access to GemFire from Spring applications.
- Spring Data REST - Exports Spring Data repositories as hypermedia-driven RESTful resources.
- Spring Data for Apache Cassandra - Spring Data module for Apache Cassandra.
- Spring Data for Apache Solr - Spring Data module for Apache Solr.

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
