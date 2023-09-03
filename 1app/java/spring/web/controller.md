# Controller Layer

## Annotations:org.springframework.web.bind.annotation
### Mapping
- **RestController**:  @Controller + @ResponseBody. class level annotations
- **CrossOrigin**: permitting cross-origin requests on specific handler classes and/or handler methods.
- **Mapping**: Meta annotation that indicates a web mapping annotation.
- **RequestMapping**: generic mapping web requests onto methods in request-handling classes with flexible method signatures(URL,request parameters,headers,media types). (class or method annotations)
```
@Configuration
@ComponentScan("org.example.web") 
public class WebConfig {  // for auto-detection
	// ...
}

@RestController
@RequestMapping("/persons")
//@RequestMapping("/owners/{ownerId}")   ref @PathVariable Long ownerId, 
public class HelloController {
	@GetMapping("/hello")
	public String handle() {
		return "Hello WebFlux";
	}
	@GetMapping("/{id}")
	public Person getPerson(@PathVariable Long id) {
		// ...
	}
@GetMapping("/owners/{ownerId}/pets/{petId}")
public Pet findPet(@PathVariable Long ownerId, @PathVariable Long petId) {
	// ...
}
	@PostMapping
	@ResponseStatus(HttpStatus.CREATED)
	public void add(@RequestBody Person person) {
		// ...
	}
}
```

### Method Mapping: GET/POST/PUT/DELETE/PATCH (Method annotations)
- **GetMapping**: mapping HTTP GET requests
- **PostMapping**: mapping HTTP POST requests
- **PutMapping**: mapping HTTP PUT requests
- **DeleteMapping**: mapping HTTP DELETE requests
- **PatchMapping**: mapping HTTP PATCH requests
- **ExceptionHandler**: handling exceptions in classes and/or methods.
 
