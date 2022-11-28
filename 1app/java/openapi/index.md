# OpenAPI
- Standard: https://swagger.io/specification/ 
- Code Generator

## Tools
- [Swagger]()
      - CLI: https://github.com/swagger-api/swagger-codegen
- [OpenAPI Generator](https://github.com/OpenAPITools/openapi-generator-cli): OpenAPI Generator allows generation of API client libraries (SDK generation), server stubs, documentation and configuration automatically given an OpenAPI Spec (both 2.0 and 3.0 are supported). 
     - CLI:
```
 https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/6.2.1/openapi-generator-cli-6.2.1.jar
```
     - [OpenAPI Generator Maven Plugin](https://github.com/OpenAPITools/openapi-generator/tree/master/modules/openapi-generator-maven-plugin)
```
<plugin>
    <groupId>org.openapitools</groupId>
    <artifactId>openapi-generator-maven-plugin</artifactId>
    <version>6.2.1</version>
    <executions>
        <execution>
            <goals>
                <goal>generate</goal>
            </goals>
            <configuration>
                <inputSpec>${project.basedir}/src/main/resources/api.yaml</inputSpec>
                <generatorName>java</generatorName>
                <configOptions>
                   <sourceFolder>src/gen/java/main</sourceFolder>
                </configOptions>
            </configuration>
        </execution>
    </executions>
</plugin>

mvn clean compile
```
For Spring:
```
<plugin>
   <groupId>org.openapitools</groupId>
   <artifactId>openapi-generator-maven-plugin</artifactId>
   <executions>
      <execution>
         <goals>
            <goal>generate</goal>
         </goals>
         <configuration>
            <inputSpec>
                 ${project.basedir}/src/main/resources/openapi.yml
            </inputSpec>
            <generatorName>spring</generatorName>
            <apiPackage>io.tej.SwaggerCodgen.api</apiPackage>
            <modelPackage>io.tej.SwaggerCodgen.model</modelPackage>
            <supportingFilesToGenerate>
                 ApiUtil.java
            </supportingFilesToGenerate>
            <configOptions>
               <sourceFolder>src/main/java/</sourceFolder>
               <delegatePattern>true</delegatePattern>
               <interfaceOnly>true</interfaceOnly>
            </configOptions>
         </configuration>
      </execution>
   </executions>
</plugin>
```
     - Reference: https://openapi-generator.tech/

## OpenAPI Object
The root document object of the OpenAPI document.
| Field Name	 | Type | 	Description |
|--------------|------|---------------|
|openapi	| string	| REQUIRED. This string MUST be the semantic version number of the OpenAPI Specification version that the OpenAPI document uses. The openapi field SHOULD be used by tooling specifications and clients to interpret the OpenAPI document. This is not related to the API info.version string.|
|info	| [Info Object](https://swagger.io/specification/#info-object)	| REQUIRED. Provides metadata about the API. The metadata MAY be used by tooling as required.|
|servers	| [ [Server Object](https://swagger.io/specification/#server-object) ]	| An array of Server Objects, which provide connectivity information to a target server. If the servers property is not provided, or is an empty array, the default value would be a Server Object with a url value of /.|
|paths	| [Paths Object](https://swagger.io/specification/#paths-object)	|REQUIRED. The available paths and operations for the API.|
|components	| [Components Object](https://swagger.io/specification/#components-object)	| An element to hold various schemas for the specification.|
| security	| [ [Security Requirement Object](https://swagger.io/specification/#security-requirement-object) ]|	A declaration of which security mechanisms can be used across the API. The list of values includes alternative security requirement objects that can be used. Only one of the security requirement objects need to be satisfied to authorize a request. Individual operations can override this definition. To make security optional, an empty security requirement ({}) can be included in the array.|
|tags	| [ [Tag Object](https://swagger.io/specification/#tag-object) ]|	A list of tags used by the specification with additional metadata. The order of the tags can be used to reflect on their order by the parsing tools. Not all tags that are used by the Operation Object must be declared. The tags that are not declared MAY be organized randomly or based on the tools' logic. Each tag name in the list MUST be unique.|
|externalDocs	| [External Documentation Object](https://swagger.io/specification/#external-documentation-object) |	Additional external documentation. |
