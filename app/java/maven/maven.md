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

### Property in pom.xml
The syntax for using a property in Maven is to surround the property name with two curly braces and precede it with a dollar symbol.
- env
    The env variable exposes environment variables exposed by os or shell. A reference to ${env.PATH} in a Maven POM would be replaced by the ${PATH} environment variable (or %PATH% in Windows). 
- project
    The project variable exposes the POM. use a dot-notated (.) path to reference the value of a POM element. For example, the groupId and artifactId to set the finalName element in the build configuration was: ${project.groupId}-${project.artifactId}. 
- settings
    The settings variable exposes Maven settings information. Can use a dot-notated (.) path to reference the value of an element in a settings.xml file. For example, ${settings.offline} would reference the value of the offline element in ~/.m2/settings.xml. 
 - Java System Properties
    All properties accessible via getProperties() on java.lang.System are exposed as POM properties. Some examples of system properties are: ${user.name}, ${user.home}, ${java.home}, and ${os.name}. A full list of system properties can be found in the Javadoc for the System class.  
 - x
    Arbitrary properties can be set with a properties element in a pom.xml or settings.xml, or properties can be loaded from external files. 

### Dependency Scope: 
| scope | desc |
|-------|-------|
| compile | the default scope; all dependencies are compile-scoped if a scope is not supplied. compile dependencies are available in all classpaths, and they are packaged. |
| provided |   Used when expect the JDK or a container to provide them. provided dependencies are available on the compilation classpath (not runtime). They are not transitive, nor are they packaged. |
| runtime |  runtime dependencies are required to execute and test the system, but they are not required for compilation. |
| test | test-scoped dependencies are not required during the normal operation of an application, and they are available only during test compilation and execution phases. |
| system | similar to provided except that need to provide an explicit path to the JAR on the local file system. This is intended to allow compilation against native objects that may be part of the system libraries. The artifact is assumed to always be available and is not looked up in a repository. If declare the scope to be system, must also provide the systemPath element.|

The dependency can be optiona via <optioanl>true</optional>.

#### dependencyManagement for dependency
Using the dependencyManagement element in a pom.xml allows you to reference a dependency in a child project without having to explicitly list the version. Maven will walk up the parent-child hierarchy until it finds a project with a dependencyManagement element, it will then use the version specified in this dependencyManagement element.

### classifier
    Use a classifier if releasing the same code but needed to produce two separate artifacts for technical reasons. Classifiers are commonly used to package up an artifact’s sources, JavaDocs or binary assemblies.

### pom inheritance
Items a Maven POM inherits from its parent POM:
- identifiers (at least one of groupId or artifactId must be overridden.)
- dependencies
- developers and contributors
- plugin lists
- reports lists
- plugin executions (executions with matching ids are merged)
- plugin configuration
Group dependencies in <packaging>pom</packaging> project, which could be depdended or inherited.

### LifeCycle
#### Clean LifeCycle: mvn clean
- pre-clean
- clean
- post-clean
#### Site LifeCycle: mvn site
- pre-site
- site
- post-site
- site-deploy
#### Default LifeCycle
| Lifecycle Phase | Description |
|-----------------|-------------|
| validate | Validate the project is correct and all necessary information is available to complete a build | 
| generate-sources | Generate any source code for inclusion in compilation |
| process-sources | Process the source code, for example to filter any values |
| generate-resources | Generate resources for inclusion in the package |
| process-resources | Copy and process the resources into the destination directory, ready for packaging |
| compile | Compile the source code of the project |
| process-classes | Post-process the generated files from compilation, for example to do bytecode enhancement on Java classes |
| generate-test-sources | Generate any test source code for inclusion in compilation |
| process-test-sources | Process the test source code, for example to filter any values |
| generate-test-resources | Create resources for testing |
| process-test-resources | Copy and process the resources into the test destination directory |
| test-compile	| Compile the test source code into the test destination directory |
| test	| Run tests using a suitable unit testing framework. These tests should not require the code be packaged or deployed |
| prepare-package | Perform any operations necessary to prepare a package before the actual packaging. This often results in an unpacked, processed version of the package | 
| package	| Take the compiled code and package it in its distributable format, such as a JAR, WAR, or EAR |
| pre-integration-test | Perform actions required before integration tests are executed. This may involve things such as setting up the required environment |
| integration-test | Process and deploy the package if necessary into an environment where integration tests can be run |
| post-integration-test | Perform actions required after integration tests have been executed. This may include cleaning up the environment | 
| verify	| Run any checks to verify the package is valid and meets quality criteria |
| install | Install the package into the local repository, for use as a dependency in other projects locally |
| deploy	| Copies the final package to the remote repository for sharing with other developers and projects (usually only relevant during a formal release)|


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





