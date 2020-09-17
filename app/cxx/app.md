# Application
- AppContext: Container of Beans
- BeanFactory: Factory to create Bean using BeanInfo
- BeanInfo: template to create Bean
- Bean: Manageable Objects with LifeCycle
- Component/Service/Repository/Controller: 

## AppContext -> BeanFactory
The IoC container of Beans

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
