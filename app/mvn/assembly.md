#[mvn Assembly](http://maven.apache.org/plugins/maven-assembly-plugin/)
An assembly is a group of files, directories, and dependencies that are assembled into an archive format and distributed.

To use the Assembly Plugin in Maven:
- choose or write the assembly descriptor to use,
- configure the Assembly Plugin in the project's pom.xml
- run "mvn assembly:single" or "mvn package" on the project.

### assembly descriptor (assembly/assembly.xml)
```
    <assembly xmlns="http://maven.apache.org/ASSEMBLY/2.1.0"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://maven.apache.org/ASSEMBLY/2.1.0 http://maven.apache.org/xsd/assembly-2.1.0.xsd">
      <id>bin</id>
      <formats>
        <format>tar.gz</format>
        <format>tar.bz2</format>
        <format>zip</format>
      </formats>
      <fileSets>
        <fileSet>
          <directory>${project.basedir}</directory>
          <outputDirectory></outputDirectory>
          <includes>
            <include>README*</include>
            <include>LICENSE*</include>
            <include>NOTICE*</include>
          </includes>
        </fileSet>
        <fileSet>
          <directory>${project.build.directory}</directory>
          <outputDirectory></outputDirectory>
          <includes>
            <include>*.jar</include>
          </includes>
        </fileSet>
        <fileSet>
          <directory>${project.build.directory}/site</directory>
          <outputDirectory>docs</outputDirectory>
        </fileSet>
      </fileSets>
    </assembly>
```
### configure the Assembly Plugin in the project's pom.xml
```
    <project>
      <parent>
        <artifactId>maven</artifactId>
        <groupId>org.apache.maven</groupId>
        <version>2.0-beta-3-SNAPSHOT</version>
      </parent>
      <modelVersion>4.0.0</modelVersion>
      <groupId>org.apache.maven</groupId>
      <artifactId>maven-embedder</artifactId>
      <name>Maven Embedder</name>
      <version>2.0-beta-3-SNAPSHOT</version>
      <build>
        <plugins>
          <plugin>
            <artifactId>maven-assembly-plugin</artifactId>
            <version>2.5.3</version>
            <configuration>
              <descriptor>assembly/assembly.xml</descriptor>
            </configuration>
            <executions>
              <execution>
                <id>create-archive</id>
                <phase>package</phase>
                <goals>
                  <goal>single</goal>
                </goals>
              </execution>
            </executions>
          </plugin>
        </plugins>
      </build>
      ...
    </project>
```

## Documents
- [Assembly Usage](http://maven.apache.org/plugins/maven-assembly-plugin/usage.html)
- [Assembly format](http://maven.apache.org/plugins/maven-assembly-plugin/assembly.html)
- [Advanced Topics](http://maven.apache.org/plugins/maven-assembly-plugin/advanced-descriptor-topics.html)
