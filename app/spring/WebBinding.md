# Web Data Binding
## Using Enums as Request Parameters
- Define enum
```
public enum Modes {
    ALPHA, BETA;
}
```
- Define Converter
```
public class StringToEnumConverter implements Converter<String, Modes> {
    @Override
    public Modes convert(String from) {
        return Modes.valueOf(from);
    }
}
```
- Register Converter:
```
@Configuration
public class WebConfig implements WebMvcConfigurer {
    @Override
    public void addFormatters(FormatterRegistry registry) {
        registry.addConverter(new StringToEnumConverter());
    }
}
```
- Use Eum as a RequestParameter:
```
@GetMapping
public ResponseEntity<Object> getStringToMode(@RequestParam("mode") Modes mode) {
    // ...
}
@GetMapping("/entity/findbymode/{mode}")
public GenericEntity findByEnum(@PathVariable("mode") Modes mode) {
    // ...
}
```

## Binding a Hierarchy of Object
- Definee hierarchies
```
public abstract class AbstractEntity {
    long id;
    public AbstractEntity(long id){
        this.id = id;
    }
}

public class Foo extends AbstractEntity {
    private String name;
    
    // standard constructors, getters, setters
}

public class Bar extends AbstractEntity {
    private int value;
    
    // standard constructors, getters, setters
}
```
- Define Converter
```
public class StringToAbstractEntityConverterFactory implements ConverterFactory<String, AbstractEntity>{
    @Override
    public <T extends AbstractEntity> Converter<String, T> getConverter(Class<T> targetClass) {
        return new StringToAbstractEntityConverter<>(targetClass);
    }

    private static class StringToAbstractEntityConverter<T extends AbstractEntity> implements Converter<String, T> {
        private Class<T> targetClass;

        public StringToAbstractEntityConverter(Class<T> targetClass) {
            this.targetClass = targetClass;
        }

        @Override
        public T convert(String source) {
            long id = Long.parseLong(source);
            if(this.targetClass == Foo.class) {
                return (T) new Foo(id);
            }
            else if(this.targetClass == Bar.class) {
                return (T) new Bar(id);
            } else {
                return null;
            }
        }
    }
}
```
- Register ConverterFactory
```
@Configuration
public class WebConfig implements WebMvcConfigurer {
    @Override
    public void addFormatters(FormatterRegistry registry) {
        registry.addConverterFactory(new StringToAbstractEntityConverterFactory());
    }
}
```
- Use converter
```
@RestController
@RequestMapping("/string-to-abstract")
public class AbstractEntityController {
    @GetMapping("/foo/{foo}")
    public ResponseEntity<Object> getStringToFoo(@PathVariable Foo foo) {
        return ResponseEntity.ok(foo);
    }
    
    @GetMapping("/bar/{bar}")
    public ResponseEntity<Object> getStringToBar(@PathVariable Bar bar) {
        return ResponseEntity.ok(bar);
    }
}
```
## Binding Domain Objects

## InitBinding: customize the request sent to Controller
- Model
```
import java.security.KeyStore.PrivateKeyEntry;
import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

public class Student{
  private String Id;
  private String firstName;
 
  @NotNull(message="is required")
  @Size(min=1,message="is required")
  private String lastName; // validation done to check if lastname is NULL
 
  @Max(value=10,message="Value should between 0 and 10")
  @Min(value=0,message="Value should between 0 and 10")
  private String standard;
  private String Age;
}
```
- InitBinder method in Controller: with WebDataBinder as the parameter to initialize WebDataBinder to preprocess the request
```
@Controller
class StudentController {
   @InitBinder
   public void initBinder(WebDataBinder dataBinder) {
       StringTrimmerEditor stringTrimmerEditor = new StringTrimmerEditor(true);
       dataBinder.registerCustomEditor(String.class, stringTrimmerEditor);
   }
}
```
The @InitBinder annotated methods will get called on each HTTP request if we don't specify the 'value' element of this annotation.

Each time this method is called a new instance of WebDataBinder is passed to it.

To be more specific about which objects our InitBinder method applies to, we can supply 'value' element of the annotation @InitBinder. The 'value' element is a single or multiple names of command/form attributes and/or request parameters that this init-binder method is supposed to apply to. 

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
        binder.registerCustomEditor(Date.class, "dateOfBirth",
                                    new CustomDateEditor(dateFormatter, true));
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

## Validator
```
import org.springframework.stereotype.Component;
import org.springframework.validation.Errors;
import org.springframework.validation.ValidationUtils;
import org.springframework.validation.Validator;

@Component
public class UserValidator implements Validator  {
	@Override
	public boolean supports(Class<?> clazz) {
		return User.class.isAssignableFrom(clazz);
	}
	@Override
	public void validate(Object target, Errors errors) {
		User user = (User)target;
		ValidationUtils.rejectIfEmptyOrWhitespace(errors, "name", "","Username is empty");
		ValidationUtils.rejectIfEmptyOrWhitespace(errors, "password", "", "Password is empty");
		if (user.getName().length()<5) {
			errors.rejectValue("name","", "Username length is less than 5");
		}
	}
} 
```
Use WebDataBinder in @InitBinder to binds request parameter to JavaBean objects. It provides methods to assign the validator and converter classes. 

