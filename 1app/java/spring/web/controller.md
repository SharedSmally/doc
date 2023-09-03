# Controller Layer

## Annotations:org.springframework.web.bind.annotation
### Mapping
- **RestController**:  @Controller + @ResponseBody.
- **CrossOrigin**: permitting cross-origin requests on specific handler classes and/or handler methods.
- **Mapping**: Meta annotation that indicates a web mapping annotation.
- **RequestMapping**: generic mapping web requests onto methods in request-handling classes with flexible method signatures(URL,request parameters,headers,media types).
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

### Method Mapping: GET/POST/PUT/DELETE/PATCH
- **GetMapping**: mapping HTTP GET requests
- **PostMapping**: mapping HTTP POST requests
- **PutMapping**: mapping HTTP PUT requests
- **DeleteMapping**: mapping HTTP DELETE requests
- **PatchMapping**: mapping HTTP PATCH requests
- **ExceptionHandler**: handling exceptions in classes and/or methods.
 
### Request
- **PathVariable**: indicates that a method parameter should be bound to a URI template variable.
- **RequestParam**: indicating a method parameter should be bound to a web request parameter.
- **RequestHeader**: indicating a method parameter should be bound to a web request header.
- **MatrixVariable**: indicates that a method parameter should be bound to a name-value pair within a path segment.
- **RequestAttribute**: bind a method parameter to a request attribute. The return type for attributes is an Object, whereas String for a parameter.
- **RequestBody**: indicating a method parameter should be bound to the body of the web request
- **RequestPart**: associate the part of a "multipart/form-data" request with a method argument.
- **CookieValue**: indicate that a method parameter is bound to an HTTP cookie.

### Response
- **ResponseBody**: indicates a method return value should be bound to the web response body. produces to set the foramt
```
@PostMapping(value = "/content", produces = MediaType.APPLICATION_JSON_VALUE) # MediaType.APPLICATION_XML_VALUE
@ResponseBody
public ResponseTransfer postResponseJsonContent( @RequestBody LoginForm loginForm) {
    return new ResponseTransfer("JSON Content!");
}
```
- **ResponseStatus: Marks a method or exception class with the status ResponseStatus.code() and ResponseStatus.reason() that should be returned.

- **InitBinder**: identifies methods that initialize the WebDataBinder which will be used for populating command and form object arguments of annotated handler methods.

### Seesion attribute
- **SessionAttribute**: bind a method parameter to a session attribute.
- **SessionAttributes**: indicates the session attributes that a specific handler uses.

### Misc
- **ControllerAdvice**: Specialization of @Component for classes that declare @ExceptionHandler, @InitBinder, or @ModelAttribute methods to be shared across multiple @ontroller classes.
- **RestControllerAdvice**: @ControllerAdvice and @ResponseBody.

### URI Patterns

| Patterm | Desc  | Example |
|---------|-------|---------|
|   ?     | Matches one character | "/pages/t?st.html" matches "/pages/test.html" and "/pages/t3st.html" |
|   *     | Matches zero or more characters within a path segment | "/resources/*.png" matches "/resources/file.png"; "/projects/*/versions" matches "/projects/spring/versions" but does not match "/projects/spring/boot/versions"|
|  **     | Matches zero or more path segments until the end of the path | "/resources/**" matches "/resources/file.png" and "/resources/images/file.png" "/resources/**/file.png" is invalid as ** is only allowed at the end of the path.|
| {name}  | Matches a path segment and captures it as a variable named "name" | "/projects/{project}/versions" matches "/projects/spring/versions" and captures project=spring |
| {name:[a-z]+} | Matches the regexp "[a-z]+" as a path variable named "name" | "/projects/{project:[a-z]+}/versions" matches "/projects/spring/versions" but not "/projects/spring1/versions" |
| {*path} | Matches zero or more path segments until the end of the path and captures it as a variable named "path" | "/resources/{*file}" matches "/resources/images/file.png" and captures file=/images/file.png|



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
