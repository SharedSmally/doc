# Web Session
Share the data for the same session:
- Using a scoped proxy
- Using the @SessionAttributes annotation

## Session Scoped proxy
- Create a session scoped proxy Bean:
```
@Bean
@Scope(value = WebApplicationContext.SCOPE_SESSION, proxyMode = ScopedProxyMode.TARGET_CLASS)
public TodoList todos() {
    return new TodoList();
}
```
- declare the bean as a dependency for the @Controller and inject it 
```
@Controller
@RequestMapping("/scopedproxy")
public class TodoControllerWithScopedProxy {
   private TodoList todos;

   @GetMapping("/form")
   public String showForm(Model model) {
     if (!todos.isEmpty()) {
        model.addAttribute("todo", todos.peekLast());
     } else {
        model.addAttribute("todo", new TodoItem());
     }
     return "scopedproxyform";
   }
}
```
## Using the @SessionAttributes Annotation
declared as a @ModelAttribute and specify the @SessionAttributes annotation to scope it to the session for the controller.

The first time our controller is accessed, Spring will instantiate an instance and place it in the Model. 
Of it is declared as @SessionAttributes, Spring will store the instance.
```
@ModelAttribute("todos")
public TodoList todos() {
    return new TodoList();
}

@Controller
@RequestMapping("/sessionattributes")
@SessionAttributes("todos")
public class TodoControllerWithSessionAttributes {
    // ... other methods
}

@GetMapping("/form")
public String showForm(Model model, @ModelAttribute("todos") TodoList todos) {
     if (!todos.isEmpty()) {
        model.addAttribute("todo", todos.peekLast());
    } else {
        model.addAttribute("todo", new TodoItem());
    }
    return "sessionattributesform";
}
```
@ModelAttribute annotated method argument is resolved as follows:
- Retrieve from model object if it is present (normally added via @ModelAttribute annotated methods)
- Retrieve from HTTP session by using @SessionAttributes.
- Create using URI path variable that matches the @ModelAttribute name through a converter
- Create using default constructor and add it to Model.

A handler class can be annotated with @SessionAttributes with a list of names as its arguments. This is to instruct Spring to persist (in session) those data items present in the model data which match the names specified in @SessionAttributes annotation.

