## [Maven](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)

Maven:
### [Predifined Varaibles](https://github.com/cko/predefined_maven_properties/blob/master/README.md)



### Maven Command
```
usage: mvn [options] [<goal(s)>] [<phase(s)>]

Options:
 -B,--batch-mode                        Run in non-interactive (batch) mode
 -f,--file <arg>                        Force the use of an alternate POM file (or directory with pom.xml).
 -q,--quiet                             Quiet output - only show errors
 -s,--settings <arg>                    Alternate path for the user settings file
 -D,--define <arg>                      Define a system property
 -e,--errors                            Produce execution error messages
 -l,--log-file <arg>                    Log file where all build output will go.
 
 -am,--also-make                        If project list is specified, also build projects required by the list
 -amd,--also-make-dependents            If project list is specified, also build projects that depend on projects on the list
 -b,--builder <arg>                     The id of the build strategy to use.
 -C,--strict-checksums                  Fail the build if checksums don't match
 -c,--lax-checksums                     Warn if checksums don't match
 -emp,--encrypt-master-password <arg>   Encrypt master security password
 -ep,--encrypt-password <arg>           Encrypt server password
 -fae,--fail-at-end                     Only fail the build afterwards; allow all non-impacted builds to continue
 -ff,--fail-fast                        Stop at first failure in reactorized builds
 -fn,--fail-never                       NEVER fail the build, regardless of project result
 -gs,--global-settings <arg>            Alternate path for the global settings file
 -gt,--global-toolchains <arg>          Alternate path for the global toolchains file 
 -llr,--legacy-local-repository         Use Maven 2 Legacy Local Repository behaviour
 -N,--non-recursive                     Do not recurse into sub-projects
 -nsu,--no-snapshot-updates             Suppress SNAPSHOT updates
 -o,--offline                           Work offline
 -P,--activate-profiles <arg>           Comma-delimited list of profiles to activate
 -pl,--projects <arg>                   Comma-delimited list of specified reactor projects to build instead of all projects
  -rf,--resume-from <arg>                Resume reactor from specified project
 -T,--threads <arg>                     Thread count, for instance 2.0C where C is core multiplied
 -t,--toolchains <arg>                  Alternate path for the user toolchains file
 -U,--update-snapshots                  Forces a check for missing releases and updated snapshots on remote repositories
 
 -h,--help                              Display help information
 -V,--show-version                      Display version information WITHOUT stopping build
 -v,--version                           Display version information
 -X,--debug                             Produce execution debug output
```

### Phases

A Build Lifecycle is Made Up of Phases. Each of these build lifecycles is defined by a different list of build phases, wherein a build phase represents a stage in the lifecycle.

For example, the default lifecycle comprises of the following phases:
- initialize - initialize the project
- validate - validate the project is correct and all necessary information is available
- compile - compile the source code of the project
- test - test the compiled source code using a suitable unit testing framework. These tests should not require the code be packaged or deployed
- package - take the compiled code and package it in its distributable format, such as a JAR.
- verify - run any checks on results of integration tests to ensure quality criteria are met
- install - install the package into the local repository, for use as a dependency in other projects locally
- deploy - done in the build environment, copies the final package to the remote repository for sharing with other developers and projects.

- mvn initialize

### Goal
A Build Phase is Made Up of Plugin Goals. A build phase is responsible for a specific step in the build lifecycle, the manner in which it carries out those responsibilities may vary. And this is done by declaring the plugin goals bound to those build phases.

A plugin goal represents a specific task (finer than a build phase) which contributes to the building and managing of a project. It may be bound to zero or more build phases. A goal not bound to any build phase could be executed outside of the build lifecycle by direct invocation. The order of execution depends on the order in which the goal(s) and the build phase(s) are invoked. For example, consider the command below. The clean and package arguments are build phases, while the dependency:copy-dependencies is a goal (of a plugin).
```
mvn clean dependency:copy-dependencies package
```

### Init project
 Execute the following the command to create the simplest of Maven projects, 
```
mvn -B archetype:generate \
  -DarchetypeGroupId=org.apache.maven.archetypes \
  -DgroupId=com.mycompany.app \
  -DartifactId=my-app
```
