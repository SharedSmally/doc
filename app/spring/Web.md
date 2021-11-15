# Spring Web 
- Web Service
- REST Web Service
- WebSocket

## Web Application Layout
- com.cainet.xxx.web
     - WebApp.java: @ComponentScan will scan @Component, including @Repository,@Service,@Controller,@RestController for the given packages, and create @Bean for each class, default is for local and sub-packages
     - com.cainet.xxx.web.config
         - XxxConfig.java: @Configuration with @Bean
     - com.cainet.xxx.web.model
         - XxxPOJO.java (@Entity)
     - com.cainet.xxx.web.repository
         - XxxRepository.java: For Data access for model(one) 
     - com.cainet.xxx.web.service
         - XxxService.java: use Repository to access data 
     - com.cainet.xxx.web.controller
         - XxxController.java: use @AutoWired services 
         - @Controller: return xxx.html template file
  - src/main/application.properties
  - src/main/static: static files
  - src/main/templates/: template files (return string from mapping method is mapped to xxx.html in templates/ or static/)
  - src/main/webapp/WEB-INF: dynamic generated files
  
  ## Component Annotations
  - @Configuration
  - @Bean
  - @Component
  - @Repository
  - @Service
  - @Controller
  - @RestController
  - @AutoWired
  - @ComponentScan
  - @EnableAutoConfig
  - @SpringBootApplication
  

  ## [Web Controller Annotations](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/package-summary.html)
  - @Controller
  - @RestController
  - @
  
|  Annotation Type | 	Description |
|------------------|-----------------|
|ControllerAdvice 	|Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @Controller classes.|
|RestController 	|A convenience annotation that is itself annotated with @Controller and @ResponseBody.|
|RestControllerAdvice 	|A convenience annotation that is itself annotated with @ControllerAdvice and @ResponseBody.|

|Mapping 	|Meta annotation that indicates a web mapping annotation.|
|GetMapping 	|Annotation for mapping HTTP GET requests onto specific handler methods.|
|PostMapping 	|Annotation for mapping HTTP POST requests onto specific handler methods.|
|PutMapping 	|Annotation for mapping HTTP PUT requests onto specific handler methods.|
|PatchMapping 	|Annotation for mapping HTTP PATCH requests onto specific handler methods.|
|DeleteMapping 	|Annotation for mapping HTTP DELETE requests onto specific handler methods.|
|RequestMapping 	|Annotation for mapping web requests onto methods in request-handling classes with flexible method signatures.|
|ExceptionHandler 	|Annotation for handling exceptions in specific handler classes and/or handler methods.|

|CookieValue 	|Annotation to indicate that a method parameter is bound to an HTTP cookie.|
|CrossOrigin 	|Annotation for permitting cross-origin requests on specific handler classes and/or handler methods.|
|InitBinder 	|Annotation that identifies methods which initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.|
|ModelAttribute 	|Annotation that binds a method parameter or method return value to a named model attribute, exposed to a web view.|
|MatrixVariable 	|Annotation which indicates that a method parameter should be bound to a name-value pair within a path segment.|
|PathVariable 	|Annotation which indicates that a method parameter should be bound to a URI template variable.|
|RequestAttribute 	|Annotation to bind a method parameter to a request attribute.|
|RequestBody 	|Annotation indicating a method parameter should be bound to the body of the web request.|
|RequestHeader |Annotation which indicates that a method parameter should be bound to a web request header.|
|RequestParam 	|Annotation which indicates that a method parameter should be bound to a web request parameter.|
|ResponseBody 	|Annotation that indicates a method return value should be bound to the web response body.|
|ResponseStatus |Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.|
|SessionAttribute 	|Annotation to bind a method parameter to a session attribute.|
|SessionAttributes 	|Annotation that indicates the session attributes that a specific handler uses.|

  ## Web Security
  
