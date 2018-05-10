
## read properties from a file to then use them in pom.xml.
- Add the following plugin defintion using properties-maven-plugin. 
```
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.stackoverflow</groupId>
    <artifactId>Q12619446</artifactId>
    <version>1.0-SNAPSHOT</version>

    <name>${project.artifactId}-${project.version}</name>

    <properties>
        <jdbc.driver>com.mysql.jdbc.Driver</jdbc.driver>
        <jdbc.url>jdbc:mysql://127.0.0.1:3306/db_abc</jdbc.url>
        <jdbc.user>db_user</jdbc.user>
    </properties>
    
    <build>
      <plugins>
        <plugin>
           <groupId>org.codehaus.mojo</groupId>
           <artifactId>properties-maven-plugin</artifactId>
           <version>1.0.0</version>
           <executions>
              <execution>
                 <phase>initialize</phase>
                 <goals>
                     <goal>read-project-properties</goal>
                 </goals>
                 <configuration>
                     <files>
                         <file>src/main/resources/abc.properties</file>
                     </files>
                 </configuration>
            </execution>
    </executions>
  </plugin>
 </plugins>
</build>
</project>
```
- In version 3.0 need to use configFile like :
```
<configFile>src/main/resources/db/config/flyway.properties</configFile>
```
- Define abc.properties that contains:
```
jdbc.driver = com.mysql.jdbc.Driver
jdbc.url = jdbc:mysql://127.0.0.1:3306/db_ab
jdbc.user = db_user
```
- Use the properties as follows in pom.xml:
```
<!-- language: xml -->
<driver>${jdbc.driver}</driver>
<url>${jdbc.url}</url>
<user>${jdbc.user}</user>
```
