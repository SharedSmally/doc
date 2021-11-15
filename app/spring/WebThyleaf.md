# Web - Thymeleaf template
- [Tutorial](https://www.thymeleaf.org/doc/tutorials/3.0/thymeleafspring.html)

## Beans
```
@Bean
public SpringResourceTemplateResolver templateResolver(){ 
}
@Bean
public SpringTemplateEngine templateEngine(){
}
@Bean
public ThymeleafViewResolver viewResolver(){
}

```
There are two interfaces in Spring MVC that conform the core of its templating system:
- org.springframework.web.servlet.View: in charge of rendering the actual HTML interface, by the execution of some template engine like Thymeleaf.
- org.springframework.web.servlet.ViewResolver: obtaining View objects for a specific operation and locale.

## Controller
- Define Model (raw data), Model Repository (access of Model) and Model Service (use Repository to access data)
- Define Controller (use Service to access data)
    - Define a list of Model Attributes: called before the mapped method is callled
```
@ModelAttribute("allTypes")
public List<Type> populateTypes() {
    return Arrays.asList(Type.ALL);
}
    
@ModelAttribute("allFeatures")
public List<Feature> populateFeatures() {
    return Arrays.asList(Feature.ALL);
}
    
@ModelAttribute("allVarieties")
public List<Variety> populateVarieties() {
    return this.varietyService.findAll();
}
    
@ModelAttribute("allSeedStarters")
public List<SeedStarter> populateSeedStarters() {
    return this.seedStarterService.findAll();
}
```
- Define template file with model

## Form Definition
### Command object
Command object is the name Spring MVC gives to form-backing beans, the objects that model a form’s fields and provide getter and setter 
methods that will be used by the framework for establishing and obtaining the values input by the user at the browser side.

Thymeleaf requires to specify the command object by using a th:object attribute in <form> tag:
```
<form action="#" th:action="@{/seedstartermng}" th:object="${seedStarter}" method="post">
    ...
</form>  
```
- Values for th:object attributes in form tags must be variable expressions (${...}) specifying only the name of a model attribute, without property navigation. This means that an expression like ${seedStarter} is valid, but ${seedStarter.data} would not be.
- Once inside the <form> tag, no other th:object attribute can be specified. This is consistent with the fact that HTML forms cannot be nested.
  
### Inputs
```
<input type="text" id="datePlanted" name="datePlanted" th:value="*{datePlanted}" />  
```
  - **th:field**: bind the input with a property in the form-backing bean. The expressions can include property navigation

-  CheckBox
```
  <li th:each="feat : ${allFeatures}">
    <input type="checkbox" th:field="*{features}" th:value="${feat}" />
    <label th:for="${#ids.prev('features')}" 
           th:text="#{${'seedstarter.feature.' + feat}}">Heating</label>
  </li>  
``` 
- Radio
```
  <li th:each="ty : ${allTypes}">
    <input type="radio" th:field="*{type}" th:value="${ty}" />
    <label th:for="${#ids.prev('type')}" th:text="#{${'seedstarter.type.' + ty}}">Wireframe</label>
  </li>  
```  
- List selector
```
<select th:field="*{type}">
  <option th:each="type : ${allTypes}" 
          th:value="${type}" 
          th:text="#{${'seedstarter.type.' + type}}">Wireframe</option>
</select>  
```  

## Thymleaf template express
