# Maven
- Apache Maven: https://maven.apache.org/index.html
- Maven available Plugins:  https://maven.apache.org/plugins/index.html
- pom.xml: https://maven.apache.org/guides/introduction/introduction-to-the-pom.html
- Lifecycle: https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html#Lifecycle_Reference

## pom.xml
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