### Request: Method arguments
- **PathVariable**: indicates that a method parameter should be bound to a URI template variable.
- **RequestParam**: indicating a method parameter should be bound to a web request(query) parameter.
```
	@GetMapping
	public String setupForm(@RequestParam("petId") int petId, Model model) { 
		Pet pet = this.clinic.loadPet(petId);
		model.addAttribute("pet", pet);
		return "petForm";
	}
When a @RequestParam annotation is declared on a Map<String, String> or MultiValueMap<String, String> argument, the map is populated with all query parameters.
```
- **RequestHeader**: indicating a method parameter should be bound to a web request header.
```
Host                    localhost:8080
Accept                  text/html,application/xhtml+xml,application/xml;q=0.9
Accept-Language         fr,en-gb;q=0.7,en;q=0.3
Accept-Encoding         gzip,deflate
Accept-Charset          ISO-8859-1,utf-8;q=0.7,*;q=0.7
Keep-Alive              300

@GetMapping("/demo")
public void handle(
		@RequestHeader("Accept-Encoding") String encoding, 
		@RequestHeader("Keep-Alive") long keepAlive) { 
	//...
}
When a @RequestHeader annotation is used on a Map<String, String>, MultiValueMap<String, String>, or HttpHeaders argument, the map is populated with all header values.
```
- **MatrixVariable**: indicates that a method parameter should be bound to a name-value pair within a path segment.
```
// GET /owners/42;q=11/pets/21;q=22
@GetMapping("/owners/{ownerId}/pets/{petId}")
public void findPet(@MatrixVariable(name="q", pathVar="ownerId") int q1,
	@MatrixVariable(name="q", pathVar="petId") int q2) {
	// q1 == 11
	// q2 == 22
}
// GET /pets/42
@GetMapping("/pets/{petId}")
public void findPet(@MatrixVariable(required=false, defaultValue="1") int q) {
	// q == 1
}
// GET /owners/42;q=11;r=12/pets/21;q=22;s=23
@GetMapping("/owners/{ownerId}/pets/{petId}")
public void findPet(@MatrixVariable MultiValueMap<String, String> matrixVars,
		@MatrixVariable(pathVar="petId") MultiValueMap<String, String> petMatrixVars) {
	// matrixVars: ["q" : [11,22], "r" : 12, "s" : 23]
	// petMatrixVars: ["q" : 22, "s" : 23]
}
```
- **RequestAttribute**: bind a method parameter to a request attribute. The return type for attributes is an Object, whereas String for a parameter.@RequestAttribute annotation to access pre-existing request attributes created earlier (for example, by a WebFilter)
```
@GetMapping("/")
public String handle(@RequestAttribute Client client) { 
	// ...
}
```
- **RequestBody**: indicating a method parameter should be bound to the body of the web request
```
@PostMapping("/accounts")
public void handle(@RequestBody Account account) {
	// ...
}
@PostMapping("/accounts")
public void handle(@RequestBody Mono<Account> account) {
	// ...
}
@PostMapping("/accounts")
public void handle(@Valid @RequestBody Mono<Account> account) {
	// use one of the onError* operators...
}

@PostMapping("/accounts")
public void handle(HttpEntity<Account> entity) { // similar to RequestBody
	// ...
}
```
- **RequestPart**: associate the part of a "multipart/form-data" request with a method argument.
```
POST /someUrl
Content-Type: multipart/mixed

--edt7Tfrdusa7r3lNQc79vXuhIIMlatb7PQg7Vp
Content-Disposition: form-data; name="meta-data"
Content-Type: application/json; charset=UTF-8
Content-Transfer-Encoding: 8bit

{
	"name": "value"
}
--edt7Tfrdusa7r3lNQc79vXuhIIMlatb7PQg7Vp
Content-Disposition: form-data; name="file-data"; filename="file.properties"
Content-Type: text/xml
Content-Transfer-Encoding: 8bit
... File Data ...

@PostMapping("/")
public String handle(@RequestPart("meta-data") Part metadata, 
		@RequestPart("file-data") FilePart file) { 
	// ...
}
@PostMapping("/")
public String handle(@Valid @RequestPart("meta-data") Mono<MetaData> metadata) {
	// use one of the onError* operators...
}
@PostMapping("/")
public String handle(@RequestBody Mono<MultiValueMap<String, Part>> parts) { //access all multipart data
	// ...
}
@PostMapping("/")
public void handle(@RequestBody Flux<PartEvent> allPartsEvents) { //access multipart data sequentially, in a streaming fashion,
}

or using data binding to a command object,
class MyForm {
	private String name;
	private MultipartFile file;
	// ...
}

@Controller
public class FileUploadController {
	@PostMapping("/form")
	public String handleFormUpload(MyForm form, BindingResult errors) {
		// ...
	}
}
```
- **CookieValue**: indicate that a method parameter is bound to an HTTP cookie.
```
JSESSIONID=415A4AC178C59DACE0B2C9CA727CDD84
@GetMapping("/demo")
public void handle(@CookieValue("JSESSIONID") String cookie) { 
	//...
}
```
### Response
- **ResponseBody**: indicates a method return value should be bound to the web response body. produces to set the foramt
```
@PostMapping(value = "/content", produces = MediaType.APPLICATION_JSON_VALUE) # MediaType.APPLICATION_XML_VALUE
@ResponseBody
public ResponseTransfer postResponseJsonContent( @RequestBody LoginForm loginForm) {
    return new ResponseTransfer("JSON Content!");
}
ResponseEntity is like @ResponseBody but with status and headers:
@GetMapping("/something")
public ResponseEntity<String> handle() {
	String body = ... ;
	String etag = ... ;
	return ResponseEntity.ok().eTag(etag).body(body);
}
```
WebFlux supports using a single value reactive type to produce the ResponseEntity asynchronously, and/or single and multi-value reactive types for the body. This allows a variety of async responses with ResponseEntity as follows:
    - ResponseEntity<Mono<T>> or ResponseEntity<Flux<T>> make the response status and headers known immediately while the body is provided asynchronously at a later point. Use Mono if the body consists of 0..1 values or Flux if it can produce multiple values.
    - Mono<ResponseEntity<T>> provides all three — response status, headers, and body, asynchronously at a later point. This allows the response status and headers to vary depending on the outcome of asynchronous request handling.
    - Mono<ResponseEntity<Mono<T>>> or Mono<ResponseEntity<Flux<T>>> are yet another possible, albeit less common alternative. They provide the response status and headers asynchronously first and then the response body, also asynchronously, second.

 Use Jackson’s @JsonView annotation to activate a serialization view class with @ResponseBody or ResponseEntity controller methods, 
