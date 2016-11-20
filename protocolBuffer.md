[Protocol Buffer] (https://developers.google.com/protocol-buffers/)
======

## Download Protocol Buffer
- Protoc Platform: (bin/protoc and include/google/protobuf/*.prot for non-cxx compile) 
  - Linux
  - Windows
  - MacOSX
- Language Compiler:
 - [CXX](https://github.com/google/protobuf/blob/master/src/README.md) : (Compile with: ./configure --prefix=xxx;  make &&  make install)
 - ObjectiveC
 - C Sharp
 - Java 
 - JavaScript
 - PHP
 - Python
 - Ruby
## [Guide](https://developers.google.com/protocol-buffers/docs/overview)

## [Reference](https://developers.google.com/protocol-buffers/docs/reference/overview)

## [Protoc Buffer v3](https://developers.google.com/protocol-buffers/docs/reference/proto3-spec)
  
### Protocol File
``` script
proto = syntax { import | package | option | topLevelDef | emptyStatement }
topLevelDef = message | enum | service
```
Sample
``` script 
syntax = “proto3”;
import public “other.proto”;
option java_package = "com.example.foo";
enum EnumAllowingAlias {
  option allow_alias = true;
  UNKNOWN = 0;
  STARTED = 1;
  RUNNING = 2 [(custom_option) = "hello world"];
}
message outer {
  option (my_option).a = true;
  message inner {   // Level 2
    int64 ival = 1;
  }
  repeated inner inner_message = 2;
  EnumAllowingAlias enum_field =3;
  map<int32, string> my_map = 4;
}
```
#### Syntax
```
syntax = "syntax" "=" quote "proto3" quote ";"
```
#### Import 
The import statement is used to import another .proto's definitions.
```
import = "import" [ "weak" | "public" ] strLit ";" 
```
Example:
```
import public "other.proto";
```
#### Package
The package specifier can be used to prevent name clashes between protocol message types.
```
package = "package" fullIdent ";"
```
Example:
```
package foo.bar;
```
#### Option
Ssed in proto files, messages, enums and services. An option can be a protobuf defined option or a custom option. 
```
option = "option" optionName  "=" constant ";"
optionName = ( ident | "(" fullIdent ")" ) { "." ident }
```
Example:
```
option java_package = "com.example.foo";
```
#### Top Level definitions

##### Enum definition
The enum definition consists of a name and an enum body. The enum body can have options and enum fields. Enum definitions must start with enum value zero.
``` script
enum = "enum" enumName enumBody
enumBody = "{" { option | enumField | emptyStatement } "}"
enumField = ident "=" intLit [ "[" enumValueOption { ","  enumValueOption } "]" ]";"
enumValueOption = optionName "=" constant
```
Example:
``` script
enum EnumAllowingAlias {
  option allow_alias = true;
  UNKNOWN = 0;
  STARTED = 1;
  RUNNING = 2 [(custom_option) = "hello world"];
}
``` 

##### Message definition
A message consists of a message name and a message body. The message body can have fields, nested enum definitions, nested message definitions, options, oneofs, map fields, and reserved statements.
``` script
message = "message" messageName messageBody
messageBody = "{" { field | enum | message | option | oneof | mapField |
reserved | emptyStatement } "}"
``` 
Example:
``` script
message Outer {
  option (my_option).a = true;
  message Inner {   // Level 2
    int64 ival = 1;
  }
  map<int32, string> my_map = 2;
}
``` 
##### Service definition
``` script
service = "service" serviceName "{" { option | rpc | stream | emptyStatement } "}"
rpc = "rpc" rpcName "(" [ "stream" ] messageType ")" "returns" "(" [ "stream" ]
messageType ")" (( "{" {option | emptyStatement } "}" ) | ";")
``` 
Example:
``` script
service SearchService {
  rpc Search (SearchRequest) returns (SearchResponse);
}
``` 
#### Fields
Fields are the basic elements of a protocol buffer message. Fields can be normal fields, oneof fields, or map fields. A field has a type and field number.
```
type = "double" | "float" | "int32" | "int64" | "uint32" | "uint64"
      | "sint32" | "sint64" | "fixed32" | "fixed64" | "sfixed32" | "sfixed64"
      | "bool" | "string" | "bytes" | messageType | enumType
fieldNumber = intLit;
```

#### Normal field
Each field has type, name and field number. It may have field options.
```
field = [ "repeated" ] type fieldName "=" fieldNumber [ "[" fieldOptions "]" ] ";"
fieldOptions = fieldOption { ","  fieldOption }
fieldOption = optionName "=" constant
```
Examples:
```
foo.bar nested_message = 2;
repeated int32 samples = 4 [packed=true];
```
#### Oneof and oneof field
A oneof consists of oneof fields and a oneof name.
```
oneof = "oneof" oneofName "{" { oneofField | emptyStatement } "}"
oneofField = type fieldName "=" fieldNumber [ "[" fieldOptions "]" ] ";"
```
Example:
```
oneof foo {
    string name = 4;
    SubMessage sub_message = 9;
}
```
#### Map field
```
A map field has a key type, value type, name, and field number. The key type can be any integral or string type.
mapField = "map" "<" keyType "," type ">" mapName "=" fieldNumber [ "[" fieldOptions "]" ] ";"
keyType = "int32" | "int64" | "uint32" | "uint64" | "sint32" | "sint64" |
          "fixed32" | "fixed64" | "sfixed32" | "sfixed64" | "bool" | "string"
```
Example:
```
map<string, Project> projects = 3;
```
#### Reserved
Reserved statements declare a range of field numbers or field names that cannot be used in this message.
```
reserved = "reserved" ( ranges | fieldNames ) ";"
fieldNames = fieldName { "," fieldName }
```
Examples:
```
reserved 2, 15, 9 to 11;
reserved "foo", "bar";
```
#### Types:
    - boolean: bool ("true" | "false" )
    - integer32:[int32,uint32,sint32; fixed32,sfixed32];
    - integer64:[int64,uint64,sint64; fixed64,sfixed64];
    - float: double, float
    - string: string; bytes
    - enum
    
 ``` script
  type = "double" | "float" | "int32" | "int64" | "uint32" | "uint64"
      | "sint32" | "sint64" | "fixed32" | "fixed64" | "sfixed32" | "sfixed64"
      | "bool" | "string" | "bytes" | messageType | enumType
 ``` 
