# Web on Bootstrap
- [Tutorial](https://frontbackend.com/thymeleaf/spring-boot-bootstrap-thymeleaf-autocomplete)

## layout:

In src/main/resources
- static/
    - css/: \*.css
    - js/: \*.js
- templates/: \*.html
- application.properties

## pom.xml:
- webjars: bootstrap; webjars-locator
```
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <artifactId>thymeleaf-bootstrap-autocomplete-input</artifactId>

    <properties>
        <bootstrap.version>4.0.0-2</bootstrap.version>
        <jquery.version>2.1.4</jquery.version>
        <webjars-locator.version>0.40</webjars-locator.version>
        <lombok.version>1.18.16</lombok.version>
    </properties>

    <!-- Inherit defaults from Spring Boot -->
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.1.5.RELEASE</version>
    </parent>

    <!-- Add typical dependencies for a web application -->
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-thymeleaf</artifactId>
        </dependency>
        <dependency>
            <groupId>org.webjars</groupId>
            <artifactId>bootstrap</artifactId>
            <version>${bootstrap.version}</version>
        </dependency>
        <dependency>
            <groupId>org.webjars</groupId>
            <artifactId>jquery</artifactId>
            <version>${jquery.version}</version>
        </dependency>
        <dependency>
            <groupId>org.webjars</groupId>
            <artifactId>webjars-locator</artifactId>
            <version>${webjars-locator.version}</version>
        </dependency>

        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <version>${lombok.version}</version>
            <scope>provided</scope>
        </dependency>
    </dependencies>

    <!-- Package as an executable jar -->
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>

</project>
```
- index.html
```
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
<meta charset="ISO-8859-1">
<title>Add Bootstrap to Thymeleaf</title>
<link th:href = "@{/css/bootstrap.min.css}" rel="stylesheet">
</head>
<body>
 <div class = "container">
  <div class = "row">
    <table class = "table table-responsive table-bordered table-striped">
     <thead>
      <tr>
       <th> Employee First Name</th>
       <th> Employee Last Name</th>
       <th> Employee Email</th>
      </tr>
     </thead>
     <tbody>
     <tr th:each="employee : ${employees}">
      <td th:text="${employee.firstName}"></td>
      <td th:text="${employee.lastName}"></td>
      <td th:text="${employee.email}"></td>
     </tr>
    </tbody>
    </table>
  </div>
 </div>
</body>
</html>
```
