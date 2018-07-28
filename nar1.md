```
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
   <modelVersion>4.0.0</modelVersion>
   <groupId>com.xpr.x3g.nr</groupId>
   <artifactId>nrppa</artifactId>
   <version>15.0.0</version>
   <packaging>nar</packaging>
   
   <!--  http://maven-nar.github.io/usage.html  -->   
   <properties>
      <!-- https://mvnrepository.com/artifact/com.github.maven-nar/nar-maven-plugin  -->
      <NAR_VERSION>3.5.2</NAR_VERSION>
   </properties>

  <build>
    <plugins>
      <plugin>
        <groupId>com.github.maven-nar</groupId>
        <artifactId>nar-maven-plugin</artifactId>
        <version>${NAR_VERSION}</version>
        <extensions>true</extensions>
<!-- http://maven-nar.github.io/configuration.html  -->
<configuration>
    <libsName>asn1rt,asn1per</libsName>
   
    <cpp>
        <name>g++</name>
        <!-- 
        <includes>
            <include>main/src/c++/**/*.cpp</include>
        </includes>
         -->
        <sourceDirectory>main/src/c++</sourceDirectory>

        <includePaths> <!-- included in  noarch -->
            <includePath><path>main/src/include</path></includePath>
        </includePaths>

        <systemIncludePaths>  <!-- not included in noarch -->
            <systemIncludePath>${HOME}/asn1/asn1c</systemIncludePath>
        </systemIncludePaths>
    
        <options>
            <option>-std=c++11</option>
        </options>
    </cpp>
 
    <linker>
        <name>g++</name>
        <options>
            <option>-L${HOME}/asn1/asn1c/cpp/libgpp4/</option>
        </options>
<!-- 
        <libs>
            <lib> 
                <name>asn1rt, asn1per</name>
                <directory>${HOME}/asn1/asn1c/cpp/libgpp4</directory>
            </lib>
        </libs>
 -->
        <!-- linker with: -Bdynamic -lasn1rt   -->
        <sysLibs>
            <sysLib> 
                <name>asn1rt, asn1per</name>
            </sysLib>
        </sysLibs>
    </linker>

    <libraries>
        <library>
            <type>shared</type>
        </library>
    </libraries>
</configuration>

      </plugin>
    </plugins>
  </build>
  
</project>
```
