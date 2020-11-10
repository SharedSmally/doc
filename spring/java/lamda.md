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
