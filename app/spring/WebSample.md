
## Controller
```
@Controller
class Ex1Controller {
    @GetMapping("/findbydate/{date}")
    public GenericEntity findByDate(@PathVariable("date") LocalDateTime date) {
        return ...;
    }
}
```
## @RequestParam vs @PathVariable
Both are used to extract values from the request, and can be optional:
- @RequestParams extract values from the query string,it is URL decoded
- @PathVariables extract values from the URI path,it’s not encoded.
For @PathVariable
```
@GetMapping("/foos/{id}")
@ResponseBody
public String getFooById(@PathVariable String id) {
    return "ID: " + id;
}
-----------------
http://localhost:8080/foos/abc
```
optionally:
```
@GetMapping({"/myfoos/optional", "/myfoos/optional/{id}"})
@ResponseBody
public String getFooByOptionalId(@PathVariable(required = false) String id){
    return "ID: " + id;
}
```
For @RequestParam:
```
@GetMapping("/foos")
@ResponseBody
public String getFooByIdUsingQueryParam(@RequestParam String id) {
    return "ID: " + id;
}
-----------------
http://localhost:8080/foos?id=abc
```
## @Matrix Variables
Appear in any part of the path: “=” is used for giving values and ‘;’ for delimiting each matrix variable. 
On the same path, the same variable name can be repeated or separate different values using the character comma(‘,’).

```
http://localhost:8080/spring-mvc-java-2/employeeArea/workingArea=rh,informatics,admin
http://localhost:8080/spring-mvc-java-2/employeeArea/workingArea=rh;workingArea=informatics;workingArea=admin
http://localhost:8080/spring-mvc-java-2/employees/John;beginContactNumber=22001

@RequestMapping(value = "/employees/{name}", method = RequestMethod.GET)
@ResponseBody
public ResponseEntity<List<Employee>> getEmployeeByNameAndBeginContactNumber(
  @PathVariable String name, @MatrixVariable String beginContactNumber) {
    List<Employee> employeesList = new ArrayList<Employee>();
    ...
    return new ResponseEntity<>(employeesList, HttpStatus.OK);
}
```
- Binding All Matrix Variables
```
http://localhost:8080/spring-mvc-java-2/employeeData/id=1;name=John;contactNumber=2200112334

@GetMapping("employeeData/{employee}")
@ResponseBody
public ResponseEntity<Map<String, String>> getEmployeeData(
  @MatrixVariable Map<String, String> matrixVars) {
    return new ResponseEntity<>(matrixVars, HttpStatus.OK);
}
```
Another example:
```
http://localhost:8080/spring-mvc-java-2/companyEmployee/id=2;name=Xpto/employeeData/id=1;name=John;contactNumber=2200112334

@RequestMapping(value = "/companyEmployee/{company}/employeeData/{employee}", method = RequestMethod.GET)
@ResponseBody
public ResponseEntity<Map<String, String>> getEmployeeDataFromCompany(@MatrixVariable(pathVar="employee") Map<String, String> matrixVars) {
  ...
}
```
## @RequestAttribute
To bind a request attribute to a handler method parameter.
- @RequestParam: bind parameter values from 'query string' 
- @RequestAttribute: access objects which have been populated on the server-side but during the same HTTP request, populated in an interceptor or a filter.
```
public class MyCounterInterceptor extends HandlerInterceptorAdapter {
  private AtomicInteger counter = new AtomicInteger(0);
  @Override
  public boolean preHandle (HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
      request.setAttribute("visitorCounter", counter.incrementAndGet());
      return true;
  }
}

@Controller
public class ExampleController {
  @RequestMapping("/")
  @ResponseBody
  public String handle (@RequestAttribute("visitorCounter") Integer counter) {
      return String.format("Visitor number: %d", counter);
  }
}

@EnableWebMvc
@ComponentScan("com.logicbig.example")
public class AppConfig extends WebMvcConfigurerAdapter {
  @Override
  public void addInterceptors (InterceptorRegistry registry) {
      registry.addInterceptor(new MyCounterInterceptor());
  }
}
```
 
## @ModelAttribute
- Used at the method level
Indicates the purpose of that method is to add one or more model attributes. It has the same argument types as @RequestMapping methods but cannot be mapped directly to requests.
```
@ModelAttribute
public void addAttributes(Model model) {
    model.addAttribute("msg", "Welcome to the Netherlands!");
}
```
@ModelAttribute methods are invoked before the controller methods annotated with @RequestMapping are invoked. 

- As a Method Argument
Indicates the argument should be retrieved from the model. When not present, it should be first instantiated 
and then added to the model and once present in the model, the arguments fields should be populated from 
all request parameters that have matching names.
```
@RequestMapping(value = "/addEmployee", method = RequestMethod.POST)
public String submit(@ModelAttribute("employee") Employee employee) {
    // Code that uses the employee object

    return "employeeView";
}
```
It binds the form data with a bean. The controller annotated with @RequestMapping can have custom class argument(s) annotated with @ModelAttribute.

## Sample
```
@Controller
@ControllerAdvice
public class EmployeeController {
    private Map<Long, Employee> employeeMap = new HashMap<>();

    @RequestMapping(value = "/addEmployee", method = RequestMethod.POST)
    public String submit( @ModelAttribute("employee") Employee employee,
      BindingResult result, ModelMap model) {
        if (result.hasErrors()) {
            return "error";
        }
        model.addAttribute("name", employee.getName());
        model.addAttribute("id", employee.getId());

        employeeMap.put(employee.getId(), employee);

        return "employeeView";
    }

    @ModelAttribute
    public void addAttributes(Model model) {
        model.addAttribute("msg", "Welcome to the Netherlands!");
    }

 /**
   * This creates a new address object for the empty form and stuffs it into the model
   */
  @ModelAttribute("User")
  public User populateUser() {
    User user = new User();
    user.setFirstName("your first name");
    user.setLastName("your last name");
    return user;
  }

  @RequestMapping(value = PATH, method = RequestMethod.POST)
  public String addAddress(@ModelAttribute("user") User user, BindingResult result, Model model) {
    model.addAttribute("newUser", user);
    return WELCOME_VIEW;
  }
}
```
