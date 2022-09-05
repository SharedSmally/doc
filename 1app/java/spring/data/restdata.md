# [Data REST](https://docs.spring.io/spring-data/rest/docs/current/reference/html/)
- [Reference]
- [javadoc API](https://docs.spring.io/spring-data/rest/docs/current/api/)

## Set up
Spring Data REST builds on top of Spring Data repositories, analyzes the application’s domain model and exposes 
hypermedia-driven HTTP resources for aggregates contained in the model.

- Dependencies
For Spring Boot project:
```
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-rest</artifactId>
  </dependency>
```
For Maven project:
```
  <dependency>
    <groupId>org.springframework.data</groupId>
    <artifactId>spring-data-rest-webmvc</artifactId>
  </dependency>
```

Spring Data REST configuration is defined in a class called **RepositoryRestMvcConfiguration**.
To customize the configuration, register a **RepositoryRestConfigurer** and implement/override the configure()methods: 

- Repository Detection Strategy
Spring Data REST uses a RepositoryDetectionStrategy to determine whether a repository is exported as a REST resource:
| Strategy | Description |
|----------|-------------|
|ALL | Considers all repositories.|
|ANNOTATED|Considers repositories that are annotated with RepositoryRestResource or RestResource and don't have the exported flag not set to false.|
|DEFAULT|Exposes public interfaces or ones explicitly annotated with RepositoryRestResource.|
|VISIBILITY|Considers the repository interface's visibility, which means only public interfaces will be exposed.|

- spring.data.rest Properties
| Property | Description |
|----------|-------------|
|basePath|the root URI for Spring Data REST: default is "/"|
|defaultPageSize|change the default for the number of items served in a single page|
|maxPageSize|change the maximum number of items in a single page|
|pageParamName|change the name of the query parameter for selecting pages|
|limitParamName|change the name of the query parameter for the number of items to show in a page|
|sortParamName|change the name of the query parameter for sorting|
|defaultMediaType|change the default media type to use when none is specified|
|returnBodyOnCreate|change whether a body should be returned when creating a new entity|
|returnBodyOnUpdate|change whether a body should be returned when updating an entity|

- HATEOS
        - links:
        - profile link:  Application-Level Profile Semantics (ALPS). 
        - Content-Type: application/hal+json or application/json

## Repository Resources
The core functionality of Spring Data REST is to export resources for Spring Data repositories.

Annotations in org.springframework.data.rest.core.annotation: 
- @RestResource
- @RepositoryRestResource
- @RepositoryEventHandler
- @Handle[Before|After][Create|Deleta|Save|LinkSave|LinkDelete]
- @Project
- @RepositoryRestController in org.springframework.data.rest.webmvc
- 



