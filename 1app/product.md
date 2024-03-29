# Product Layout
- Product: a list project with the deployment configuration, including platform, os, project, etc.
- Project: a list of applications, libraries and services (dynamically loaded libraries)

## product: product.xml
```
<product name="" version="">
   <arg></arg>
   <project></project>
</project>
```
## project: project.xml 
```
<project name="" version="" namespace="">
   <arg></arg>
   <dependency></dependency>
   <application></application>
   <library></library>
   <service></service>
   <database></database>
   <protocol></protocol>  
   <meta></meta>
</project>
```
### Application: application.xml 
- command-line arg
- library/service/database/protocol

### Library: library.xml 
- module

### Service: service.xml 
- configs(view/config/update/reset;count/gauge/metric)

### Database: database.xml 

### Protocol: protocol.xml 
- message (protocol buffer; binary/json)
- rpc services

#### CXX File: cxxfile.xml 
- import
- cimport
- macro
- typedef
- struct
- class
- function

#### Class: class.xml 
- template
- type
- field
- method