```
@RestController
public class UserController {
	@GetMapping("/user")
	@JsonView(User.WithoutPasswordView.class)
	public User getUser() {
		return new User("eric", "7!jd#h23");
	}
}

public class User {
	public interface WithoutPasswordView {};
	public interface WithPasswordView extends WithoutPasswordView {};

	private String username;
	private String password;

	public User() {
	}

	public User(String username, String password) {
		this.username = username;
		this.password = password;
	}

	@JsonView(WithoutPasswordView.class)
	public String getUsername() {
		return this.username;
	}

	@JsonView(WithPasswordView.class)
	public String getPassword() {
		return this.password;
	}
}
``` 
- **ResponseStatus**: Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.
- **ModelAttribute**: Access an attribute from the model or have it instantiated if not present. It is overlaid with the values of query parameters and form fields whose names match to field name( data binding, no need to parse and converting individual query parameters and form fields.)
```
@PostMapping("/owners/{ownerId}/pets/{petId}/edit")
public String processSubmit(@ModelAttribute Pet pet) { }

@PostMapping("/owners/{ownerId}/pets/{petId}/edit")
public String processSubmit(@ModelAttribute("pet") Pet pet, BindingResult result) { 
	if (result.hasErrors()) {
		return "petForm";
	}
	// ...
}
@PostMapping("/owners/{ownerId}/pets/{petId}/edit")
public String processSubmit(@Valid @ModelAttribute("pet") Pet pet, BindingResult result) { //apply validation automatically
	if (result.hasErrors()) {
		return "petForm";
	}
	// ...
}
@PostMapping("/owners/{ownerId}/pets/{petId}/edit")
public Mono<String> processSubmit(@Valid @ModelAttribute("pet") Mono<Pet> petMono) { // for WebFlux
	return petMono
		.flatMap(pet -> {
			// ...
		})
		.onErrorResume(ex -> {
			// ...
		});
}

The Pet instance in the preceding example is resolved as follows:
    From the model if already added through Model.
    From the HTTP session through @SessionAttributes.
    From the invocation of a default constructor.
    From the invocation of a “primary constructor” with arguments that match query parameters or form fields. Argument names are determined through JavaBeans @ConstructorProperties or through runtime-retained parameter names in the bytecode.

The default arguments are ModelAttribute.
```
- **InitBinder**: identifies methods that initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.
@Controller or @ControllerAdvice classes can have @InitBinder methods, to initialize instances of WebDataBinder. Those, in turn, are used to:
    - Bind request parameters (that is, form data or query) to a model object.
    - Convert String-based request values (such as request parameters, path variables, headers, cookies, and others) to the target type of controller method arguments.
    - Format model object values as String values when rendering HTML forms.
```
@Controller
public class FormController {
	@InitBinder 
	public void initBinder(WebDataBinder binder) {
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
		dateFormat.setLenient(false);
		binder.registerCustomEditor(Date.class, new CustomDateEditor(dateFormat, false));
	}
}
```

- @ExceptionHandler
@Controller and @ControllerAdvice classes can have @ExceptionHandler methods to handle exceptions from controller methods. The same signature as @RequestMapping methods
```
@Controller
public class SimpleController {
	@ExceptionHandler 
	public ResponseEntity<String> handle(IOException ex) {
		// ...
	}
}
```

### Seesion attribute
- **SessionAttribute**: bind a method parameter to a session attribute. store model attributes in the WebSession between requests.
```
@Controller
@SessionAttributes("pet") 
public class EditPetForm {
	// ...
}
On the first request, when a model attribute with the name, pet, is added to the model, it is automatically promoted to and saved in the WebSession. It remains there until another controller method uses a SessionStatus method argument to clear the storage,

	@PostMapping("/pets/{id}")
	public String handle(Pet pet, BindingResult errors, SessionStatus status) { 
		if (errors.hasErrors()) {
			// ...
		}
			status.setComplete();
			// ...
		}
	}

If you need access to pre-existing session attributes that are managed globally (that is, outside the controller — for example, by a filter) and may or may not be present, you can use the @SessionAttribute annotation on a method parameter
@GetMapping("/")
public String handle(@SessionAttribute User user) { 
	// ...
}
```  
- **SessionAttributes**: indicates the session attributes that a specific handler uses (temperatively).

### Model & Data Binder
Use the @ModelAttribute annotation:
- On a method argument in @RequestMapping methods to create or access an Object from the model and to bind it to the request through a WebDataBinder.
- As a method-level annotation in @Controller or @ControllerAdvice classes, helping to initialize the model prior to any @RequestMapping method invocation.
- On a @RequestMapping method to mark its return value as a model attribute.

