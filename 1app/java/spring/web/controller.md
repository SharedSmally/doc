# Controller Layer

## Annotations:org.springframework.web.bind.annotation
### Mapping
- **RestController**:  @Controller + @ResponseBody.
- **CrossOrigin**: permitting cross-origin requests on specific handler classes and/or handler methods.
- **Mapping**: Meta annotation that indicates a web mapping annotation.
- **GetMapping**: mapping HTTP GET requests
- **PostMapping**: mapping HTTP POST requests
- **PutMapping**: mapping HTTP PUT requests
- **DeleteMapping**: mapping HTTP DELETE requests
- **PatchMapping**: mapping HTTP PATCH requests
- **ExceptionHandler**: handling exceptions in classes and/or methods.
 
### Request
- **PathVariable**: indicates that a method parameter should be bound to a URI template variable.
- **RequestAttribute**: bind a method parameter to a request attribute.
- **RequestBody**: indicating a method parameter should be bound to the body of the web request.
- **RequestHeader**: indicating a method parameter should be bound to a web request header.
- **RequestMapping**: mapping web requests onto methods in request-handling classes with flexible method signatures.
- **RequestParam**: indicating a method parameter should be bound to a web request parameter.
- **RequestPart**: associate the part of a "multipart/form-data" request with a method argument.
- **MatrixVariable**: indicates that a method parameter should be bound to a name-value pair within a path segment.
- **CookieValue**: indicate that a method parameter is bound to an HTTP cookie.

### Response
- **ResponseBody**: indicates a method return value should be bound to the web response body.
- **ResponseStatus: Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.
- **ModelAttribute**: binds a method parameter or method return value to a named model attribute, exposed to a web view.
- **InitBinder**: identifies methods that initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.

### Seesion attribute
- **SessionAttribute**: bind a method parameter to a session attribute.
- **SessionAttributes**: indicates the session attributes that a specific handler uses.

### Misc
- **ControllerAdvice**: Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @ontroller classes.
- **RestControllerAdvice**: @ControllerAdvice and @ResponseBody.

