# Boot Data
- SQL
    - Data Access
    - SQL Driver
    - Migration
- NoSQL

## SQL
- [ Tutorial ](https://spring.io/guides/gs/relational-data-access/)
```
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>
	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>2.3.2.RELEASE</version>
		<relativePath/>
	</parent>
	<groupId>com.example</groupId>
	<artifactId>relational-data-access</artifactId>
	<version>0.0.1-SNAPSHOT</version>
	<name>relational-data-access</name>
	<description>Demo project for Spring Boot</description>

	<properties>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-data-jdbc</artifactId>
		</dependency>
		<dependency>
			<groupId>com.h2database</groupId>
			<artifactId>h2</artifactId>
			<scope>runtime</scope>
		</dependency>
    
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
			<exclusions>
				<exclusion>
					<groupId>org.junit.vintage</groupId>
					<artifactId>junit-vintage-engine</artifactId>
				</exclusion>
			</exclusions>
		</dependency>
	</dependencies>

	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>
</project>
```
### Data Access
- Data JDBC
- Data JPA
- Data R2DBC
- JOOQ Access

### SQL Drivers
#### Embedded DB
- MyBatis
- H2
- Derby
- HyperSQL
#### SQL Driver
- IBM DB2
- MySQL
- MS SQL
- Oracle
- PostgreSQL
### Data Migration
- Liquidbase
- Flyway

## NoSQL
- Redis / Reactive Redis
- MongDB / Reactive MongoDB
- Cassandra / Reactive Cassandra
- Couchbase/ Reactive Couchbase
- ElasticSearch
- Apache Geode
- Apache Solr
- Neo4j