The @ModelAttribute methods: similar signatures to @RequestMapping methods, A controller can have any number of @ModelAttribute methods. All such methods are invoked before @RequestMapping methods in the same controller.
```
@ModelAttribute
public void populateModel(@RequestParam String number, Model model) {
	model.addAttribute(accountRepository.findAccount(number));
	// add more ...
}
//only add one attribute, the default name is used. can be override
@ModelAttribute
public Account addAccount(@RequestParam String number) { 
	return accountRepository.findAccount(number);
}
// For Spring WebFlux
@ModelAttribute
public void addAccount(@RequestParam String number) {
    Mono<Account> accountMono = accountRepository.findAccount(number);
    model.addAttribute("account", accountMono);
}

@PostMapping("/accounts")
public String handle(@ModelAttribute Account account, BindingResult errors) {
	// ...
}
//use @ModelAttribute as a method-level annotation on @RequestMapping methods, in which case
//the return value of the @RequestMapping method is interpreted as a model attribute. 
@GetMapping("/accounts/{id}")
@ModelAttribute("myAccount")
public Account handle() {
	// ...
	return account;
}
```

### Misc
- **ControllerAdvice**: Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @ontroller classes.
- **RestControllerAdvice**: @ControllerAdvice and @ResponseBody.

Typically, the @ExceptionHandler, @InitBinder, and @ModelAttribute methods apply within the @Controller class (or class hierarchy) in which they are declared. If you want such methods to apply more globally (across controllers), you can declare them in a class annotated with @ControllerAdvice or @RestControllerAdvice.

@ControllerAdvice is annotated with @Component, which means that such classes can be registered as Spring beans through component scanning . @RestControllerAdvice is a composed annotation that is annotated with both @ControllerAdvice and @ResponseBody, which essentially means @ExceptionHandler methods are rendered to the response body through message conversion (versus view resolution or template rendering).

By default, @ControllerAdvice methods apply to every request (that is, all controllers), but you can narrow that down to a subset of controllers by using attributes on the annotation,
```
// Target all Controllers annotated with @RestController
@ControllerAdvice(annotations = RestController.class)
public class ExampleAdvice1 {}

// Target all Controllers within specific packages
@ControllerAdvice("org.example.controllers")
public class ExampleAdvice2 {}

// Target all Controllers assignable to specific classes
@ControllerAdvice(assignableTypes = {ControllerInterface.class, AbstractController.class})
public class ExampleAdvice3 {}
```



### URI Patterns
| Patterm | Desc  | Example |
|---------|-------|---------|
|   ?     | Matches one character | "/pages/t?st.html" matches "/pages/test.html" and "/pages/t3st.html" |
|   *     | Matches zero or more characters within a path segment | "/resources/*.png" matches "/resources/file.png"; "/projects/*/versions" matches "/projects/spring/versions" but does not match "/projects/spring/boot/versions"|
|  **     | Matches zero or more path segments until the end of the path | "/resources/**" matches "/resources/file.png" and "/resources/images/file.png" "/resources/**/file.png" is invalid as ** is only allowed at the end of the path.|
| {name}  | Matches a path segment and captures it as a variable named "name" | "/projects/{project}/versions" matches "/projects/spring/versions" and captures project=spring |
| {name:[a-z]+} | Matches the regexp "[a-z]+" as a path variable named "name" | "/projects/{project:[a-z]+}/versions" matches "/projects/spring/versions" but not "/projects/spring1/versions" |
| {*path} | Matches zero or more path segments until the end of the path and captures it as a variable named "path" | "/resources/{*file}" matches "/resources/images/file.png" and captures file=/images/file.png|

