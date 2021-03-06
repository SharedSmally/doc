[gradle](https://gradle.org/)
======
## [User Guide](https://docs.gradle.org/current/userguide/userguide.html)
- mvn repos: https://mvnrepository.com/artifact

## [DSL](https://docs.gradle.org/current/dsl/)
There is a one-to-one relationship between a [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) and a _build.gradle_ file, a [Settings](https://docs.gradle.org/current/dsl/org.gradle.api.initialization.Settings.html) instance and a _settings.gradle_ settings file. 

| Script File      | Delegator    |
| ---------------- |:------------:|
| Build script     | [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html)      |
| Init script      | [Gradle](https://docs.gradle.org/current/dsl/org.gradle.api.invocation.Gradle.html)       |
| Settings script  | [Settings](https://docs.gradle.org/current/dsl/org.gradle.api.initialization.Settings.html)     |


A build script is made up of zero or more statements and script blocks. Statements can include method calls, property assignments, and local variable definitions. A script block is a method call which takes a closure as a parameter. The closure is treated as a configuration closure which configures some delegate object as it executes.

The top level script blocks in **build.gradle**: 

|     Block     	  | Description  |
| ----------------- |:------------:|
|[allprojects](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) { }	  |Configures this project and each of its sub-projects. Delegate to [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html)
|[subprojects](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) { }	  |Configures the sub-projects of this project. Delegate to [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html)
|[configurations](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.ConfigurationContainer.html) { }	|Configures the dependency configurations for this project. Delegate to [ConfigurationContainer](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.ConfigurationContainer.html)
|[buildscript](https://docs.gradle.org/current/javadoc/org/gradle/api/initialization/dsl/ScriptHandler.html) { }	  |Configures the build script classpath for this project. Delegate to [ScriptHandler] (https://docs.gradle.org/current/javadoc/org/gradle/api/initialization/dsl/ScriptHandler.html)
|[artifacts](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.ArtifactHandler.html) { }	    |Configures the published artifacts for this project. Delegate to [ArtifactHandler](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.ArtifactHandler.html)
|[publishing](https://docs.gradle.org/current/dsl/org.gradle.api.publish.PublishingExtension.html) { }	    |Configures the PublishingExtension added by the publishing plugin. Delegate to [PublishingExtension](https://docs.gradle.org/current/dsl/org.gradle.api.publish.PublishingExtension.html)
|[repositories](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.RepositoryHandler.html) { }	  |Configures the repositories for this project. Delegate to [RepositoryHandler](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.RepositoryHandler.html)
|[dependencies](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html) { }	  |Configures the dependencies for this project. Delegate to [DependencyHandler](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html)
|[sourceSets](https://docs.gradle.org/current/javadoc/org/gradle/api/tasks/SourceSetContainer.html) { }	    |Configures the source sets of this project. Delegate to [SourceSetContainer](https://docs.gradle.org/current/javadoc/org/gradle/api/tasks/SourceSetContainer.html)


Some core types in Gradle: [API JavaDoc](https://docs.gradle.org/current/javadoc/)

|     Block     	  | Description  |
| ----------------- |:------------:|
|[task](https://docs.gradle.org/current/dsl/org.gradle.api.Task.html) | A single atomic piece of work for a build, such as compiling classes or generating javadoc. It consists of list of Actions. Delegate to [Task](https://docs.gradle.org/current/dsl/org.gradle.api.Task.html) 
|[ant](https://docs.gradle.org/current/javadoc/org/gradle/api/AntBuilder.html) | An instance of an [AntBuilder](https://docs.gradle.org/current/javadoc/org/gradle/api/AntBuilder.html)  that allows to use Ant from your build script.
|[gradle](https://docs.gradle.org/current/dsl/org.gradle.api.invocation.Gradle.html) | Represents an invocation of [Gradle](https://docs.gradle.org/current/dsl/org.gradle.api.invocation.Gradle.html). Obtain a Gradle instance by calling Project.getGradle().
|[script](https://docs.gradle.org/current/dsl/org.gradle.api.Script.html) | This interface is implemented by all Gradle scripts to add in some Gradle-specific methods.

## gradle
- Use gradle daemon:
```
Add the following in ~/.gradle/gradle.properties:
    org.gradle.daemon=true
Stop gradle daemon:  gradle --stop
```
- Init a gradle project: using [init plugin](https://docs.gradle.org/current/userguide/build_init_plugin.html)

gradle init --type xxx

Supported types:
   - pom: convert pom.xml to build.gradle
   - java-application:
   - java-library:  --test-framework testng|spock|junit
   - scala-library
   - groovy-library
   - basic
   
   

