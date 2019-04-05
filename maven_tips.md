# maven

## envs
- ~/.m2/settings.xml: user-specific configurration for authentication, repositories and other customized info
- ~/.m2/repository: local maven repository. Store dependencies and packages by mvn install
- ./pom.xml:
```
$ java -version
$ ln -s maven-2.0.9 maven
$ export M2_HOME=/usr/local/maven
$ export PATH=${M2_HOME}/bin:${PATH}
$ mvn -version
```

## command
```
mvn [options] [<plugin:goal(s)>] [<phase(s)>] [-Dparameter=name]
```
- Create a simple project
Use Maven Archetype plugin with goal *create* to create project layout.
```
mvn archetype:create -DgroupId=com.jpw -DarctifactId=common -DpackageName=com.jpw.common -Dversion=1.0.0
```
##