### Method Arguments
| Controller method argument  | Description |
|---------|--------------|
| ServerWebExchange | Access to the full ServerWebExchange — container for the HTTP request and response, request and session attributes, checkNotModified methods, and others. |
| ServerHttpRequest, ServerHttpResponse | Access to the HTTP request or response. |
| WebSession | Access to the session. This does not force the start of a new session unless attributes are added. Supports reactive types. |
| java.security.Principal | The currently authenticated user — possibly a specific Principal implementation class if known. Supports reactive types. |
| org.springframework.http.HttpMethod | The HTTP method of the request. |
| java.util.Locale | The current request locale, determined by the most specific LocaleResolver available — in effect, the configured LocaleResolver/LocaleContextResolver. |
| java.util.TimeZone + java.time.ZoneId | The time zone associated with the current request, as determined by a LocaleContextResolver. |
| @PathVariable | For access to URI template variables. See URI Patterns. |
| @MatrixVariable | For access to name-value pairs in URI path segments. See Matrix Variables. |
| @RequestParam | For access to query parameters. Parameter values are converted to the declared method argument type. See @RequestParam.. Note that use of @RequestParam is optional — for example, to set its attributes. See “Any other argument” later in this table. |
| @RequestHeader | For access to request headers. Header values are converted to the declared method argument type. See @RequestHeader. |
| @CookieValue | For access to cookies. Cookie values are converted to the declared method argument type. See @CookieValue. |
| @RequestBody | For access to the HTTP request body. Body content is converted to the declared method argument type by using HttpMessageReader instances. Supports reactive types. See @RequestBody. |
| HttpEntity<B> | For access to request headers and body. The body is converted with HttpMessageReader instances. Supports reactive types. See HttpEntity. |
| @RequestPart | For access to a part in a multipart/form-data request. Supports reactive types. See Multipart Content and Multipart Data. |
| java.util.Map, org.springframework.ui.Model, and org.springframework.ui.ModelMap. | For access to the model that is used in HTML controllers and is exposed to templates as part of view rendering. |
| @ModelAttribute | For access to an existing attribute in the model (instantiated if not present) with data binding and validation applied. See @ModelAttribute as well as Model and DataBinder. Note that use of @ModelAttribute is optional — for example, to set its attributes. See “Any other argument” later in this table. |
| Errors, BindingResult | For access to errors from validation and data binding for a command object, i.e. a @ModelAttribute argument. An Errors, or BindingResult argument must be declared immediately after the validated method argument. |
| SessionStatus + class-level @SessionAttributes | For marking form processing complete, which triggers cleanup of session attributes declared through a class-level @SessionAttributes annotation. See @SessionAttributes for more details.| 
| UriComponentsBuilder | For preparing a URL relative to the current request’s host, port, scheme, and context path. See URI Links. |
| @SessionAttribute | For access to any session attribute — in contrast to model attributes stored in the session as a result of a class-level @SessionAttributes declaration. See @SessionAttribute for more details. |
| @RequestAttribute | For access to request attributes. See @RequestAttribute for more details. |
| Any other argument | If a method argument is not matched to any of the above, it is, by default, resolved as a @RequestParam if it is a simple type, as determined by BeanUtils#isSimpleProperty, or as a @ModelAttribute, otherwise. |

### Method Return Values
| Controller method return value  | Description |
|---------|--------------|
| @ResponseBody | The return value is encoded through HttpMessageWriter instances and written to the response. See @ResponseBody.|
| HttpEntity<B>, ResponseEntity<B> | The return value specifies the full response, including HTTP headers, and the body is encoded through HttpMessageWriter instances and written to the response. See ResponseEntity. |
| HttpHeaders | For returning a response with headers and no body. |
| ErrorResponse | To render an RFC 7807 error response with details in the body, see Error Responses |
| ProblemDetail | To render an RFC 7807 error response with details in the body, see Error Responses |
| String | A view name to be resolved with ViewResolver instances and used together with the implicit model — determined through command objects and @ModelAttribute methods. The handler method can also programmatically enrich the model by declaring a Model argument (described earlier). |
| View | A View instance to use for rendering together with the implicit model — determined through command objects and @ModelAttribute methods. The handler method can also programmatically enrich the model by declaring a Model argument (described earlier). |
| java.util.Map, org.springframework.ui.Model | Attributes to be added to the implicit model, with the view name implicitly determined based on the request path. |
| @ModelAttribute | An attribute to be added to the model, with the view name implicitly determined based on the request path.Note that @ModelAttribute is optional. See “Any other return value” later in this table. |
| Rendering | An API for model and view rendering scenarios. |
| void | A method with a void, possibly asynchronous (for example, Mono<Void>), return type (or a null return value) is considered to have fully handled the response if it also has a ServerHttpResponse, a ServerWebExchange argument, or an @ResponseStatus annotation. The same is also true if the controller has made a positive ETag or lastModified timestamp check. See Controllers for details.If none of the above is true, a void return type can also indicate “no response body” for REST controllers or default view name selection for HTML controllers. |
| Flux<ServerSentEvent>, Observable<ServerSentEvent>, or other reactive type | Emit server-sent events. The ServerSentEvent wrapper can be omitted when only data needs to be written (however, text/event-stream must be requested or declared in the mapping through the produces attribute). |
| Other return values | If a return value remains unresolved in any other way, it is treated as a model attribute, unless it is a simple type as determined by BeanUtils#isSimpleProperty, in which case it remains unresolved. |




