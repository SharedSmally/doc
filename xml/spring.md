1. PropertyEditor: register customized PropertyEditor; string->Object
```
    <bean class="org.springframework.beans.factory.config.CustomEditorConfigurer">
      <property name="customEditors">
       <map>
         <entry key="com.concretepage.bean.PersonType" value="com.concretepage.PersonTypeEditor"/>
       </map>
      </property>
    </bean>
    
import java.beans.PropertyEditorSupport;
import com.concretepage.bean.PersonType;
public class PersonTypeEditor extends PropertyEditorSupport  {
	public void setAsText(String text) {
        setValue(new PersonType(text.toUpperCase()));
    }
}
```
2. PropertySource: register customized PropertySource: source->properties in Environment
```
http://techieme.in/properties-propertysources-spring/
In XML configuration, Spring allows you to configure a more complex object called PropertySourcesPlaceholderConfigurer. This is useful when you want to use placeholders for properties. 
http://javapapers.com/spring/spring-properties-with-propertysource-annotation/
https://gist.github.com/scottfrederick/2641169
Use @Value(${val})
get Properties via Environment:
    PropertySource propertySource = propertySourceContext.getBean(RedisPropertySource.class);
    context.getEnvironment().getPropertySources().addFirst(propertySource);
    
@Configuration
public class TcpIpPropertySourceConfig {
    @Autowired
    private ConfigurableEnvironment env;

    @Bean
    @Lazy(false)
    public TcpIpPropertySource tcpIpPropertySource() {
        TcpIpPropertySource tcpIpPropSource = new TcpIpPropertySource();
        MutablePropertySources sources = env.getPropertySources();
        sources.addFirst(new PropertiesPropertySource("tcp-ip", tcpIpPropSource.getAllProperties()));
    }

    return tcpIpPropSource;
}    
```
3. Converter: register customized Converter in ConversonService
```    
<bean id="conversionService" class="org.springframework.context.support.ConversionServiceFactoryBean">
     <property name="converters">
         <list>
             <!-- list of converters-->
             <bean class="org.anotes.springexample.converter.PersonToClient" />
             <bean class="org.anotes.springexample.converter.ClientToPerson" />
             ...
         </list>
     </property>
 </bean>    
 
    ConversionService conversionService = (ConversionService) context.getBean("conversionService");
    Person person = conversionService.convert(client, Person.class);
    logger.info("Client:{}", client );
    logger.info("Person:{}", person );
```
4. Formatter
```
```
