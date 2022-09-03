# Spring Boot for Data

# [Data](https://docs.spring.io/spring-boot/docs/current/reference/html/data.html)

## SQL

### Embedded Database 
- h2
- HSQL
- Derby 
- 
### Data Source
Properties: *spring.datasource.\**: url,username,password,driver-class-name
Fine Tunning for connection pool: *spring.datasource.hikari.\*, spring.datasource.tomcat.\*, spring.datasource.dbcp2.\*, and spring.datasource.oracleucp.\**

### Using JdbcTemplate
Auto-configure *JdbcTemplate* and *NamedParameterJdbcTemplate* with *spring.jdbc.template.\**, can @Autowire them directly into the beans:
```
@Component
public class MyBean {
    private final JdbcTemplate jdbcTemplate;
    public MyBean(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
    public void doSomething() {
        this.jdbcTemplate ...
    }
}
```
### JPA and Spring Data JPA


## NOSQL


