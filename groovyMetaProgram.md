# Groovy

## [Groovy Meta Programming](http://groovy-lang.org/metaprogramming.html)
- [GroovyObject](http://docs.groovy-lang.org/2.4.14/html/gapi/index.html?groovy/lang/GroovyObject.html)
```
package groovy.lang;
public interface GroovyObject {
    Object invokeMethod(String name, Object args);
    
    Object getProperty(String propertyName);
    void setProperty(String propertyName, Object newValue);
    
    MetaClass getMetaClass();
    void setMetaClass(MetaClass metaClass);
}
```
- [MetaClass](http://docs.groovy-lang.org/2.4.14/html/gapi/index.html?groovy/lang/MetaClass.html)
```
Object	invokeMethod(Class sender, Object receiver, String methodName, Object[] arguments, boolean isCallToSuper, boolean fromInsideClass)
Object	invokeMissingMethod(Object instance, String methodName, Object[] arguments)
Object	invokeMissingProperty(Object instance, String propertyName, Object optionalValue, boolean isGetter)

Object	getProperty(Class sender, Object receiver, String property, boolean isCallToSuper, boolean fromInsideClass)
void	setAttribute(Class sender, Object receiver, String messageName, Object messageValue, boolean useSuper, boolean fromInsideClass)
void	setProperty(Class sender, Object receiver, String property, Object value, boolean isCallToSuper, boolean fromInsideClass)
```
