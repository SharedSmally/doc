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
    - [Pass parameters from Controller to View] (https://www.baeldung.com/spring-mvc-model-model-map-model-view) via Model, ModelMap and ModelView
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

## Request Mapping
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

# [RequestParam](https://www.baeldung.com/spring-request-param)
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

# PathVariable



## Tips
- th:tag should be in <>:
```
working:  <div>Web Application. Passed spring parameter : <div th:text="${spring}"/></div>
Not work: <div>Web Application. Passed spring parameter : th:text="${spring}"</div>
```
