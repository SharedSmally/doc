## [Maven Plugin](https://maven.apache.org/index.html)

## [Plugin Developer](https://maven.apache.org/plugin-developers/index.html)
- [Mojo Guide](https://maven.apache.org/guides/plugin/guide-java-plugin-development.html)

## A Build [Lifecycle]() is Made Up of Phases
Each of these build lifecycles is defined by a different list of build phases, wherein a build phase represents a stage in the lifecycle.

For example, the default lifecycle comprises of the following phases:
- validate - validate the project is correct and all necessary information is available
- compile - compile the source code of the project
- test - test the compiled source code using a suitable unit testing framework. These tests should not require the code be packaged or deployed
- package - take the compiled code and package it in its distributable format, such as a JAR.
- verify - run any checks on results of integration tests to ensure quality criteria are met
- install - install the package into the local repository, for use as a dependency in other projects locally
- deploy - done in the build environment, copies the final package to the remote repository for sharing with other developers and projects.

These lifecycle phases (plus the other lifecycle phases not shown here) are executed sequentially to complete the default lifecycle. Given the lifecycle phases above, this means that when the default lifecycle is used, Maven will first validate the project, then will try to compile the sources, run those against the tests, package the binaries (e.g. jar), run integration tests against that package, verify the integration tests, install the verified package to the local repository, then deploy the installed package to a remote repository.

## [Mojo API spec](https://maven.apache.org/developers/mojo-api-specification.html)
Main Methods:
- public void setLog( org.apache.maven.plugin.logging.Log )

Inject a standard Maven logging mechanism to allow this Mojo to communicate events and feedback to the user.

- protected Log getLog()

Furnish access to the standard Maven logging mechanism which is managed in this base class.

- void execute() throws org.apache.maven.plugin.MojoExecutionException [ABSTRACT]

Perform whatever build-process behavior this Mojo implements. See the documentation for Mojo above for more information.

[Annotations](https://maven.apache.org/plugin-tools/maven-plugin-tools-java/index.html):
- goal	@goal <goalName>:

The name for the Mojo that users will reference from the command line to execute the Mojo directly, or inside a POM in order to provide Mojo-specific configuration.
- phase	@phase <phaseName>:

Defines a default phase to bind a mojo execution to if the user does not explicitly set a phase in the POM. Note: This annotation will not automagically make a mojo run when the plugin declaration is added to the POM. It merely enables the user to omit the <phase> element from the surrounding <execution> element.
- configuration: @parameter property="aSystemProperty" default-value="${anExpression}"

Specifies the expressions used to calculate the value to be injected into this parameter of the Mojo at buildtime.

