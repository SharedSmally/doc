# CORE Resources

## Resources
### Resource 
```
public interface Resource extends InputStreamSource {
    boolean exists();
    boolean isOpen();
    URL getURL() throws IOException;
    File getFile() throws IOException;
    Resource createRelative(String relativePath) throws IOException;
    String getFilename();
    String getDescription();
}

public interface InputStreamSource {
    InputStream getInputStream() throws IOException;
}
```
Resource is used to access to low-level resources. The Built-in implementations:
- UrlResource: accessible with a URL, such as files(file:), an HTTP target(http:), an FTP target(ftp:), relative in classpath(classpath:), and others
- ClassPathResource
- FileSystemResource
- ServletContextResource
- InputStreamResource
- ByteArrayResource

### ResourceLoader
```
public interface ResourceLoader {
    Resource getResource(String location);
}
```
All application contexts implement the ResourceLoader interface, so it may be used to obtain Resource instances.
- ClassPathXmlApplicationContext returns a ClassPathResource
- FileSystemXmlApplicationContext returns a FileSystemResource
- WebApplicationContext returns a ServletContextResource. 

The strategy for converting String objects to Resource objects:

| Prefix |	Example | 	Explanation |
| :------------- | :----------: | -----------: |
| classpath: | classpath:com/myapp/config.xml | Loaded from the classpath.|
| file: |  file:///data/config.xml | Loaded as a URL from the filesystem.|
| http: | https://myserver/logo.png | Loaded as a URL. |
| (none) | /data/config.xml | Depends on the underlying ApplicationContext.|

### ResourceLoaderAware
 A special callback interface which identifies components that expect to be provided with a ResourceLoader reference.
 ```
 public interface ResourceLoaderAware {
    void setResourceLoader(ResourceLoader resourceLoader);
}
 ```
When a class implements ResourceLoaderAware and is deployed into an application context as a Spring-managed bean, it is recognized by the application context. The application context then invokes setResourceLoader(ResourceLoader), supplying itself as the argument. The constructor and byType autowiring modes via @Autowired can provide a ResourceLoader for either a constructor argument or a setter method parameter, respectively.

The bean could also implement the ApplicationContextAware interface ato get the application context directly.


## Validation / Data Binding / Type Conversion
The Validator and the DataBinder make up the validation package. DataBinder and BeanWrapper use PropertyEditorSupport to parse and format property values. core.convert package provides a general type conversion facility, and a higher-level format package for formatting UI field values.

### Validator
Validator is used to validate objects:
```
public class Person {
    private String name;
    private int age;
}
public class PersonValidator implements Validator {
     // validates only Person instances
    public boolean supports(Class clazz) {
        return Person.class.equals(clazz);
    }
    public void validate(Object obj, Errors e) {
        ValidationUtils.rejectIfEmpty(e, "name", "name.empty");
        Person p = (Person) obj;
        if (p.getAge() < 0) {
            e.rejectValue("age", "negativevalue");
        } else if (p.getAge() > 110) {
            e.rejectValue("age", "too.darn.old");
        }
    }
}
```
Validate member
```
public class CustomerValidator implements Validator {
    private final Validator addressValidator;
    
    public CustomerValidator(Validator addressValidator) {
        if (addressValidator == null) {
            throw new IllegalArgumentException("The supplied [Validator] is required and must not be null.");
        }
        if (!addressValidator.supports(Address.class)) {
            throw new IllegalArgumentException("The supplied [Validator] must support the validation of [Address] instances.");
        }
        this.addressValidator = addressValidator;
    }

    //validates Customer instances, and any subclasses of Customer too
    public boolean supports(Class clazz) {
        return Customer.class.isAssignableFrom(clazz);
    }

    public void validate(Object target, Errors errors) {
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "firstName", "field.required");
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "surname", "field.required");
        Customer customer = (Customer) target;
        try {
            errors.pushNestedPath("address");
            ValidationUtils.invokeValidator(this.addressValidator, customer.getAddress(), errors);
        } finally {
            errors.popNestedPath();
        }
    }
}
```

