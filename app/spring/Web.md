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
  ### Controller
|  Annotation Type | 	Description |
|------------------|-----------------|
|ControllerAdvice 	|Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @Controller classes.|
|RestController 	|A convenience annotation that is itself annotated with @Controller and @ResponseBody.|
|RestControllerAdvice 	|A convenience annotation that is itself annotated with @ControllerAdvice and @ResponseBody.|

### Mapping
|  Annotation Type | 	Description |
|------------------|-----------------|
|Mapping 	|Meta annotation that indicates a web mapping annotation.|
|GetMapping 	|Annotation for mapping HTTP GET requests onto specific handler methods.|
|PostMapping 	|Annotation for mapping HTTP POST requests onto specific handler methods.|
|PutMapping 	|Annotation for mapping HTTP PUT requests onto specific handler methods.|
|PatchMapping 	|Annotation for mapping HTTP PATCH requests onto specific handler methods.|
|DeleteMapping 	|Annotation for mapping HTTP DELETE requests onto specific handler methods.|
|RequestMapping 	|Annotation for mapping web requests onto methods in request-handling classes with flexible method signatures.|
|ExceptionHandler 	|Annotation for handling exceptions in specific handler classes and/or handler methods.|

### Binding
|  Annotation Type | 	Description |
|------------------|-----------------|
|CookieValue 	|Annotation to indicate that a method parameter is bound to an HTTP cookie.|
|CrossOrigin 	|Annotation for permitting cross-origin requests on specific handler classes and/or handler methods.|
|InitBinder 	|Annotation that identifies methods which initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.|

### Request
|  Annotation Type | 	Description |
|------------------|-----------------|
|MatrixVariable 	|Annotation which indicates that a method parameter should be bound to a name-value pair within a path segment.|
|PathVariable 	|Annotation which indicates that a method parameter should be bound to a URI template variable.|
|RequestParam 	|Annotation which indicates that a method parameter should be bound to a web request parameter.|
|RequestBody 	|Annotation indicating a method parameter should be bound to the body of the web request.|
|RequestHeader |Annotation which indicates that a method parameter should be bound to a web request header.|

## Response
|  Annotation Type | 	Description |
|------------------|-----------------|
|ResponseBody 	|Annotation that indicates a method return value should be bound to the web response body.|
|ResponseStatus |Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.|

## Attribute
|  Annotation Type | 	Description |
|------------------|-----------------|
|ModelAttribute 	|Annotation that binds a method parameter or method return value to a named model attribute, exposed to a web view.|
|RequestAttribute 	|Annotation to bind a method parameter to a request attribute.|
|SessionAttribute 	|Annotation to bind a method parameter to a session attribute.|
|SessionAttributes 	|Annotation that indicates the session attributes that a specific handler uses.|

  ## Web Security
  
  ## Sample
```
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class GreetingController {
  @GetMapping("/greeting")
  public String greetingForm(Model model) {
    model.addAttribute("greeting", new Greeting());
    return "greeting";
  }

  @PostMapping("/greeting")
  public String greetingSubmit(@ModelAttribute Greeting greeting, Model model) {
    model.addAttribute("greeting", greeting);
    return "result";
  }
}
```
Model will be passed to the view: the template.html file.
```
<!DOCTYPE HTML>
<html xmlns:th="https://www.thymeleaf.org">
<head> 
    <title>Getting Started: Handling Form Submission</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
</head>
<body>
	<h1>Form</h1>
    <form action="#" th:action="@{/greeting}" th:object="${greeting}" method="post">
    	<p>Id: <input type="text" th:field="*{id}" /></p>
        <p>Message: <input type="text" th:field="*{content}" /></p>
        <p><input type="submit" value="Submit" /> <input type="reset" value="Reset" /></p>
    </form>
</body>
</html>
```
  
