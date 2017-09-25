
### tips:
- [Generate a Java thread dump](https://access.redhat.com/solutions/18178): when java app is stucked, the command _kill -3_ will show the stack of the java app.

### Java Type vs Class:
- A type is either a class (including an enum constant), an interface, a primitive, or an array.
- A class is a type with constructors, fields, methods, annotations,
  
```
static Class<?>	forName(String className)
static Class<?>	forName(String name, boolean initialize, ClassLoader loader)

String	getCanonicalName()
ClassLoader	getClassLoader()
Class<?>[]	getClasses()
Class<?>	getComponentType()
Class<?>[]	getDeclaredClasses()
Class<?>	getDeclaringClass()
Class<?>	getEnclosingClass()
Class<?>[]	getInterfaces()

Constructor<T>	getConstructor(Class<?>... parameterTypes)
Constructor<?>[]	getConstructors()
Constructor<T>	getDeclaredConstructor(Class<?>... parameterTypes)
Constructor<?>[]	getDeclaredConstructors()
Constructor<?>	getEnclosingConstructor()

Annotation[]	getDeclaredAnnotations()
<A extends Annotation> A	getAnnotation(Class<A> annotationClass)
Annotation[]	getAnnotations()

Field	getDeclaredField(String name)
Field[]	getDeclaredFields()
Field	getField(String name)
Field[]	getFields()

Method	getDeclaredMethod(String name, Class<?>... parameterTypes)
Method[]	getDeclaredMethods()
Method	getEnclosingMethod()
Method	getMethod(String name, Class<?>... parameterTypes)
Method[]	getMethods()

Type[]	getGenericInterfaces()
Type	getGenericSuperclass()

T[]	getEnumConstants()
```
- An interface is a type. A primitive is a type. An array is a type.
