# Build docker image
## Documents
- [docker-maven plugin](https://github.com/fabric8io/docker-maven-plugin)
- [Document](https://dmp.fabric8.io/)
- [Introduction](https://github.com/fabric8io/docker-maven-plugin/blob/master/doc/intro.md)
```
<plugin>
  <groupId>io.fabric8</groupId>
  <artifactId>docker-maven-plugin</artifactId>
  <version>0.37.0</version>
  <configuration>
     ....
     <images>
     ...
     </images>
  <configuration>
  <executions>
      <execution>
       <id>docker-build</id>
       <phase>package</phase>
       <goals>
         <goal>build</goal> <!-- build to create the images with the artifact -->
       </goals>
    </execution>
  </executions>
```

## Configuration
Each specific image configuration has three parts:
- A general image part containing the image's name and alias.
- A <build> configuration specifying how images are built. Can Use inline or external Dockerfile.
- A <run> configuration describing how containers should be created and started.
```
  <configuration>
  <images>
    <image>
      <alias>service</alias>
      <name>fabric8/docker-demo:${project.version}</name>

      <build>
         <from>java:8</from>
         <assembly>
           <descriptor>docker-assembly.xml</descriptor>
         </assembly>
         <ports>
           <port>8080</port>
         </ports>
         <cmd>
            <shell>java -jar /maven/service.jar</shell>
         </cmd>
      </build>

      <run>
         <ports>
           <port>tomcat.port:8080</port>
         </ports>
         <wait>
           <http>
              <url>http://localhost:${tomcat.port}/access</url>
           </http>
           <time>10000</time>
         </wait>
         <links>
           <link>database:db</link>
         </links>
       </run>
    </image>

    <image>
      <alias>database</alias>
      <name>postgres:9</name>
      <run>
        <wait>
          <log>database system is ready to accept connections</log>
          <time>20000</time>
        </wait>
      </run>
    </image>
  </images>
</configuration>
```
