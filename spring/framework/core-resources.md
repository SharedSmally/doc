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

## [BeanWrapper](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/BeanWrapper.html) and [BeanWrapperImpl](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/BeanWrapperImpl.html)

BeanWrapper can set and get property values (individually or in bulk), get property descriptors, and query properties, support for nested properties, enabling the setting of properties on sub-properties to an unlimited depth, add standard JavaBeans PropertyChangeListeners and VetoableChangeListeners. support for setting indexed properties.
```
BeanWrapper company = new BeanWrapperImpl(new Company());
company.setPropertyValue("name", "Some Company Inc.");
PropertyValue value = new PropertyValue("name", "Some Company Inc.");
company.setPropertyValue(value);

BeanWrapper jim = new BeanWrapperImpl(new Employee());
jim.setPropertyValue("name", "Jim Stravinsky");
company.setPropertyValue("managingDirector", jim.getWrappedInstance());

Float salary = (Float) company.getPropertyValue("managingDirector.salary");
```

### PropertyEditor
Spring uses PropertyEditor to effect the conversion between an Object and a String. Sprint Built-in PropertyEditors:
- ByteArrayPropertyEditor*: Editor for byte arrays. * means registered by BeanWrapperImpl.
- ClassEditor*: Parses Strings that represent classes to actual classes and vice-versa.
- CustomBooleanEditor*: Customizable property editor for Boolean properties.
- CustomCollectionEditor: Property editor for collections, converting any source Collection to a given target Collection type.
- CustomDateEditor: Customizable property editor for java.util.Date, supporting a custom DateFormat. 
- CustomNumberEditor*:  Customizable property editor for any Number subclass, such as Integer, Long, Float, or Double.
- FileEditor*: Resolves strings to java.io.File objects. 
- InputStreamEditor*:  One-way property editor that can take a string and produce an InputStream.
- LocaleEditor*: resolve strings to Locale objects and vice-versa .
- PatternEditor: Can resolve strings to java.util.regex.Pattern objects and vice-versa.
- PropertiesEditor*: Can convert strings to Properties objects. 
- StringTrimmerEditor: Property editor that trims strings. 
- URLEditor*:  Can resolve a string representation of a URL to an actual URL object.

Spring uses the java.beans.PropertyEditorManager to set the search path for property editors that might be needed

For customized PropertyEditor:
```
public class ExoticTypeEditor extends PropertyEditorSupport {
    public void setAsText(String text) {
        setValue(new ExoticType(text.toUpperCase()));
    }
}
```

To register property editor Using PropertyEditorRegistrar and PropertyEditorRegistry:
```
public final class CustomPropertyEditorRegistrar implements PropertyEditorRegistrar {
    public void registerCustomEditors(PropertyEditorRegistry registry) {
        // expected the new PropertyEditor instances are created
        registry.registerCustomEditor(ExoticType.class, new ExoticTypeEditor());
        // you could register as many custom property editors as are required here...
    }
}
```

```
public final class RegisterUserController extends SimpleFormController {
    private final PropertyEditorRegistrar customPropertyEditorRegistrar;
    public RegisterUserController(PropertyEditorRegistrar propertyEditorRegistrar) {
        this.customPropertyEditorRegistrar = propertyEditorRegistrar;
    }

    protected void initBinder(HttpServletRequest request, ServletRequestDataBinder binder) throws Exception {
        this.customPropertyEditorRegistrar.registerCustomEditors(binder);
    }

    // other methods to do with registering a User
}
```

## Type Conversion
```
package org.springframework.core.convert.converter;

public interface Converter<S, T> {
    T convert(S source);
}
```
Several converter implementations are provided in the core.convert.support package:
```
package org.springframework.core.convert.support;

final class StringToInteger implements Converter<String, Integer> {
    public Integer convert(String source) {
        return Integer.valueOf(source);
    }
}
```
Using ConverterFactory when need to centralize the conversion logic:
```
package org.springframework.core.convert.converter;

public interface ConverterFactory<S, R> {
    <T extends R> Converter<S, T> getConverter(Class<T> targetType);
}
```
Using GenericConverter when require a sophisticated Converter implementation:
```
package org.springframework.core.convert.converter;

public interface GenericConverter {
    public Set<ConvertiblePair> getConvertibleTypes();
    Object convert(Object source, TypeDescriptor sourceType, TypeDescriptor targetType);
}
```
Using ConditionalGenericConverter when a Converter to run only if a specific condition holds true:
```
public interface ConditionalConverter {
    boolean matches(TypeDescriptor sourceType, TypeDescriptor targetType);
}

public interface ConditionalGenericConverter extends GenericConverter, ConditionalConverter {
}
```
### ConversionService 
ConversionService defines a unified API for executing type conversion logic at runtime:
```
package org.springframework.core.convert;

public interface ConversionService {
    boolean canConvert(Class<?> sourceType, Class<?> targetType);
    <T> T convert(Object source, Class<T> targetType);
    boolean canConvert(TypeDescriptor sourceType, TypeDescriptor targetType);
    Object convert(Object source, TypeDescriptor sourceType, TypeDescriptor targetType);
}
```
Most ConversionService (in core.convert.support) implementations implement ConverterRegistry, which provides an SPI for registering converters. GenericConversionService is the general-purpose implementation suitable for use in most environments. ConversionServiceFactory provides a convenient factory for creating common ConversionService configurations.
```
@Service
public class MyService {
    public MyService(ConversionService conversionService) {
        this.conversionService = conversionService;
    }

    public void doIt() {
        this.conversionService.convert(...)
    }
}
```

