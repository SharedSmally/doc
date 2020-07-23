
# mvn plugins

- Run shell script
```
<plugin>
 <groupId>org.codehaus.mojo</groupId>
 <artifactId>exec-maven-plugin</artifactId>
 <version>1.6.0</version>
 <executions>
  <execution>
   <id>my-exec</id>
   <phase>pre-integration-test</phase>
  <goals>
   <goal>exec</goal>
  </goals>
  </execution>
 </executions>
 <configuration>
  <executable>${project-home}/resources/run.sh</executable>
 </configuration>
</plugin>
```
