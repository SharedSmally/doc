## [Maven](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)

Maven:
### [Predifined Varaibles](https://github.com/cko/predefined_maven_properties/blob/master/README.md)

 - ${project.basedir} represents the directory containing pom.xml
 - ${project.build.directory} results in the path to the "target" directory 
 - ${project.build.outputDirectory} results in the path to the "target/classes" directory
 - ${project.name} refers to the name of the project (deprecated: ${pom.name} ).
 - ${project.version} refers to the version of the project (deprecated: ${pom.version}).
 - ${project.build.finalName} refers to the final name of the file created when the built project is packaged

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

### [LifeCycle](http://maven.apache.org/ref/3.5.0/maven-core/lifecycles.html)
Maven defines 3 lifecycles in META-INF/plexus/components.xml:
- [default](http://maven.apache.org/ref/3.5.0/maven-core/lifecycles.html#default_Lifecycle) Lifecycle
- [clean](http://maven.apache.org/ref/3.5.0/maven-core/lifecycles.html#clean_Lifecycle) Lifecycle
- [site](http://maven.apache.org/ref/3.5.0/maven-core/lifecycles.html#site_Lifecycle) Lifecycle


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
A Build Phase is Made Up of [Plugin Goals](https://maven.apache.org/guides/mini/guide-configuring-plugins.html). A build phase is responsible for a specific step in the build lifecycle, the manner in which it carries out those responsibilities may vary. And this is done by declaring the plugin goals bound to those build phases.

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

### Setup  ~/.m2/settings.xml:
```
<settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0
                      https://maven.apache.org/xsd/settings-1.0.0.xsd">
  <localRepository>${user.home}/.m2/repository</localRepository>
  <interactiveMode>true</interactiveMode>
  <offline>false</offline>
 
  <servers>
    <server>
      <id>{server/repo-id}</id>
      <username>{username}</username>
      <password>{password}</password>
      <privateKey>${user.home}/.ssh/id_dsa</privateKey>
      <passphrase>some_passphrase</passphrase>
      <filePermissions>664</filePermissions>
      <directoryPermissions>775</directoryPermissions>
      <configuration></configuration>
    </server>
  </servers>

  <mirrors>
    <mirror>
      <id>maven-central</id>
      <name>maven central</name>
      <url>http://{hostname}/repository/maven-central/</url>
      <mirrorOf>central</mirrorOf>
    </mirror>
  </mirrors>

  <profiles>
    <profile>
      <id>{profile-id}</id>
      <repositories>
        <repository>
          <id>env-test</id>
          <name>Codehaus Snapshots</name>
          <releases>
            <enabled>false</enabled>
            <updatePolicy>always</updatePolicy>
            <checksumPolicy>warn</checksumPolicy>
          </releases>
          
          <snapshots>
            <enabled>true</enabled>
            <updatePolicy>never</updatePolicy>
            <checksumPolicy>fail</checksumPolicy>
          </snapshots>
          <url>http://snapshots.maven.codehaus.org/maven2</url>
          <layout>default</layout>
        </repository>
      </repositories>

      <pluginRepositories>
        ...
      </pluginRepositories>
    </profile>
  </profiles>

  <activeProfiles>
    <activeProfile>{profile-id}</activeProfile>
  </activeProfiles> 
</settings>
```

### Upload maven file to repos
- Add server in ~/.m2/settings.xml:
```
   <server>
      <id>{repo-id}</id>
      <username>{repo-username}</username>
      <password>{password/encrypted password}</password>
    </server>
```
- Add remote (artifactory) repository in pom.xml: 2 repo-id should match
```
    <distributionManagement>
      <repository>
        <id>{repo-id}</id>
        <name>{repo-name}</name>
        <url>(http://integ/){repo-host-name}/artifactory/{repo-url}</url>
      </repository>
    </distributionManagement>
```
- Deploy maven jar to remote repos
```
   mvn clean deploy
```
- Deploy maven jar to local repos[defined in ~/.m2/settings.xml. Default is ~/.m2/repository]:
```
<localRepository>${user.home}/.m2/repository</localRepository>
```
```
   mvn clean install
```

### maven for c++: [ maven-nar-plugin ] (http://maven-nar.github.io/index.html)
- [ Usage/Example ] (http://maven-nar.github.io/usage.html)
- [ nar configurations ] (http://maven-nar.github.io/configuration.html)
- standard layout
```
/${project}
   /src
      /main
            /java
            /resources
            /include
            /c++
            /c
            /fortran
      /test
            /java
            /resources
            /include
            /c++
            /c
            /fortran                        
```
- sample pom.xml
```
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.cpw.app</groupId>
  <artifactId>cpw</artifactId>
  <packaging>nar</packaging>
  <version>1.0-SNAPSHOT</version>
  <name>cxx app</name>
  <url>http://maven.apache.org</url>

  <dependencies>
    <dependency>
      <groupId>cppunit</groupId>
      <artifactId>cppunit</artifactId>
      <version>3.8.1</version>
      <scope>test</scope>
      <type>nar</type>
    </dependency>
  </dependencies>

  <build>
    <plugins>
        <plugin>
  	        <groupId>com.github.maven-nar</groupId>
		         <artifactId>nar-maven-plugin</artifactId>
		         <version>3.6.0</version>
		         <extensions>true</extensions>
           <configuration>
               <libraries>
                    <library>
                        <type>executable</type>
                        <run>true</run>
                    </library>
               </libraries>

                <!-- Here is the config for the custom source dir and includes -->
                <cpp>
                    <sourceDirectory>
                        ${basedir}/src/main/c++/
                    </sourceDirectory>
                    <includes>
                        <include>${basedir}/src/main/c++/include/*.h</include>
                    </includes>
                </cpp>
                
                <libraries>
                    <library>
                        <type>executable</type>
                        <run>true</run>
                    </library>
                </libraries>
            </configuration>
        </plugin>
     </plugins>
   </build>

   <distributionManagement>
      <repository>
        <id>release-snapshoot</id>
        <name>jpw snapshoot</name>
        <url>${url}</url>
      </repository>
   </distributionManagement>
</project>

```
The following archetypes are available for the nar plugin:
- maven-archetype-nar-jni, a project with a native file, its java jni class and a java test class
- maven-archetype-nar-lib, a project with a native library, its header file and a c test program
- maven-archetype-nar-exec, a project with a native file which compiles into an executable
    
The NAR plugin sets several properties that can be helpful in configuring other plugins.
- nar.arch: The architecture (e.g. x86_64).
- nar.os: The operating system (e.g. MacOSX).
- nar.linker: The linker (e.g. gpp).
- nar.aol: The full [ AOL ](http://maven-nar.github.io/aol.html) string. This is helpful when setting java.library.path; with a default configuration, this would be target/nar/${project.artifactId}-${project.version}-${nar.aol}/lib/${nar.aol}/jni
- nar.aol.key: The AOL string with the '-' characters replaced by '.' characters.

