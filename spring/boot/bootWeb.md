
# Web

Samples
```
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.web.bind.annotation.*;

@RestController
@SpringBootApplication
public class Example {
	@RequestMapping("/")
	String home() {
		return "Hello World!";
	}

	public static void main(String[] args) {
		SpringApplication.run(Example.class, args);
	}
}
```

## Request parameter vs attribute

Request parameters are the result of submitting an HTTP request with a query string that specifies the name/value pairs, or of submitting an HTML form that specifies the name/value pairs. The name and the values are always strings, and can be automatically retrieved by using request.getParameter(). 

Request attributes (request-scoped variables) are objects of any type that are explicitly placed on the request object via a call to the setAttribute() method. They are retrieved via the getAttribute(). Attributes are objects, not just a string, and can be placed in the request, session, or context objects. They can be set programaticly and retrieve them later.

## Web Annotations
- [API doc](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/package-summary.html)
- [@RestController](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RestController.html)/TYPE: @Controller(class) + @ResponseBody(method)

### Web Mapping
- [@Mapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/Mapping.html): Meta annotation that indicates a web mapping annotation.
- [@RequestMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestMapping.html)(method): Annotation for mapping web requests onto methods in request-handling classes with flexible method signatures. HTTP method specific variants: @GetMapping, @PostMapping, @PutMapping, @DeleteMapping, or @PatchMapping.
- [@GetMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/GetMapping.html)/METHOD:Annotation for mapping HTTP GET requests onto specific handler methods.
- [@PostMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/PostMapping.html)//METHOD: Annotation for mapping HTTP POST requests onto specific handler methods.
- [@PutMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/PutMapping.html)//METHOD: Annotation for mapping HTTP PUT requests onto specific handler methods.
- [@DeleteMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/DeleteMapping.html)/METHOD: Annotation for mapping HTTP DELETE requests onto specific handler methods.
- [@PatchMapping](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/PatchMapping.html)/METHOD: Annotation for mapping HTTP PATCH requests onto specific handler methods.
- [@CrossOrigin](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/CrossOrigin.html)/TYPE,METHOD: Annotation for permitting cross-origin requests on specific handler classes and/or handler methods.

### Web method parameter
- [@PathVariable](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/PathVariable.html)/PARAMETER: Annotation which indicates that a method parameter should be bound to a URI template variable.
- [@MatrixVariable](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/MatrixVariable.html)/PARAMETER: Annotation which indicates that a method parameter should be bound to a name-value pair within a path segment.
- [@SessionAttribute](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/SessionAttribute.html)/PARAMETER: Annotation to bind a method parameter to a session attribute.
- [@SessionAttributes](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/SessionAttributes.html)/TYPE: Annotation that indicates the session attributes that a specific handler uses.

### Web Request Parameter
- [@CookieValue](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/CookieValue.html)/PARAMETER: Annotation which indicates that a method parameter should be bound to an HTTP cookie.
- [@RequestAttribute](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestAttribute.html)/PARAMETER: Annotation to bind a method parameter to a request attribute.
- [@RequestBody](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestBody.html)/PARAMETER:Annotation indicating a method parameter should be bound to the body of the web request.
- [@RequestHeader](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestHeader.html)/PARAMETER: Annotation which indicates that a method parameter should be bound to a web request header.
- [@RequestParam](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestParam.html)/PARAMETER: Annotation which indicates that a method parameter should be bound to a web request parameter.
- [@RequestPart](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestParam.html)/PARAMETER: Annotation that can be used to associate the part of a "multipart/form-data" request with a method argument.

### Web Response
- [@ResponseBody](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/ResponseBody.html)/METHOD: Annotation that indicates a method return value should be bound to the web response body.
- [@ResponseStatus](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/ResponseStatus.html)/METHOD: Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.

### Advice
- [@ControllerAdvice](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/ControllerAdvice.html)/TYPE: Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @Controller classes.
- [@RestControllerAdvice](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RestControllerAdvice.html): A convenience annotation that is itself annotated with @ControllerAdvice and @ResponseBody.
- [@ExceptionHandler](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/ExceptionHandler.html)/METHOD: Annotation for handling exceptions in specific handler classes and/or handler methods.
- [@InitBinder](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/InitBinder.html)/METHOD:Annotation that identifies methods which initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.
- [@ModelAttribute](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/ModelAttribute.html)/PARAMETER,METHOD: Annotation that binds a method parameter or method return value to a named model attribute, exposed to a web view.

### [Request Method](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/RequestMethod.html)
- DELETE 
- GET 
- HEAD 
- OPTIONS 
- PATCH 
- POST 
- PUT 
- TRACE 
