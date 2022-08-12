# Maven
- Maven Reference: https://books.sonatype.com/mvnref-book/reference/index.html
- Apache Maven: https://maven.apache.org/index.html
- Maven available Plugins:  https://maven.apache.org/plugins/index.html
- pom.xml: https://maven.apache.org/guides/introduction/introduction-to-the-pom.html
- Lifecycle: https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html#Lifecycle_Reference

## pom.xml
![POM (Project Object Model)](https://books.sonatype.com/mvnref-book/reference/figs/web/pom-relationships_pom-small.png)
The super pom.xml: https://maven.apache.org/ref/3.1.1/maven-model-builder/super-pom.html
The pom.xml layout:  https://maven.apache.org/ref/3.8.6/maven-model/maven.html
- parent project
- properties:
- depdendencies: for list of dependencies
- build/reporting: with plugins
- profiles:
- scm: how to checkout the source code
- repositories: where to deploy the build targets

### Create a project based on archetype:
- List of available archetypes: https://maven.apache.org/archetypes/index.html  
```
mvn archetype:generate         \
   -DarchetypeGroupId=org.apache.maven.archetypes     \
   -DarchetypeArtifactId=maven-archetype-quickstart   \
   -DarchetypeVersion=xxx [-DarchetypeCatalog=local]	\
   -DgroupId=com.xxx -DartifactId=xxx -Dversion=xxx -Dpackage=xxx	\
```

## Archetype
Template to create a project
### Tutorials
- https://maven.apache.org/archetype/index.html
- https://www.baeldung.com/maven-archetype

### Create a Archetype project
```
mvn archetype:generate              \
  -DarchetypeGroupId=org.apache.maven.archetypes   \
  -DarchetypeArtifactId=maven-archetype-archetype  \
  -DgroupId=com.jpw.plugins         \
  -DartifactId=counter-maven-plugin \
  -Dversion=1.0.0-SNAPSHOT          \
```
### update meta files and template files
- src/main/resources/archetype-resources: the template from which resources are copied to the newly created project
- src/main/resources/META-INF/maven/archetype-metadata.xml: the descriptor to describe archetypes' metadata

## Plugin
A plugin contains multiple mojo, each mojo implement one goal (task), which can be attached to one or multiple phases. A phase executes the goals attached 
to this phase by the order in executions.
### Tutorials
- https://maven.apache.org/plugin-developers/index.html
- https://www.baeldung.com/maven-plugin
- List of available plugins: https://maven.apache.org/plugins/index.html
- Plugin name: **plugin_name-maven-plugin**

### Create a plugin project
```
mvn archetype:generate                 \
  -DarchetypeGroupId=org.apache.maven.archetypes \
  -DarchetypeArtifactId=maven-archetype-mojo     \
  -DgroupId=com.jpw.archetype          \
  -DartifactId=counter-maven-archetype \
  -Dversion=1.0.0-SNAPSHOT             \
```
update pom.xml for packaging type:
```
<packaging>maven-archetype</packaging>
```
and extension point:
```
<build>
    <extensions>
        <extension>
            <groupId>org.apache.maven.archetype</groupId>
            <artifactId>archetype-packaging</artifactId>
            <version>3.0.1</version>
        </extension>
    </extensions>
    <!--....-->
</build>
```

### Add Dependencies and Parameters
```
    <dependency>
        <groupId>org.apache.maven</groupId>
        <artifactId>maven-plugin-api</artifactId>
        <version>3.6.3</version>
    </dependency>
    <dependency>
        <groupId>org.apache.maven.plugin-tools</groupId>
        <artifactId>maven-plugin-annotations</artifactId>
        <version>3.6.0</version>
        <scope>provided</scope>
    </dependency>
    <dependency>
        <groupId>org.apache.maven</groupId>
        <artifactId>maven-project</artifactId>
        <version>2.2.1</version>
    </dependency>
```
### Execute the plugin goal or phase
```
mvn groupId:artifactId:version:goal
mvn phase
```
### Mojo parameters
https://books.sonatype.com/mvnref-book/reference/writing-plugins-sect-mojo-params.html

| annotation | desc |
|------------|------|
|@parameter [alias="someAlias"] [expression="${someExpression}"] [default-value="value"]|Marks a private field (or a setter method) as a parameter. The alias provides the name of the parameter. If alias is omitted, Maven will use the name of the variable as the parameter name. The expression is an expression that Maven will evaluate to obtain a value. Usually the expression is a property reference like ${echo.message}. default-value is the value that this Mojo will use if no value can be derived from the expression or if a value was not explicitly supplied via plugin configuration in a POM. |
|@required|If this annotation is present, a valid value for this parameter is required prior to Mojo execution. If Maven tries to execute this Mojo and the parameter has a null value, Maven will throw an error when it tries to execute this goal. |
|@readonly |If this annotation is present, the user cannot directly configure this parameter in the POM. You would use this annotation with the expression attribute of the parameter annotation. For example, if you wanted to make sure that a particular parameter always had the value of the finalName POM property, you would list an expression of ${build.finalName} and then add the @readOnly annotation. If this were the case, the user could only change the value of this parameter by changing the value of finalName in the POM. |
|@component| Tells Maven to populate a field with a Plexus Component. A valid value for the @component annotation would be:
    @component role="org.codehaus.plexus.archiver.Archiver" roleHint="zip"|





