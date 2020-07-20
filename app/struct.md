# Data Object

## Basic Types 
- bool
- int8,int16,int32,int64
- uint8,uint16,uint32,uint64
- float32,float64,complex32,complex64
- string
- bits:uintX, enum:intX

## Container Types
- array<T>:N(uint32): Fixed Size
- vector<T>/set<T>: Variant Size
- map<K,T>:
- union: 

## struct: new data type
- field:
   type, name, size?, initial_value

## type: alias to existing data type. C++ typedef
```
<type name="" class="array:XXX|vector|set|map" template="">
    <template>
</type>
```
Similar to [ FIDL ](https://fuchsia.dev/fuchsia-src/development/languages/fidl)/ [ Protocol-buffer ](https://developers.google.com/protocol-buffers).

## Definitions: publicid systemid
```
<dao xmlns="" publicid="ref_id" namespace="">
   <include local="localfile"/>*
   
   <import ref="id" local="localfile" as=""/>*
   
   <struct>
      <field name="fieldName" type="fieldType" container="array/vector/set" size="min..max|fixedSize" default=""/>*
   </struct>*
   <bits name="" size="1|2|4|8" >  unsigned integer
      <bit name="" />*
   </bits>
   <enum name="" size="1|2|4|8" >  integer
      <item name="" value="" literal="" />*
   </enum>
   <union name="">
      <field name="fieldName" type="fieldType" container="array/vector/set" size="min..max|fixedSize" default=""/>*
   </bits>
   
   <type name="" container="array/vector/set" type="" size="" />
   <map name="" key="key_type" value="value_type"/>
</dao>
```
- include file; same namespace.
- import file as xxx; in different namespace; href="HREF_ID"

### Schema
- In an XML instance document, the value of @schemaLocation is a link to the XML Schema
```
<dao xsi:schemaLocation="https://xxx/xxx.xsd"
     xmlns="https://xxx.com/schema/v1.0.0/dao.xsd"
     xmlns:dao="https://xxx.com/schema/v1.0.0/dao.xsd"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     systemid="xxx.xml" namespace="">
    
    <include local=""/>
    <import ref="" local="" alias=""/>
    
    <struct name="">
        <field name="name" type="ns:type"
    </struct
</dao>
```

- Links in an XML Schema document:
```
   <include schemaLocation="... link ..." />
   <import schemaLocation="... link ..." namespace="XYZ" />
```

- Links in an XSLT document:
```
   <include href="... link ..." />
   <import href="... link ..." />
   document('... link ...')
   doc ('... link ...')
```   
