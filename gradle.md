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

|     Block     	 | Description  |
| ---------------- |:------------:|
|allprojects { }	 |Configures this project and each of its sub-projects.
|artifacts { }	   |Configures the published artifacts for this project.
|buildscript { }	 |Configures the build script classpath for this project.
|configurations { }	|Configures the dependency configurations for this project.
|dependencies { }	 |Configures the dependencies for this project.
|repositories { }	 |Configures the repositories for this project.
|sourceSets { }	   |Configures the source sets of this project.
|subprojects { }	 |Configures the sub-projects of this project.
|publishing { }	   |Configures the PublishingExtension added by the publishing plugin.

