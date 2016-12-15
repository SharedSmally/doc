[gradle](https://gradle.org/)
======
## [User Guide](https://docs.gradle.org/current/userguide/userguide.html)
## [DSL](https://docs.gradle.org/current/dsl/)
There is a one-to-one relationship between a [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) and a _build.gradle_ file, a [Settings](https://docs.gradle.org/current/dsl/org.gradle.api.initialization.Settings.html) instance and a _settings.gradle_ settings file. 

| Script File      | Delegator    |
| ---------------- |:------------:|
| Build script     | [Project](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html)      |
| Init script      | [Gradle](https://docs.gradle.org/current/dsl/org.gradle.api.invocation.Gradle.html)       |
| Settings script  | [Settings](https://docs.gradle.org/current/dsl/org.gradle.api.initialization.Settings.html)     |


The top level script blocks are listed below.

|     Block     	  | Description  |
| ----------------- |:------------:|
|[allprojects](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) { }	  |Configures this project and each of its sub-projects.
|[subprojects](https://docs.gradle.org/current/dsl/org.gradle.api.Project.html) { }	  |Configures the sub-projects of this project.
|[configurations](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.ConfigurationContainer.html) { }	|Configures the dependency configurations for this project.
|[buildscript](https://docs.gradle.org/current/javadoc/org/gradle/api/initialization/dsl/ScriptHandler.html) { }	  |Configures the build script classpath for this project.
|(artifacts](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.ArtifactHandler.html) { }	    |Configures the published artifacts for this project.
|[publishing](https://docs.gradle.org/current/dsl/org.gradle.api.publish.PublishingExtension.html) { }	    |Configures the PublishingExtension added by the publishing plugin.
|[repositories](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.RepositoryHandler.html) { }	  |Configures the repositories for this project.
|[dependencies](https://docs.gradle.org/current/dsl/org.gradle.api.artifacts.dsl.DependencyHandler.html) { }	  |Configures the dependencies for this project.
|[sourceSets](https://docs.gradle.org/current/javadoc/org/gradle/api/tasks/SourceSetContainer.html) { }	    |Configures the source sets of this project.
