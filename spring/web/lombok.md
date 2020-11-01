# Project Lombok
- [Web Site](https://projectlombok.org/): Version:(1.18.16)[https://projectlombok.org/download]
- [Introduction to project lombok](https://www.baeldung.com/intro-to-project-lombok)

## [Features](https://projectlombok.org/features/all)
- @NoArgsConstructor, @RequiredArgsConstructor and @AllArgsConstructor

- @Getter/@Setter
Anotate any field with @Getter and/or @Setter, to let lombok generate the default getter/setter automatically.

A default getter simply returns the field, and is named getFoo if the field is called foo (or isFoo if the field's type is boolean). A default setter is named setFoo if the field is called foo, returns void, and takes 1 parameter of the same type as the field. It simply sets the field to this value. 

The generated getter/setter method will be public unless you explicitly specify an AccessLevel, as shown in the example below. Legal access levels are PUBLIC, PROTECTED, PACKAGE, and PRIVATE. NONE to disable etter/setter generation for any field.

You can also put a @Getter and/or @Setter annotation on a class. In that case, it's as if you annotate all the non-static fields in that class with the annotation. 

```
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

public class GetterSetterExample {
  /**
   * Age of the person. Water is wet.
   * 
   * @param age New value for this person's age. Sky is blue.
   * @return The current value of this person's age. Circles are round.
   */
  @Getter @Setter private int age = 10;
  
  /**
   * Name of the person.
   * 
   * Changes the name of this person.
   * 
   * @param name The new value.
   */
  @Setter(AccessLevel.PROTECTED) private String name;
  
  @Override public String toString() {
    return String.format("%s (age: %d)", name, age);
  }
}
```

- @NonNull
On the parameter of a method or constructor to have lombok generate a null-check statement

The null-check looks like if (param == null) throw new NullPointerException("param is marked @NonNull but is null"); and will be inserted at the very top of your method. For constructors, the null-check will be inserted immediately following any explicit this() or super() calls.

If a null-check is already present at the top, no additional null-check will be generated. 
```
import lombok.NonNull;

public class NonNullExample extends Something {
  private String name;
  
  public NonNullExample(@NonNull Person person) {
    super("Hello");
    this.name = person.getName();
  }
}
```

@Cleanup

Ensure a given resource is automatically cleaned up before the code execution path exits the current scope: At the end of the scope, its close() is called. A cleanup method that takes 1 or more arguments cannot be called via @Cleanup. 
```
import lombok.Cleanup;
import java.io.*;

public class CleanupExample {
  public static void main(String[] args) throws IOException {
    @Cleanup InputStream in = new FileInputStream(args[0]);
    @Cleanup OutputStream out = new FileOutputStream(args[1]);
    @Cleanup("dispose") org.eclipse.swt.widgets.CoolBar bar = new CoolBar(parent, 0);
    byte[] b = new byte[10000];
    while (true) {
      int r = in.read(b);
      if (r == -1) break;
      out.write(b, 0, r);
    }
  }
}
```

- @ToString

Generate an implementation of the toString() method. By default, it'll print your class name, along with each field, in order, separated by commas. 

By default, all non-static fields will be printed. If you want to skip some fields, you can annotate these fields with @ToString.Exclude. 
```
import lombok.ToString;

@ToString
public class ToStringExample {
  private static final int STATIC_VAR = 10;
  private String name;
  private Shape shape = new Square(5, 10);
  private String[] tags;
  @ToString.Exclude private int id;
  
  public String getName() {
    return this.name;
  }
  
  @ToString(callSuper=true, includeFieldNames=true)
  public static class Square extends Shape {
    private final int width, height;
    
    public Square(int width, int height) {
      this.width = width;
      this.height = height;
    }
  }
}
```

- @EqualsAndHashCode

Generate implementations of the equals(Object other) and hashCode() methods.

By default, it'll use all non-static, non-transient fields, but can modify which fields are used by marking type members with @EqualsAndHashCode.Include or @EqualsAndHashCode.Exclude. Alternatively, can specify exactly which fields or methods to be used by marking them with @EqualsAndHashCode.Include and using @EqualsAndHashCode(onlyExplicitlyIncluded = true)
```
import lombok.EqualsAndHashCode;

@EqualsAndHashCode
public class EqualsAndHashCodeExample {
  private transient int transientVar = 10;
  private String name;
  private double score;
  @EqualsAndHashCode.Exclude private Shape shape = new Square(5, 10);
  private String[] tags;
  @EqualsAndHashCode.Exclude private int id;
  
  public String getName() {
    return this.name;
  }
  
  @EqualsAndHashCode(callSuper=true)
  public static class Square extends Shape {
    private final int width, height;
    
    public Square(int width, int height) {
      this.width = width;
      this.height = height;
    }
  }
}
```

@Data
@Data is a convenient shortcut annotation that bundles the features of @ToString, @EqualsAndHashCode, @Getter / @Setter and @RequiredArgsConstructor together.
```
import lombok.AccessLevel;
import lombok.Setter;
import lombok.Data;
import lombok.ToString;

@Data public class DataExample {
  private final String name;
  @Setter(AccessLevel.PACKAGE) private int age;
  private double score;
  private String[] tags;
  
  @ToString(includeFieldNames=true)
  @Data(staticConstructor="of")
  public static class Exercise<T> {
    private final String name;
    private final T value;
  }
}
```
@Value
@Value is the immutable variant of @Data; all fields are made private and final by default, and setters are not generated. 
```
import lombok.AccessLevel;
import lombok.experimental.NonFinal;
import lombok.experimental.Value;
import lombok.experimental.Wither;
import lombok.ToString;

@Value public class ValueExample {
  String name;
  @Wither(AccessLevel.PACKAGE) @NonFinal int age;
  double score;
  protected String[] tags;
  
  @ToString(includeFieldNames=true)
  @Value(staticConstructor="of")
  public static class Exercise<T> {
    String name;
    T value;
  }
}
```

@Builder

 @Builder lets you automatically produce the code required to have your class be instantiable with code such as:
Person.builder().name("Adam Savage").city("San Francisco").job("Mythbusters").job("Unchained Reaction").build();

@Builder can be placed on a class, or on a constructor, or on a method. While the "on a class" and "on a constructor" mode are the most common use-case, @Builder is most easily explained with the "method" use-case. 
```
import lombok.Builder;
import lombok.Singular;
import java.util.Set;

@Builder
public class BuilderExample {
  @Builder.Default private long created = System.currentTimeMillis();
  private String name;
  private int age;
  @Singular private Set<String> occupations;
}
```

@SneakyThrows
Ued to sneakily throw checked exceptions without actually declaring this in your method's throws clause
```
import lombok.SneakyThrows;

public class SneakyThrowsExample implements Runnable {
  @SneakyThrows(UnsupportedEncodingException.class)
  public String utf8ToString(byte[] bytes) {
    return new String(bytes, "UTF-8");
  }
  
  @SneakyThrows
  public void run() {
    throw new Throwable();
  }
}
```

@Synchronized

@Synchronized is a safer variant of the synchronized method modifier. Like synchronized, the annotation can be used on static and instance methods only. It operates similarly to the synchronized keyword, but it locks on different objects. The keyword locks on this, but the annotation locks on a field named $lock, which is private.
If the field does not exist, it is created for you. If you annotate a static method, the annotation locks on a static field named $LOCK instead. 
```
import lombok.Synchronized;

public class SynchronizedExample {
  private final Object readLock = new Object();
  
  @Synchronized
  public static void hello() {
    System.out.println("world");
  }
  
  @Synchronized
  public int answerToLife() {
    return 42;
  }
  
  @Synchronized("readLock")
  public void foo() {
    System.out.println("bar");
  }
}
```

@With
Immutable 'setters' - methods that create a clone but with one changed field.
```
import lombok.AccessLevel;
import lombok.NonNull;
import lombok.With;

public class WithExample {
  @With(AccessLevel.PROTECTED) @NonNull private final String name;
  @With private final int age;
  
  public WithExample(String name, int age) {
    if (name == null) throw new NullPointerException();
    this.name = name;
    this.age = age;
  }
}
```

- @Getter(lazy=true)
Generate a getter which will calculate a value once, the first time this getter is called, and cache it from then on
```
import lombok.Getter;

public class GetterLazyExample {
  @Getter(lazy=true) private final double[] cached = expensive();
  
  private double[] expensive() {
    double[] result = new double[1000000];
    for (int i = 0; i < result.length; i++) {
      result[i] = Math.asin(i);
    }
    return result;
  }
}
```

- @Log
Put the variant of @Log on theass to have a static final log field, initialized as is the commonly prescribed way for the logging framework, and then use to write log statements. 

    - @CommonsLog: Creates private static final org.apache.commons.logging.Log log = org.apache.commons.logging.LogFactory.getLog(LogExample.class); 
    - @Flogger:    Creates private static final com.google.common.flogger.FluentLogger log = com.google.common.flogger.FluentLogger.forEnclosingClass(); 
    - @JBossLog:   Creates private static final org.jboss.logging.Logger log = org.jboss.logging.Logger.getLogger(LogExample.class); 
    - @Log:        Creates private static final java.util.logging.Logger log = java.util.logging.Logger.getLogger(LogExample.class.getName()); 
    - @Log4j:      Creates private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LogExample.class); 
    - @Log4j2:     Creates private static final org.apache.logging.log4j.Logger log = org.apache.logging.log4j.LogManager.getLogger(LogExample.class); 
    - @Slf4j:      Creates private static final org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LogExample.class); 
    - @XSlf4j:     Creates private static final org.slf4j.ext.XLogger log = org.slf4j.ext.XLoggerFactory.getXLogger(LogExample.class); 
    - @CustomLog:  Creates private static final com.foo.your.Logger log = com.foo.your.LoggerFactory.createYourLogger(LogExample.class);
```
import lombok.extern.java.Log;
import lombok.extern.slf4j.Slf4j;

@Log
public class LogExample { 
  public static void main(String... args) {
    log.severe("Something's wrong here");
  }
}

@Slf4j
public class LogExampleOther {  
  public static void main(String... args) {
    log.error("Something else is wrong here");
  }
}

@CommonsLog(topic="CounterLog")
public class LogExampleCategory {
  public static void main(String... args) {
    log.error("Calling the 'CounterLog' with a message");
  }
}
```