## Samples
### [RequestMapping](https://www.baeldung.com/spring-requestmapping): For class/method
```
# Path variable: http://localhost:8080/spring-rest/ex/foos/1
@RequestMapping(value = "/ex/foos/{id}", method = GET,  
       produces = { "application/json", "application/xml" })  
       #curl -H "Accept:application/json" http://localhost:8080/spring-rest/ex/foos
@ResponseBody
public String getFoosBySimplePathWithPathVariable(@PathVariable("id") long id) {
    return "Get a specific Foo with id=" + id;
}
@RequestMapping(value = "/ex/bars/{numericId:[\\d]+}", method = GET)  # with regex
public String getBarsBySimplePathWithPathVariable( @PathVariable long numericId) {}

#Request Parameters: http://localhost:8080/spring-rest/ex/bars?id=100
@RequestMapping(value = "/ex/bars", method = GET)  
    # value = { "/ex/advanced/bars", "/ex/advanced/foos" }, # multiple paths
    # method = { RequestMethod.PUT, RequestMethod.POST }    # multiple methods
public String getBarBySimplePathWithRequestParam(@RequestParam("id") long id)
@GetMapping("/{id}")
public ResponseEntity<?> getBazz(@PathVariable String id){}
```

### [InitBinder](https://www.logicbig.com/tutorials/spring-framework/spring-web-mvc/spring-custom-property-editor.html)
Used with the methods which initializes WebDataBinder and as a preprocessor for each request coming to the controller.

```
@Controller
public class MyController{
 # void method with one parameter as WebDataBinder to register custom formatter, validators and PropertyEditors
 @InitBinder
 @InitBinder("user") #
 public void customizeBinding (WebDataBinder binder, ......) {  
 }
   ....
}
```
The Model class with custom validatioin:
```
  public class User {
    private Long id;

    @Size(min = 5, max = 20)
    private String name;

    @Size(min = 6, max = 15)
    @Pattern(regexp = "\\S+", message = "Spaces are not allowed")
    private String password;

    @NotEmpty
    @Email
    private String emailAddress;

    @NotNull
    private Date dateOfBirth;
 }
```
Using InitBinder to validate the input in BindingResult:
```
@Controller
@RequestMapping("/register")
public class UserRegistrationController {
    @Autowired
    private UserService userService;

    @InitBinder("user")
    public void customizeBinding (WebDataBinder binder) {
        SimpleDateFormat dateFormatter = new SimpleDateFormat("yyyy-MM-dd");
        dateFormatter.setLenient(false);
        binder.registerCustomEditor(Date.class, "dateOfBirth", new CustomDateEditor(dateFormatter, true));
    }

    @RequestMapping(method = RequestMethod.GET)
    public String handleGetRequest (Model model) {
        model.addAttribute("user", new User());
        return "user-registration";
    }

    @RequestMapping(method = RequestMethod.POST)
    public String handlePostRequest (@Valid @ModelAttribute("user") User user,
                                     BindingResult bindingResult, Model model) {
        if (bindingResult.hasErrors()) {
            return "user-registration";
        }

        userService.saveUser(user);
        model.addAttribute("users", userService.getAllUsers());
        return "registration-done";
    }
}
```

The @InitBinder annotated methods will get called on each HTTP request if nt specify the 'value' element. Each time this method is called a new instance of WebDataBinder is passed to it.


### [RequestBody](https://www.baeldung.com/spring-request-response-body): 
method parameter for automatic deserialization of the inbound HttpRequest body (default in json format) onto a Java object
```
@PostMapping("/request")
public ResponseEntity postController(@RequestBody LoginForm loginForm) {
     ...
    return ResponseEntity.ok(HttpStatus.OK);
}

public class LoginForm {
    private String username;
    private String password;
    // ...
}

curl -i -H "Accept: application/json" -H "Content-Type:application/json" \
-X POST --data '{"username": "johnny", "password": "password"}' "https://localhost:8080/.../request"
```

