# Java Lamda Function

An interface with only single abstract method is called functional interface(or Single Abstract method interface), such as Runnable,....

## Syntax
Lambda expression only has body and parameter list: for Function interface implemented annonymous class
```
(parameter_list) -> {function_body}
```
Sample:
```
        b.addActionListener(new ActionListener(){  
          public void actionPerformed(ActionEvent e){  
    	     System.out.println("Hello World!"); 
          }  
       }); 
       
        b.addActionListener(e -> System.out.println("Hello World!")); 
```
- Java Lambda Expression with no parameter
```
@FunctionalInterface
interface MyFunctionalInterface {
    public String sayHello(); 	//A method with no parameter
}

public class Example {
   public static void main(String args[]) {        
    	MyFunctionalInterface msg = () -> { // lambda expression
    		return "Hello";
    	};
      System.out.println(msg.sayHello());
    }
}
```
- Java Lambda Expression with single parameter
```
@FunctionalInterface
interface MyFunctionalInterface {
    public int incrementByFive(int a); //A method with single parameter
}

public class Example {
   public static void main(String args[]) {
        // lambda expression with single parameter num
    	MyFunctionalInterface f = (num) -> num+5;
        System.out.println(f.incrementByFive(22));
    }
}
```
- Java Lambda Expression with Multiple Parameters
```
@FunctionalInterface
interface StringConcat {
    public String sconcat(String a, String b);
}
public class Example {
   public static void main(String args[]) {
        // lambda expression with multiple arguments
    	StringConcat s = (str1, str2) -> str1 + str2;
        System.out.println("Result: "+s.sconcat("Hello ", "World"));
    }
}
```
- 
```
import java.util.*;  
public class Example{  
    public static void main(String[] args) {       
       List<String> list=new ArrayList<String>();  
       list.add("Rick");  list.add("Negan");  list.add("Daryl");         
       list.add("Glenn"); list.add("Carl");                
       list.forEach(                     
           (name)->System.out.println(name) // lambda expression        
       );  
       
    }  
}

// forEach() of Iteratable:
default void forEach(Consumer<? super T> action)
Default implementation:
    for (T t : this)
         action.accept(t);
```

## Common Functions in  [java.util.function](https://docs.oracle.com/javase/8/docs/api/java/util/function/package-summary.html)

### UnaryFunctions
- UnaryOperator<T> 	Represents an operation on a single operand that produces a result of the same type as its operand.
```
@FunctionalInterface
public interface UnaryOperator<T> extends Function<T,T>        
```
- Function<T,R> 	Represents a function that accepts one argument and produces a result.
```
@FunctionalInterface
public interface Function<T,R> {
        R apply(T t)
}        
```
- Consumer<T> 	        Represents an operation that accepts a single input argument and returns no result.
```
@FunctionalInterface
public interface Consumer<T> {        
    void accept(T t)        
}
```
- Supplier<T> 	        Represents a supplier of results.
```
@FunctionalInterface
public interface Supplier<T> {
        T get()        
}        
```        
- Predicate<T> 	        Represents a predicate (boolean-valued function) of one argument.
```
@FunctionalInterface
public interface Predicate<T> {
    boolean test(T t)        
}
```
### Bi-Functions
- BiConsumer<T,U> 	Represents an operation that accepts two input arguments and returns no result.
```
@FunctionalInterface
public interface BiConsumer<T,U> {
        void 	accept(T t, U u)
}
```
- BiFunction<T,U,R> 	Represents a function that accepts two arguments and produces a result.
```
@FunctionalInterface
public interface BiFunction<T,U,R> {
        R 	apply(T t, U u)
}
```
- BiPredicate<T,U> 	Represents a predicate (boolean-valued function) of two arguments.
```
@FunctionalInterface
public interface BiPredicate<T,U> {
        boolean 	test(T t, U u)
}        
```        
- BinaryOperator<T> 	Represents an operation upon two operands of the same type, producing a result of the same type as the operands.
```
@FunctionalInterface
public interface BinaryOperator<T> extends BiFunction<T,T,T>        
```        

###  Bool Functions      
- BooleanSupplier 	Represents a supplier of boolean-valued results.        

###  Double Functions
- DoubleBinaryOperator 	Represents an operation upon two double-valued operands and producing a double-valued result.
- DoubleConsumer 	        Represents an operation that accepts a single double-valued argument and returns no result.
- DoubleFunction<R> 	Represents a function that accepts a double-valued argument and produces a result.
- DoublePredicate 	Represents a predicate (boolean-valued function) of one double-valued argument.
- DoubleSupplier 	        Represents a supplier of double-valued results.
- DoubleToIntFunction 	Represents a function that accepts a double-valued argument and produces an int-valued result.
- DoubleToLongFunction 	Represents a function that accepts a double-valued argument and produces a long-valued result.
- DoubleUnaryOperator 	Represents an operation on a single double-valued operand that produces a double-valued result.

###  Int Functions
- IntBinaryOperator 	Represents an operation upon two int-valued operands and producing an int-valued result.
- IntConsumer 	        Represents an operation that accepts a single int-valued argument and returns no result.
- IntFunction<R> 	        Represents a function that accepts an int-valued argument and produces a result.
- IntPredicate 	        Represents a predicate (boolean-valued function) of one int-valued argument.
- IntSupplier 	        Represents a supplier of int-valued results.
- IntToDoubleFunction 	Represents a function that accepts an int-valued argument and produces a double-valued result.
- IntToLongFunction 	Represents a function that accepts an int-valued argument and produces a long-valued result.
- IntUnaryOperator 	Represents an operation on a single int-valued operand that produces an int-valued result.

###  Long Functions
- LongBinaryOperator 	Represents an operation upon two long-valued operands and producing a long-valued result.
- LongConsumer 	        Represents an operation that accepts a single long-valued argument and returns no result.
- LongFunction<R> 	Represents a function that accepts a long-valued argument and produces a result.
- LongPredicate 	        Represents a predicate (boolean-valued function) of one long-valued argument.
- LongSupplier 	        Represents a supplier of long-valued results.
- LongToDoubleFunction 	Represents a function that accepts a long-valued argument and produces a double-valued result.
- LongToIntFunction 	Represents a function that accepts a long-valued argument and produces an int-valued result.
- LongUnaryOperator 	Represents an operation on a single long-valued operand that produces a long-valued result.

###  Object Consumer Functions
- ObjDoubleConsumer<T> 	Represents an operation that accepts an object-valued and a double-valued argument, and returns no result.
- ObjIntConsumer<T> 	Represents an operation that accepts an object-valued and a int-valued argument, and returns no result.
- ObjLongConsumer<T> 	Represents an operation that accepts an object-valued and a long-valued argument, and returns no result.

###  Convert Functions
- ToDoubleBiFunction<T,U> Represents a function that accepts two arguments and produces a double-valued result.
- ToDoubleFunction<T> 	Represents a function that produces a double-valued result.
- ToIntBiFunction<T,U> 	Represents a function that accepts two arguments and produces an int-valued result.
- ToIntFunction<T> 	Represents a function that produces an int-valued result.
- ToLongBiFunction<T,U> 	Represents a function that accepts two arguments and produces a long-valued result.
- ToLongFunction<T> 	Represents a function that produces a long-valued result.

        
