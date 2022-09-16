# Java Lamda
- [Java Lamda](https://docs.oracle.com/javase/tutorial/java/javaOO/lambdaexpressions.html)
- [Function Interface](https://docs.oracle.com/javase/8/docs/api/java/util/function/package-summary.html)
```
Function<T,R>: R apply(T t)
Predicate<T>: boolean	test(T t) 	
Consumer<T>: void accept(T t)
Supplier<T>: T get()

BiConsumer<T,U> : void accept(T t, U u)	
BiFunction<T,U,R>: R apply(T t, U u) 	
BiPredicate<T,U>: boolean 	test(T t, U u);  negate(); and/or(BiPredicate<T,U> other) 	

BinaryOperator<T>: extends BiFunction<T,T,T>
UnaryOperator<T>: extends Function<T,T>
xxxFunctor
```
A lambda expression is a short block of code which takes in parameters and returns a value. Lambda expressions are similar to methods, 
but they do not need a name and they can be implemented right in the body of a method.

```
parameter -> expression
(parameter1, parameter2) -> expression
(parameter1, parameter2) -> { code block }
```
Sample
```
   ArrayList<Integer> numbers = new ArrayList<Integer>();
   numbers.forEach( (n) -> { System.out.println(n); } );

   Consumer<Integer> method = (n) -> { System.out.println(n); };
   numbers.forEach( method );
```
Function Interface: with one method
```
interface StringFunction {
  String run(String str);
}

public class Main {
  public static void main(String[] args) {
    StringFunction exclaim = (s) -> s + "!";
    StringFunction ask = (s) -> s + "?";
    printFormatted("Hello", exclaim);
    printFormatted("Hello", ask);
  }
  public static void printFormatted(String str, StringFunction format) {
    String result = format.run(str);
    System.out.println(result);
  }
}

Function<String,String> mapper = String::toUpperCase;
     // Assignment context
     Predicate<String> p = String::isEmpty;

     // Method invocation context
     stream.filter(e -> e.getSize() > 10)...

     // Cast context
     stream.map((ToIntFunction) e -> e.getSize())...
```
