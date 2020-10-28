# Spring Web Framework
Spring web framework is built on the MVC (Model-View-Controller) pattern, it needs to define a ViewResolver bean corresponding 
for each technology to render each view type, so returning the view names from @Controller mapping methods in the same way as returning JSP files.

Template engines: [Configuration](https://www.baeldung.com/spring-template-engines) and [Comparison](https://springhow.com/spring-boot-template-engines-comparison/)
- Thymeleaf: HTML files should be placed in the resources/templates location
- FreeMarker: placing template files (*.ftl) in the resources/templates folder
- Java Server Pages (JSP): not good
- Groovy: slower; placing template files (*.groovy) in the resources/templates folder using html
- Jade
- Mustache (faster), smiliar to FreeMarker
- Pebble
- jasper: for docs or PDF


## Controllers
- Normal controller: method() return view name, and the corresponding view page is rendered via template engine (template file name without .html suffix)  
    - [Config thymeleaf](http://zetcode.com/springboot/thymeleafconfig/): Not needed in autoconfig.
    - Serialize returned object if specified as @RequestBody
```
@Controller
@RequestMapping("books")
public class SimpleBookController { 
    @GetMapping("/{id}", produces = "application/json")
    public @ResponseBody Book getBook(@PathVariable int id) {
        return findBookById(id);
    }
 
    private Book findBookById(int id) {
        // ...
    }
}
```
- RestController: @Controller+@ResponseBody, method() return model object, and the corresponding json string is rendered
```
@RestController
@RequestMapping("books-rest")
public class SimpleBookRestController {   
    @GetMapping("/{id}", produces = "application/json")
    public Book getBook(@PathVariable int id) {
        return findBookById(id);
    }
 
    private Book findBookById(int id) {
        // ...
    }
}
```

## [Pass parameters to render a View](https://www.baeldung.com/spring-mvc-model-model-map-model-view)
- via Model, method returns the View name

The model can supply attributes used for rendering views. To provide a view with usable data, simply add this data to its Model object. Additionally, maps with attributes can be merged with Model instances:
```
@GetMapping("/showViewPage")
public String passParametersWithModel(Model model) {
    Map<String, String> map = new HashMap<>();
    map.put("spring", "mvc");
    model.addAttribute("message", "Baeldung");
    model.mergeAttributes(map);
    return "viewPage";
}
```
- via ModelMap, method returns the View name 

ModelMap can pass a collection of values and treat these values as if they were within a Map
```
@GetMapping("/printViewPage")
public String passParametersWithModelMap(ModelMap map) {
    map.addAttribute("welcomeMessage", "welcome");
    map.addAttribute("message", "Baeldung");
    return "viewPage";
}
```
- via ModelView

Pass all the information required by Spring MVC in one return.
```
@GetMapping("/goToViewPage")
public ModelAndView passParametersWithModelAndView() {
    ModelAndView modelAndView = new ModelAndView("viewPage");
    modelAndView.addObject("message", "customer message");
    return modelAndView;
}
```

## Request Mapping
- [web bind annotation](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/annotation/package-summary.html)

### [Request Mapping](https://www.baeldung.com/spring-requestmapping)
- By Path and HTTP method
```
@RequestMapping(value = "/ex/foos", method = RequestMethod.GET)
@ResponseBody
public String getFoosBySimplePath() {
    return "Get some Foos";
}

@RequestMapping(value = "/ex/foos", method = POST)
@ResponseBody
public String postFoos() {
    return "Post some Foos";
}
```
- With the headers Attribute
```
@RequestMapping(value = "/ex/foos", headers = "key=val", method = GET)
@ResponseBody
public String getFoosWithHeader() {
    return "Get some Foos with Header";
}

@RequestMapping( value = "/ex/foos",  headers = { "key1=val1", "key2=val2" }, method = GET)
@ResponseBody
public String getFoosWithHeaders() {
    return "Get some Foos with Header";
}
```
- Consumes and Produces and Accept header 
```
@RequestMapping( value = "/ex/foos", method = GET, headers = "Accept=application/json")
@ResponseBody
public String getFoosAsJsonFromBrowser() {
    return "Get some Foos with Header Old";
}

@RequestMapping(value = "/ex/foos", method = RequestMethod.GET, produces = "application/json")
@ResponseBody
public String getFoosAsJsonFromREST() {
    return "Get some Foos with Header New";
}
@RequestMapping(value = "/ex/foos", method = GET, produces = { "application/json", "application/xml" })
```
- Path Variables
```
@RequestMapping(value = "/ex/foos/{id}", method = GET)
@ResponseBody
public String getFoosBySimplePathWithPathVariable(@PathVariable("id") long id) {
    return "Get a specific Foo with id=" + id;
}

@RequestMapping(value = "/ex/foos/{id}", method = GET)
@ResponseBody
public String getFoosBySimplePathWithPathVariable(@PathVariable String id) {
    return "Get a specific Foo with id=" + id;
}

@RequestMapping(value = "/ex/foos/{fooid}/bar/{barid}", method = GET)
@ResponseBody
public String getFoosBySimplePathWithPathVariables(@PathVariable long fooid, @PathVariable long barid) {
    return "Get a specific Bar with id=" + barid + " from a Foo with id=" + fooid;
}

@RequestMapping(value = "/ex/bars/{numericId:[\\d]+}", method = GET)
@ResponseBody
public String getBarsBySimplePathWithPathVariable(@PathVariable long numericId) {
    return "Get a specific Bar with id=" + numericId;
}
```
- Request Parameters
```
//http://localhost:8080/spring-rest/ex/bars?id=100
@RequestMapping(value = "/ex/bars", method = GET)
@ResponseBody
public String getBarBySimplePathWithRequestParam(@RequestParam("id") long id) {
    return "Get a specific Bar with id=" + id;
}

@RequestMapping(value = "/ex/bars", params = "id", method = GET)
@ResponseBody
public String getBarBySimplePathWithExplicitRequestParam(@RequestParam("id") long id) {
    return "Get a specific Bar with id=" + id;
}

//http://localhost:8080/spring-rest/ex/bars?id=100&second=something
@RequestMapping(value = "/ex/bars", params = { "id", "second" }, method = GET)
@ResponseBody
public String getBarBySimplePathWithExplicitRequestParams(@RequestParam("id") long id) {
    return "Narrow Get a specific Bar with id=" + id;
}
```
- Multiple Paths Mapped to the Same Controller Method
```
@RequestMapping(value = { "/ex/advanced/bars", "/ex/advanced/foos" },  method = GET)
@ResponseBody
public String getFoosOrBarsByPath() {
    return "Advanced - Get some Foos or Bars";
}
```
- Multiple HTTP Request Methods to the Same Controller Method
```
@RequestMapping(value = "/ex/foos/multiple", method = { RequestMethod.PUT, RequestMethod.POST } )
@ResponseBody
public String putAndPostFoos() {
    return "Advanced - PUT and POST within single method";
}
```
- a Fallback for All Requests
```
@RequestMapping(value = "*", method = RequestMethod.GET)
@ResponseBody
public String getFallback() {
    return "Fallback for GET Requests";
}

@RequestMapping(value = "*", method = { RequestMethod.GET, RequestMethod.POST ... })
@ResponseBody
public String allFallback() {
    return "Fallback for All Requests";
}
```
- New Request Mapping Shortcuts
    - @GetMapping
    - @PostMapping
    - @PutMapping
    - @DeleteMapping
    - @PatchMapping
```
@GetMapping("/{id}")
public ResponseEntity<?> getBazz(@PathVariable String id){
    return new ResponseEntity<>(new Bazz(id, "Bazz"+id), HttpStatus.OK);
}
 
@PostMapping
public ResponseEntity<?> newBazz(@RequestParam("name") String name){
    return new ResponseEntity<>(new Bazz("5", name), HttpStatus.OK);
}
 
@PutMapping("/{id}")
public ResponseEntity<?> updateBazz( @PathVariable String id,  @RequestParam("name") String name) {
    return new ResponseEntity<>(new Bazz(id, name), HttpStatus.OK);
}
 
@DeleteMapping("/{id}")
public ResponseEntity<?> deleteBazz(@PathVariable String id){
    return new ResponseEntity<>(new Bazz(id), HttpStatus.OK);
}
```

### [RequestParam](https://www.baeldung.com/spring-request-param)
- A Simple Mapping: http://localhost:8080/api/foos?id=abc
```
@GetMapping("/api/foos")
@ResponseBody
public String getFoos(@RequestParam String id) {
    return "ID: " + id;
}
```
- Specify the Request Parameter Name: 
```
@PostMapping("/api/foos")
@ResponseBody
public String addFoo(@RequestParam(name = "id") String fooId, @RequestParam String name) { 
    //same as @RequestParam(value = “id”) or @RequestParam(“id”). 
    return "ID: " + fooId + " Name: " + name;
}
```
- Optional Request Parameters
```
@GetMapping("/api/foos")
@ResponseBody
public String getFoos(@RequestParam(required = false) String id) { 
    return "ID: " + id; //NULL if missing
}

@GetMapping("/api/foos")
@ResponseBody
public String getFoos(@RequestParam Optional<String> id){ //Java8 Optional
    return "ID: " + id.orElseGet(() -> "not provided");
}
```
- A Default Value for the Request Parameter
```
@GetMapping("/api/foos")
@ResponseBody
public String getFoos(@RequestParam(defaultValue = "test") String id) {
    return "ID: " + id;
}
```
- Mapping All Parameters
```
@PostMapping("/api/foos")
@ResponseBody
public String updateFoos(@RequestParam Map<String,String> allParams) {
    return "Parameters are " + allParams.entrySet();
}
```
- Mapping a Multi-Value Parameter: A single @RequestParam can have multiple values
```
@GetMapping("/api/foos")
@ResponseBody
public String getFoos(@RequestParam List<String> id) {
    return "IDs are " + id;
}
http://localhost:8080/api/foos?id=1,2,3
http://localhost:8080/api/foos?id=1&id=2
```

### PathVariable
@PathVariable indicates that a method parameter should be bound to a URI template variable. If the method parameter is Map<String, String> then the map is populated with all path variable names and values. It has the following optional elements:
- name - name of the path variable to bind to
- required - tells whether the path variable is required
- value - alias for name

```
@RestController
public class MyController {
    private static final Logger logger = LoggerFactory.getLogger(MyController.class);

    @ResponseStatus(value = HttpStatus.OK)
    @GetMapping(value = "/user/{name}")
    public void process(@PathVariable String name) {
        logger.info("User name: {}", name);
    }

    @ResponseStatus(value = HttpStatus.OK)
    @GetMapping(value = "/user/{name}/{email}")
    public void process2(@PathVariable String name, @PathVariable String email) {
        logger.info("User name: {} and email: {}", name, email);
    }

    @ResponseStatus(value = HttpStatus.OK)
    @GetMapping(value = "/book/{author}/{title}")
    public void process3(@PathVariable Map<String, String> vals) {
        logger.info("{}: {}", vals.get("author"), vals.get("title"));
    }
}
```

### [Request Headers](https://www.baeldung.com/spring-rest-http-headers)
- Accessing HTTP Headers: header could be string, numeric type. If a named header isn't found in the request, the method returns a “400 Bad Request” error. 
```
@GetMapping("/greeting")
public ResponseEntity<String> greeting(@RequestHeader("accept-language") String language) {
    return new ResponseEntity<String>(greeting, HttpStatus.OK);
}

@GetMapping("/double")
public ResponseEntity<String> doubleNumber(@RequestHeader("my-number") int myNumber) {
    return new ResponseEntity<String>(String.format("%d * 2 = %d",  myNumber, (myNumber * 2)), HttpStatus.OK);
}
```
- All Headers: could use a Map, a MultiValueMap(headers may have multiple values) or a HttpHeaders object
```
@GetMapping("/listHeaders")
public ResponseEntity<String> listAllHeaders(@RequestHeader Map<String, String> headers) {
    headers.forEach((key, value) -> { LOG.info(String.format("Header '%s' = %s", key, value)); });
    return new ResponseEntity<String>(String.format("Listed %d headers", headers.size()), HttpStatus.OK);
}
// If the header has more than one value, will get only the first value using Map

@GetMapping("/multiValue")
public ResponseEntity<String> multiValue( @RequestHeader MultiValueMap<String, String> headers) {
    headers.forEach((key, value) -> { LOG.info(String.format("Header '%s' = %s", key, value.stream().collect(Collectors.joining("|"))));  });
        
    return new ResponseEntity<String>(String.format("Listed %d headers", headers.size()), HttpStatus.OK);
}

@GetMapping("/getBaseUrl")
public ResponseEntity<String> getBaseUrl(@RequestHeader HttpHeaders headers) {
    InetSocketAddress host = headers.getHost();
    String url = "http://" + host.getHostName() + ":" + host.getPort();
    return new ResponseEntity<String>(String.format("Base URL = %s", url), HttpStatus.OK);
}
```
- @RequestHeader Attributes
```
public ResponseEntity<String> greeting(@RequestHeader("accept-language") String language) {}
public ResponseEntity<String> greeting(@RequestHeader(name = "accept-language") String language) {}
public ResponseEntity<String> greeting(@RequestHeader(value = "accept-language") String language) {}
```
When we name a header specifically, the header is required by default. If the header isn't found in the request, the controller returns a 400 error.
```
@GetMapping("/nonRequiredHeader")
public ResponseEntity<String> evaluateNonRequiredHeader(@RequestHeader(value = "optional-header", required = false) String optionalHeader) {
    return new ResponseEntity<String>(String.format("Was the optional header present? %s!",(optionalHeader == null ? "No" : "Yes")),HttpStatus.OK);
}
```

### [Request and Response Body](https://www.baeldung.com/spring-request-response-body)
@RequestBody annotation maps the HttpRequest body to a transfer or domain object, enabling automatic deserialization of the inbound HttpRequest body onto a Java object
```
@PostMapping("/request")
public ResponseEntity postController(@RequestBody LoginForm loginForm) {
    exampleService.fakeAuthenticate(loginForm);
    return ResponseEntity.ok(HttpStatus.OK);
}
```
@ResponseBody annotation tells a controller that the object returned is automatically serialized into JSON and passed back into the HttpResponse object
```
@Controller
@RequestMapping("/post")
public class ExamplePostController {
    @Autowired
    ExampleService exampleService;
 
    @PostMapping("/response")
    @ResponseBody
    public ResponseTransfer postResponseController( @RequestBody LoginForm loginForm) {
        return new ResponseTransfer("Thanks For Posting!!!");
     }
}
```
Explicitly set the content type that the mapping method returns by produces
```
@PostMapping(value = "/content", produces = MediaType.APPLICATION_JSON_VALUE)
@ResponseBody
public ResponseTransfer postResponseJsonContent(@RequestBody LoginForm loginForm) {
    return new ResponseTransfer("JSON Content!");
}

@PostMapping(value = "/content", produces = MediaType.APPLICATION_XML_VALUE)
@ResponseBody
public ResponseTransfer postResponseXmlContent(@RequestBody LoginForm loginForm) {
    return new ResponseTransfer("XML Content!");
}
```
Aark these methods with @ResponseStatus to return a custom HTTP status.

### [ResponseEntity](https://www.baeldung.com/spring-response-entity)
ResponseEntity represents the whole HTTP response: status code, headers, and body.
```
@GetMapping("/hello")
ResponseEntity<String> hello() {
    return new ResponseEntity<>("Hello World!", HttpStatus.OK);
}

@GetMapping("/customHeader")
ResponseEntity<String> customHeader() {
    HttpHeaders headers = new HttpHeaders();
    headers.add("Custom-Header", "foo");        
    return new ResponseEntity<>("Custom header set", headers, HttpStatus.OK);
}

@GetMapping("/hello")
ResponseEntity<String> hello() {
    return ResponseEntity.ok("Hello World!");  //
}

@GetMapping("/customHeader")
ResponseEntity<String> customHeader() {
    return ResponseEntity.ok().header("Custom-Header", "foo").body("Custom header set");
}
```
Furthermore, ResponseEntity provides two nested builder interfaces: HeadersBuilder and its subinterface, BodyBuilder.
- BodyBuilder accepted();
- BodyBuilder badRequest();
- BodyBuilder created(java.net.URI location);
- BodyBuilder ok();
- HeadersBuilder<?> noContent();
- HeadersBuilder<?> notFound();

## [multipart File Upload](https://www.baeldung.com/spring-file-upload)
May need Apache commons-fileupload Commons IO, See [Guides](https://spring.io/guides/gs/uploading-files/)
```
<dependency>
	<groupId>commons-fileupload</groupId>
	<artifactId>commons-fileupload</artifactId>
	<version>1.3.1</version>
</dependency>
<dependency>
	<groupId>commons-io</groupId>
	<artifactId>commons-io</artifactId>
	<version>2.4</version>
</dependency>
```
In application.properties, control whether fileuploading is enabled, the maximum file upload size, and the location:
```
spring.servlet.multipart.enabled=true

spring.servlet.multipart.max-file-size=128KB
spring.servlet.multipart.max-request-size=128KB

spring.servlet.multipart.location=${java.io.tmpdir}
```
- Upload file
Build a form use an HTML input tag with type='file', set the encoding attribute of the form to multipart/form-data:
```
<form:form method="POST" action="/spring-mvc-xml/uploadFile" enctype="multipart/form-data">
    <table>
        <tr>
            <td><form:label path="file">Select a file to upload</form:label></td>
            <td><input type="file" name="file" /></td>
        </tr>
        <tr>
            <td><input type="submit" value="Submit" /></td>
        </tr>
    </table>
</form>
```
In the controller, use a MultipartFile variable to store the uploaded file
```
@RequestMapping(value = "/uploadFile", method = RequestMethod.POST)
public String submit(@RequestParam("file") MultipartFile file, ModelMap modelMap) {
    modelMap.addAttribute("file", file);    
    return "fileUploadView";
}

private void storeUploadFile(MultipartFile file)
{
    InputStream in = file.getInputStream();
    File currDir = new File(".");
    String path = currDir.getAbsolutePath();
    fileLocation = path.substring(0, path.length() - 1) + file.getOriginalFilename();
    FileOutputStream f = new FileOutputStream(fileLocation);
    int ch = 0;
    while ((ch = in.read()) != -1) {
        f.write(ch);
    }
    f.flush();
    f.close();
}
```
- Upload Multiple Files
```
<form:form method="POST" action="/spring-mvc-java/uploadMultiFile" enctype="multipart/form-data">
    <table>
        <tr>
            <td>Select a file to upload</td>
            <td><input type="file" name="files" /></td>
        </tr>
        <tr>
            <td>Select a file to upload</td>
            <td><input type="file" name="files" /></td>
        </tr>
        <tr>
            <td>Select a file to upload</td>
            <td><input type="file" name="files" /></td>
        </tr>
        <tr>
            <td><input type="submit" value="Submit" /></td>
        </tr>
    </table>
</form:form>
```
In Controller, use an array of MultipartFile
```
@RequestMapping(value = "/uploadMultiFile", method = RequestMethod.POST)
public String submit(@RequestParam("files") MultipartFile[] files, ModelMap modelMap) {
    modelMap.addAttribute("files", files);
    return "fileUploadView";
}
```

- Uploading Files With Additional Form Data
```
<form:form method="POST" 
  action="/spring-mvc-java/uploadFileWithAddtionalData"
  enctype="multipart/form-data">
    <table>
        <tr>
            <td>Name</td>
            <td><input type="text" name="name" /></td>
        </tr>
        <tr>
            <td>Email</td>
            <td><input type="text" name="email" /></td>
        </tr>
        <tr>
            <td>Select a file to upload</td>
            <td><input type="file" name="file" /></td>
        </tr>
        <tr>
            <td><input type="submit" value="Submit" /></td>
        </tr>
    </table>
</form:form>
```
In the controller, get all the form data using the @RequestParam annotation:
```
@PostMapping("/uploadFileWithAddtionalData")
public String submit( @RequestParam MultipartFile file, @RequestParam String name, @RequestParam String email, ModelMap modelMap) {
    modelMap.addAttribute("name", name);
    modelMap.addAttribute("email", email);
    modelMap.addAttribute("file", file);
    return "fileUploadView";
}
```
- Ancapsulate all the form fields in a model class and use @ModelAttribute annotation in the controller
```
public class FormDataWithFile { 
    private String name;
    private String email;
    private MultipartFile file;
    
    // standard getters and setters
}

@PostMapping("/uploadFileModelAttribute")
public String submit(@ModelAttribute FormDataWithFile formDataWithFile, ModelMap modelMap) { 
    modelMap.addAttribute("formDataWithFile", formDataWithFile);
    return "fileUploadView";
}
``

## Data Binding from From
- One GET method to show the Form input page: Create ModelAttribute object and pass it to page
- One POST method to`handle the Inputs from Form (ModelAttribute)
- Tutorial:
    - [Spring MVC and Thymeleaf](https://www.thymeleaf.org/doc/articles/springmvcaccessdata.html)
    - [Spring MVC and Thymelead Tutorial](https://www.thymeleaf.org/doc/tutorials/2.1/thymeleafspring.html)
    - [Spring Form Guidline](https://spring.io/guides/gs/handling-form-submission/)
    - [*HTML Form Handling in Thymeleaf](https://attacomsian.com/blog/spring-boot-thymeleaf-form-handling)
    - [Spring Boot + Thymeleaf HTML Form Handling](https://medium.com/@grokwich/spring-boot-thymeleaf-html-form-handling-762ef0d51327)
    - [Spring Thymeleaf](https://stackoverflow.com/questions/39596933/spring-boot-thymeleaf-form-binding)
    - [Bind Fixed Length](https://www.baeldung.com/thymeleaf-list)
    - [Spring Boot Thymeleaf Form Handling](https://www.codejava.net/frameworks/spring-boot/spring-boot-thymeleaf-form-handling-tutorial)
- Model    
```
public class Greeting {
  private long id;
  private String content;

  public long getId() {
    return id;
  }

  public void setId(long id) {
    this.id = id;
  }

  public String getContent() {
    return content;
  }

  public void setContent(String content) {
    this.content = content;
  }
}
```
- Controller
```
@Controller
public class GreetingController {
  @GetMapping("/greeting")
  public String greetingForm(Model model) {
    model.addAttribute("greeting", new Greeting());   # create ModelAttribute object
    return "greeting";
  }

  @PostMapping("/greeting")
  public String greetingSubmit(@ModelAttribute Greeting greeting, Model model) {
    model.addAttribute("greeting", greeting);
    return "result";
  }
}
```
- Form page: th:object is the model attribute to be binding, and td:field is the individual field.
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
Thymeleaf provides several special attributes to work with HTML forms:
- th:object — Used for specifying a model attribute that acts as a command object.
- th:field — Used for binding HTML form elements with a property in the form-backing bean.
- th:errors — An attribute that holds all form validation errors.
- th:errorclass — Used for setting a CSS class to a form input if that field has validation errors.


## Tips
- th:tag should be in <>:
```
working:  <div>Web Application. Passed spring parameter : <div th:text="${spring}"/></div>
Not work: <div>Web Application. Passed spring parameter : th:text="${spring}"</div>
```