## Formatter
Specialized to parse and print localized field values:
```
package org.springframework.format;

public interface Formatter<T> extends Printer<T>, Parser<T> {
}

public interface Printer<T> {
    String print(T fieldValue, Locale locale);
}

public interface Parser<T> {
    T parse(String clientValue, Locale locale) throws ParseException;
}
```
Sample:
```
package org.springframework.format.datetime;

public final class DateFormatter implements Formatter<Date> {
    private String pattern;

    public DateFormatter(String pattern) {
        this.pattern = pattern;
    }

    public String print(Date date, Locale locale) {
        if (date == null) {  return "";   }
        return getDateFormat(locale).format(date);
    }

    public Date parse(String formatted, Locale locale) throws ParseException {
        if (formatted.length() == 0) { return null; }
        return getDateFormat(locale).parse(formatted);
    }

    protected DateFormat getDateFormat(Locale locale) {
        DateFormat dateFormat = new SimpleDateFormat(this.pattern, locale);
        dateFormat.setLenient(false);
        return dateFormat;
    }
}
```
Field formatting can be configured by field type or annotation. To bind an annotation to a Formatter, implement AnnotationFormatterFactory:
```
public interface AnnotationFormatterFactory<A extends Annotation> {
    Set<Class<?>> getFieldTypes();
    Printer<?> getPrinter(A annotation, Class<?> fieldType);
    Parser<?> getParser(A annotation, Class<?> fieldType);
}
```
Sample:
```
public final class NumberFormatAnnotationFormatterFactory implements AnnotationFormatterFactory<NumberFormat> {
    public Set<Class<?>> getFieldTypes() {
        return new HashSet<Class<?>>(asList(new Class<?>[] {
            Short.class, Integer.class, Long.class, Float.class,
            Double.class, BigDecimal.class, BigInteger.class }));
    }

    public Printer<Number> getPrinter(NumberFormat annotation, Class<?> fieldType) {
        return configureFormatterFrom(annotation, fieldType);
    }

    public Parser<Number> getParser(NumberFormat annotation, Class<?> fieldType) {
        return configureFormatterFrom(annotation, fieldType);
    }

    private Formatter<Number> configureFormatterFrom(NumberFormat annotation, Class<?> fieldType) {
        if (!annotation.pattern().isEmpty()) {
            return new NumberStyleFormatter(annotation.pattern());
        } else {
            Style style = annotation.style();
            if (style == Style.PERCENT) {
                return new PercentStyleFormatter();
            } else if (style == Style.CURRENCY) {
                return new CurrencyStyleFormatter();
            } else {
                return new NumberStyleFormatter();
            }
        }
    }
}
```
Use 
```
public class MyModel {
    @NumberFormat(style=Style.CURRENCY)
    private BigDecimal decimal;
    @DateTimeFormat(iso=ISO.DATE)
    private Date date;
}
```
### FormatterRegistry
The FormatterRegistry is an SPI for registering formatters and converters. FormattingConversionService is an implementation of FormatterRegistry suitable for most environments
```
public interface FormatterRegistry extends ConverterRegistry {
    void addFormatterForFieldType(Class<?> fieldType, Printer<?> printer, Parser<?> parser);
    void addFormatterForFieldType(Class<?> fieldType, Formatter<?> formatter);
    void addFormatterForFieldType(Formatter<?> formatter);
    void addFormatterForAnnotation(AnnotationFormatterFactory<?> factory);
}
```
### FormatterRegistrar
```
public interface FormatterRegistrar {
    void registerFormatters(FormatterRegistry registry);
}
```

### Configuring Formatting in Spring MVC
- org.springframework.format.datetime.standard.DateTimeFormatterRegistrar
- org.springframework.format.datetime.DateFormatterRegistrar
- org.springframework.format.datetime.joda.JodaTimeFormatterRegistrar for Joda-Time.
```
@Configuration
public class AppConfig {
    @Bean
    public FormattingConversionService conversionService() {
        // Use the DefaultFormattingConversionService but do not register defaults
        DefaultFormattingConversionService conversionService = new DefaultFormattingConversionService(false);

        // Ensure @NumberFormat is still supported
        conversionService.addFormatterForFieldAnnotation(new NumberFormatAnnotationFormatterFactory());

        // Register JSR-310 date conversion with a specific global format
        DateTimeFormatterRegistrar registrar = new DateTimeFormatterRegistrar();
        registrar.setDateFormatter(DateTimeFormatter.ofPattern("yyyyMMdd"));
        registrar.registerFormatters(conversionService);

        // Register date conversion with a specific global format
        DateFormatterRegistrar registrar = new DateFormatterRegistrar();
        registrar.setFormatter(new DateFormatter("yyyyMMdd"));
        registrar.registerFormatters(conversionService);

        return conversionService;
    }
}
```

### Bean Validation
```
public class PersonForm {
    @NotNull
    @Size(max=64)
    private String name;

    @Min(0)
    private int age;
}
```
###  Configuring a Bean Validation Provider
```
import org.springframework.validation.beanvalidation.LocalValidatorFactoryBean;

@Configuration
public class AppConfig {
    @Bean
    public LocalValidatorFactoryBean validator() {
        return new LocalValidatorFactoryBean();
    }
}
```
### Inject Validator
```
import javax.validation.Validator;
//import org.springframework.validation.Validator;

@Service
public class MyService {

    @Autowired
    private Validator validator;
}
```
### Configuring a DataBinder
```
Foo target = new Foo();
DataBinder binder = new DataBinder(target);
binder.setValidator(new FooValidator());

// bind to the target object
binder.bind(propertyValues);

// validate the target object
binder.validate();

// get BindingResult that includes any validation errors
BindingResult results = binder.getBindingResult();
```
