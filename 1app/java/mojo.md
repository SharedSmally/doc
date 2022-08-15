# Mojo

One plugin has one or more Mojo. Each Mojo is assigned to one Goal name. One goal can be assigned to one or more phases. Its configuration could be within execution, or configuration. 

## create a Mojo plugin
```
mvn archetype:create 
  -DgroupId=[group_id]
  -DartifactId=[artifact_id]
  -DarchetypeArtifactId=maven-archetype-mojo
```

- Plugin Prefix Mapping, typically named as:
```
<yourplugin>-maven-plugin
```
- Run the plugin
```
    mvn groupId:artifactId:version:goal
    mvn sample.plugin:hello-maven-plugin:1.0-SNAPSHOT:sayhi
```
- Add plugin's groupId to be searched by default. In ${user.home}/.m2/settings.xml file:
```
    <pluginGroups>
      <pluginGroup>sample.plugin</pluginGroup>
    </pluginGroups>
```
- Parameters
```
@Parameter
private boolean myBoolean;  //    <myBoolean>true</myBoolean>
private Integer myInteger;  //    <myInteger>10</myInteger>
private Double myDouble;    //    <myDouble>1.0</myDouble>
private Date myDate;        //    <myDate>2005-10-06 2:22:55.1 PM</myDate>
private File myFile;        //    <myFile>c:\temp</myFile>  File/Directory
private URL myURL;          //    <myURL>http://maven.apache.org</myURL>
char, Character, StringBuffer, and String for text
private Color myColor;      //    <myColor>GREEN</myColor>  // enum
private String[] myArray;   //    <myArray><param>value1</param><param>value2</param></myArray>
// Collections: any class which implements java.util.Collection such as ArrayList or HashSet
private List myList;        //    <myList><param>value1</param><param>value2</param></myList>
// Maps: any class which implements java.util.Map such as HashMap
private Map myMap;          //   <myMap><key1>value1</key1><key2>value2</key2></myMap>
// Properties: any map which implements java.util.Properties
private Properties myProperties;     //<myProperties><property><name>propertyName1</name><value>propertyValue1</value></property>
                                     //   <property><name>propertyName2</name><value>propertyValue2</value></property></myProperties>
// Object Classes:any class not implement java.util.Map, java.util.Collection, or java.util.Dictionary.
private MyObject myObject;           //<myObject><myField>test</myField></myObject>
```

## Tips
- Get project directory
Add  maven-project dependency:
```
<groupId>org.apache.maven</groupId><artifactId>maven-project</artifactId><scope>provided</scope>
```
Get the project:
```
@Parameter(readonly = true, defaultValue = "${project}")
private MavenProject project;

/**
 * The maven project.
 * 
 * @parameter expression="${project}"
 * @readonly
 */
private MavenProject project;

this.model = project.getModel();
this.build = model.getBuild();
this.finalName = build.getFinalName();
this.targetDir = new File(build.getDirectory());
```
Get the build path
```
/**
 * @parameter expression="${project.build.directory}/${project.build.finalName}"
 * @readonly
 */
private File outputPath;
```

