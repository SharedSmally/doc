# Release 
- [Release plugin](http://maven.apache.org/maven-release/maven-release-plugin/)

## SCM: 
used by release plugin to checkin/checkout code and create tag/label
```
    <project>
      [...]
      <build>
        [...]
        <plugins>
          [...]
          <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-release-plugin</artifactId>
            <version>3.0.0-M4</version>
            <configuration>
              <tagNameFormat>@{project.artifactId}-v@{project.version}</tagNameFormat>
            </configuration>
          </plugin>
          [...]
        </plugins>
        [...]
      </build>
      [...]
    </project>
```
