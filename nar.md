# nar : maven plugin to generate shared library from c++:
## nar project layout:
- pom.xml; src/main/cpp/*.cpp; src/main/include/*.h
```
- <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
        <modelVersion>4.0.0</modelVersion>
        <groupId>group</groupId>
        <artifactId>artifact</artifactId>
        <packaging>nar</packaging>
        <version>version</version>
        <name>desc</name>

        <build>
                <plugins>
                        <plugin>
                                <groupId>com.github.maven-nar</groupId>
                                <artifactId>nar-maven-plugin</artifactId>
                                <configuration>
                                        <libraries>
                                                <library>
                                                        <linkCPP>false</linkCPP>
                                                        <type>shared</type>
                                                        <run>true</run>
                                                </library>
                                        </libraries>
                                </configuration>
                        </plugin>
                </plugins>
        </build>

        <profiles>
                <profile>
                        <id>Linux C++ compile</id>
                        <activation>
                                <os>
                                        <family>unix</family>
                                        <name>linux</name>
                                </os>
                        </activation>
                        <build>
                                <pluginManagement>
                                        <plugins>
                                                <plugin>
                                                        <groupId>com.github.maven-nar</groupId>
                                                        <artifactId>nar-maven-plugin</artifactId>
                                                        <version>${nar.maven.plugin.version}</version>
                                                        <extensions>true</extensions>

                                                        <configuration>
                                                                <cpp>
                                                                        <name>gcc</name>
                                                                        <includes>
                                                                                <include>**/*.cpp</include>
                                                                        </includes>
                                                                        <options>
                                                                                <option>-D__int64=int64_t</option>
                                                                                <option>-I${JDK_HOME}/include</option>
                                                                                <option>-I${JDK_HOME}/include/linux</option>
                                                                                <option>${stack.protector.option}</option>
                                                                                <option>${architecture.option}</option>
                                                                                <option>${subsystem.option}</option>
                                                                                <option>${debug.option}</option>
                                                                                
                                                                                <option>-m64</option>
                                                                                <option>-fPIC</option>
                                                                                <option>-std=c++11</option>
                                                                                <option>-pipe</option>
                                                                                <option>-MMD</option>
                                                                                <option>-pthread</option>
                                                                                <option>-msse2</option>
                                                                                <option>-mfpmath=sse</option>
                                                                                <option>-Wall</option>
                                                                                <option>-Wno-reorder</option>
                                                                                <option>-Wno-sign-compare</option>
                                                                                <option>-Wc++11-compat</option>
                                                                                <option>-fdiagnostics-color=auto</option>
                                                                                <option>-O3</option>
                                                                                <option>-mtune=generic</option>
                                                                                
                                                                                <option>-shared</option>
                                                                                <option>-fexceptions</option>
                                                                        </options>
                                                                </cpp>

                                                                <linker>
                                                                        <name>gcc</name>
                                                                        <options>
                                                                                <option>${architecture.option}</option>
                                                                                <option>${subsystem.option}</option>
                                                                        </options>
                                                                        <sysLibs>
                                                                                <sysLib>
                                                                                        <name>stdc++</name>
                                                                                </sysLib>
                                                                        </sysLibs>
                                                                        <libs>
                                                                                <lib>
                                                                                        <name>jvm</name>
                                                                                        <type>shared</type>
                                                                                        <directory>${JDK_HOME}/jre/lib/${os.arch}/server</directory>
                                                                                </lib>
                                                                        </libs>
                                                                </linker>
                                                        </configuration>
                                                </plugin>
                                        </plugins>
                                </pluginManagement>
                        </build>
                </profile>
        </profiles>

```

- Generated files:
   - xxx-${VERSION}-amd64-Linux-gcc-shared.nar: include lib/amd64-Linux-gcc/shared/libxxx-${VERSION}.so and history.xml
   - xxx-${VERSION}-noarch.nar: include header files in include/:
   - Only has META-INF/maven/xxx with  pom.properties and pom.xml; and  META-INF/nar/xxx/nar.properties
