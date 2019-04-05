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
Use Maven Archetype plugin with goal *create* to create project layout. B=batchMode(no prompt)
```
mvn archetype:generate -B -DgroupId=com.jpw -DarctifactId=common -DpackageName=com.jpw.common -Dversion=1.0.0
```
- Install to local repository(~/.m2/repository)
```
mvn install
```
- Deploy to remote repository(SCM reposotory server)
```
mvn deploy
```
- Run a goal: defined in pom.xml
```
mvn install@install-artifacts
mvn antrun:run@install-artifacts   #run a task defined as id=install-artifacts in goal=run with antrun plugin.
```
The sample pom.xml:
```
  <build>
    <plugins>
  		<plugin>
				<groupId>org.codehaus.mojo</groupId>
				<artifactId>rpm-maven-plugin</artifactId>
				<version>${rpm.plugin.version}</version>
				<configuration>
					<name>${project.artifactId}</name>
					<version>${project.version}</version>
					<release>${release}</release>
					<needarch>true</needarch>
					<license>license message</license>
					<distribution>distributor</distribution>
					<group>location/commonappdata</group>
					<packager>packer</packager>
					<prefix>/opt/${project.artifactId}</prefix>
					<changelogFile>src/changelog</changelogFile>
					<defineStatements>
						<defineStatement>_unpackaged_files_terminate_build 0</defineStatement>
					</defineStatements>
					<mappings>
						<mapping>
							<directory>/opt/${project.artifactId}/meta</directory>
							<filemode>750</filemode>
							<sources>
								<source>
									<location>../meta</location>
								</source>
							</sources>
						</mapping>
					</mappings>

				</configuration>
				<executions>
					<execution>
						<id>package-to-rpm</id>
						<phase>package</phase>
						<goals>
							<goal>rpm</goal>
						</goals>
					</execution>
				</executions>
			</plugin>

			<plugin>
				<artifactId>maven-assembly-plugin</artifactId>
				<version>${assembly.plugin.version}</version>
				<configuration>
					<descriptors>
						<descriptor>${project.basedir}/assembly.xml</descriptor>
					</descriptors>
					<appendAssemblyId>false</appendAssemblyId>
				</configuration>
				<executions>
					<execution>
						<id>make-tgz-file</id>
						<phase>package</phase>
						<goals>
							<goal>single</goal>
						</goals>
					</execution>
				</executions>
			</plugin>
      
			<plugin>
				<groupId>org.apache.maven.plugins</groupId>
				<artifactId>maven-antrun-plugin</artifactId>
				<version>${antrun.plugin.version}</version>
				<executions>
					<execution>
						<id>install-artifacts</id>
						<phase>install</phase>
						<goals>
							<goal>run</goal>
						</goals>
						<configuration>
							<target>
								<taskdef
									resource="net/sf/antcontrib/antcontrib.properties"
									classpathref="maven.plugin.classpath" />
								<taskdef resource="net/sf/antcontrib/antlib.xml"
									classpathref="maven.dependency.classpath" />
								<property environment="env" />
								<property name="root.dir"	location="${project.basedir}/../../.." />
                <!-- list of ant tasks -->
                <echo></echo>
                <if></if>
                <move></move>
                ...
							</target>
						</configuration>
					</execution>                
				</executions>

				<dependencies>
					<dependency>
						<groupId>ant-contrib</groupId>
						<artifactId>ant-contrib</artifactId>
						<version>1.0b3</version>
						<exclusions>
							<exclusion>
								<groupId>ant</groupId>
								<artifactId>ant</artifactId>
							</exclusion>
						</exclusions>
					</dependency>
					<dependency>
						<groupId>org.apache.ant</groupId>
						<artifactId>ant-nodeps</artifactId>
						<version>1.8.1</version>
					</dependency>
					<dependency>
						<groupId>org.apache.maven.plugins</groupId>
						<artifactId>maven-deploy-plugin</artifactId>
						<version>2.7</version>
					</dependency>
				</dependencies>
			</plugin>
		</plugins>
	</build>                
</build>
```
##