### [ModelAttribute](https://www.baeldung.com/spring-mvc-and-the-modelattribute-annotation): method return value or parameter

The @ModelAttribute methods are invoked before the controller methods annotated with @RequestMapping are invoked. 
```
@ModelAttribute
public void addAttributes(Model model) {
    model.addAttribute("msg", "Welcome to the Netherlands!");
}

@RequestMapping(value = "/addEmployee", method = RequestMethod.POST)
public String submit(@ModelAttribute("employee") Employee employee) { }

<form:form method="POST" action="/spring-mvc-basics/addEmployee" modelAttribute="employee">
    <form:label path="name">Name</form:label> <form:input path="name" />
    <form:label path="id">Id</form:label> <form:input path="id" />    
    <input type="submit" value="Submit" />
</form:form>

@Controller
@ControllerAdvice
public class EmployeeController {
    private Map<Long, Employee> employeeMap = new HashMap<>();

    @RequestMapping(value = "/addEmployee", method = RequestMethod.POST)
    public String submit( @ModelAttribute("employee") Employee employee, BindingResult result, ModelMap model) {
        if (result.hasErrors()) { return "error";   }
        model.addAttribute("name", employee.getName());
        model.addAttribute("id", employee.getId());
        employeeMap.put(employee.getId(), employee);
        return "employeeView";
    }

    @ModelAttribute
    public void addAttributes(Model model) {
        model.addAttribute("msg", "Welcome to the Netherlands!");
    }
}
```

### @RequestParam vs @@RequestAttribute
@RequestParam is used to bind parameter values from 'query string' e.g. in http://www.example.com?myParam=3, myParam=3 can populate @RequestParam parameter. @RequestAttribute is to access objects which have been populated on the server-side but during the same HTTP request, for example they can be populated in an interceptor or a filter.

The interceptor
```
public class MyCounterInterceptor extends HandlerInterceptorAdapter {
  private AtomicInteger counter = new AtomicInteger(0);
  @Override
  public boolean preHandle (HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
      request.setAttribute("visitorCounter", counter.incrementAndGet());
      return true;
  }
}
```
The controller
```
@Controller
public class ExampleController {
  @RequestMapping("/")
  @ResponseBody
  public String handle (@RequestAttribute("visitorCounter") Integer counter) {
      return String.format("Visitor number: %d", counter);
  }
}
```

### [@SessionAttribute](https://www.baeldung.com/spring-mvc-session-attributes):
When need to refer to the same attributes in several views, a good location to store those attributes is in the user's session. declare it as a @ModelAttribute and specify the @SessionAttributes annotation to scope it to the session for the controller.
- declare the bean by providing a method on the controller and we annotate the method with @ModelAttribute:
```
@ModelAttribute("todos")
public TodoList todos() {
    return new TodoList();
}
```
- inform the controller to treat TodoList as session-scoped by using @SessionAttributes:
```
@Controller
@RequestMapping("/sessionattributes")
@SessionAttributes("todos")
public class TodoControllerWithSessionAttributes {
    // ... other methods
}
```
- use the bean within a request, provide a reference to it in the method signature of a @RequestMapping:
```
@GetMapping("/form")
public String showForm( Model model, @ModelAttribute("todos") TodoList todos) {
    if (!todos.isEmpty()) {
        model.addAttribute("todo", todos.peekLast());
    } else {
        model.addAttribute("todo", new TodoItem());
    }
    return "sessionattributesform";
}
```
and
```
@PostMapping("/form")
public RedirectView create( @ModelAttribute TodoItem todo,  @ModelAttribute("todos") TodoList todos, RedirectAttributes attributes) {
    todo.setCreateDate(LocalDateTime.now());
    todos.add(todo);
    attributes.addFlashAttribute("todos", todos);
    return new RedirectView("/sessionattributes/todos.html");
}
```
Spring uses a specialized RedirectAttributes implementation of Model for redirect scenarios to support the encoding of URL parameters. During a redirect, any attributes stored on the Model would normally only be available to the framework if they were included in the URL.

By using addFlashAttribute we are telling the framework that we want our TodoList to survive the redirect without needing to encode it in the URL.
