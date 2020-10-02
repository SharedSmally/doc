# Boot Data:
- Data [Application Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#data-properties)
- SQL    
    - Data Access
    - SQL Drivers
    - Migration: [Application Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#transaction-properties)
- NoSQL
- Transaction: [Application Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#transaction-properties)

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
- Data JDBC: use [JdbcTemplate](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/jdbc/core/JdbcTemplate.html) to execute SQL statement directly on Java Object.
    - [Setup JdbcTemplate with/without Spring Boot](https://www.sivalabs.in/2016/03/springboot-working-with-jdbctemplate/)
```
  @Autowired
  JdbcTemplate jdbcTemplate;
  
    jdbcTemplate.execute("DROP TABLE customers IF EXISTS");
    jdbcTemplate.execute("CREATE TABLE customers(id SERIAL, first_name VARCHAR(255), last_name VARCHAR(255))");
    // Uses JdbcTemplate's batchUpdate operation to bulk load data
    jdbcTemplate.batchUpdate("INSERT INTO customers(first_name, last_name) VALUES (?,?)", splitUpNames);
    jdbcTemplate.query("SELECT id, first_name, last_name FROM customers WHERE first_name = ?", new Object[] { "Josh" },
        (rs, rowNum) -> new Customer(rs.getLong("id"), rs.getString("first_name"), rs.getString("last_name"))
    ).forEach(customer -> log.info(customer.toString()));
```
For [Data Source properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#data-properties):
```
spring.datasource.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/test
spring.datasource.username=root
spring.datasource.password=admin
spring.datasource.schema=create-db.sql
spring.datasource.data=seed-data.sql
```
- Data JPA
    - JPA Hibernate
- Data R2DBC
- JOOQ Access
- Database Connection Pool:
    - dbcp2
    - Hikari DataSource
    - Tomcat DataSource
    - XA DataSource

### Data Transaction
- [Transaction App Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#transaction-properties)
- atomikos
- bitronix

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
- [Application Properties](https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html#data-migration-properties)
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

