# Application
- AppContext: Container of Beans, root of ServiceContext
- BeanFactory: Factory to create Bean using BeanInfo
- BeanInfo: template to create Bean
- Bean: Manageable Objects with LifeCycle
- Component/Service/Repository/Controller: 
- ServiceContext: Service containers with hierarchy: 

## BeanFactory
```
std::shared_ptr<T> create(const String & name, ARGS... args)
```
## BeanFactoryMgr
```
void subscribe<T>(BeanFactory<T> factory)
void unsubscribe<T>()
std::shared_ptr<T> create(const String & name)
```
## AppContext -> BeanFactoryMgr
The IoC container of Beans
```
std::shared_ptr<Bean> get(const String & name)
std::shared_ptr<T> get<T>(const String & name)
bool contains(const String & name) const
```
## ServiceContext -> AppContext
```
AppContext & getRoot()
ServiceContext & getParent()
ServiceContext & getChild(const String & name)
bool isRoot() const
```

## beans.xml
```
<beans>
   <bean name="id" class="fullClassname" include=""headerFile">
       <constructor>
           <arg name="argName" value="argValue" ref="refBeanName"/>*
       </constructor>   // ${argValue}: from property file
       <property name="propeytyName" value="propertyValue" ref="refBeanName">
           <item key="mapKey">itemValue</iterm>* // for array/set/vector/map
       </property>*
   </bean>*
</beans>
```
