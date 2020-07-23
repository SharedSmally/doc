# mvn pom.xml
- [ Super pom.xml ](https://maven.apache.org/ref/3.6.3/maven-model-builder/super-pom.html)

## Life Cycle
- Goal 
The single unit of task which does some real work. For example the compile goal (runs as  mvn compiler:compile) which compiles the Java source. 
All goals are provided by plugins, either by default plugins or by user defined plugins (configured in pom file).
- Phase
A group of ordered goals. Zero or more plugin goals are bound to a phase (either by default or by user). 
For example the compile phase (runs as "mvn compile") consists only compiler:compile goal (plugin). 
Running a phase basically runs the plugins bound with it.
- Build Lifecycle: [ attached Phases ](http://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html#Lifecycle%5FReference)
A group of ordered phases. There are three built-in lifecycle: default, clean and site. 


