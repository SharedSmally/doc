# Eclipse Tycho

The process of creating a runnable application from the source code is calling building application. 
A headless build builds the application via the command line or via a build server, typically without 
user interaction The result of this process an be delivery to the end users, e.g., as a zip file.

Tycho is a set of Maven plug-ins for building Eclipse plug-ins, features, products and OSGi bundles. 
A Tycho build is configured via one or multiple pom.xml files.

Eclipse Tycho is a manifest-first way with maven to build 
- Eclipse Platform plug-ins/OSGi bundles
- Eclipse Platform Features
- Eclipse Update sites/p2 repositories
- Eclipse RCP applications

## Tutorial
- [tycho project](https://projects.eclipse.org/projects/technology.tycho)
- [Maven Tycho for building Eclipse Applications](https://www.vogella.com/tutorials/EclipseTycho/article.html)
- [Create Java OSGi project with Maven and Tycho](https://o7planning.org/10137/create-java-osgi-project-with-maven-and-tycho)
  - Install Tycho on Eclipse.
  - Create OSGi plugin project: with OSGi framework selected; then convert to Maven project (add pom.xml)
  - Create Maven project:
  - Create Java project as parent; then convert to Maven project; Update the previous projects with this project as the parent
    - In this parent, when run Maven Install, the child projects will be built with the target files
- [Working with the Eclipse Tycho Plug-In](https://docs.wso2.com/display/DVS400/Working+with+the+Eclipse+Tycho+Plug-In)
