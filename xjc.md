## xjc

### catalog file: -catalog *catalogfile*
- catalog files may includes the imported files from the direct imported files.
- needs for importing files (solve the import files): mapping shcemaLocation(http://xxx) for systemId, or namespace for publicId, to the local file (uri; refer to catalog file).  See [Articles](https://dzone.com/articles/jaxb-xjc-imported-schemas-and)
```
<import namespace="urn:ietf:params:xml:ns:iris1" />
:
<public publicId="urn:ietf:params:xml:ns:iris1"
        uri = "../../iris1/1.0/meta/xsd/iris1.xsd"/>   uri is the local xsd fle refering  to the catalog file

<import namespace="urn:ietf:params:xml:ns:iris1"
        schemaLocation="gml4xls.xsd" />    
 without catalog file, need to find gml4xls.xsd with the same directory (refer to *.xsd)
 
    <system
        systemId="http://www.example.com/address/address.xsd"
        uri="imports/address.xsd"/>
 for system  system mapping:
    <xs:import
        schemaLocation="http://www.example.com/address/address.xsd"
        namespace="http://www.example.com/address"/>
If import schemaLocation is local file, such as schemaLocation="iris1.xsd"; then iris1.xsd must be in the same directory.

    <public
        publicId="http://www.example.com/phone-number"
        uri="imports/phone-number.xsd"/>
 for a public mapping based on the namespace URI:
    <xs:import
         namespace="http://www.example.com/phone-number"/>

The following import can be used with a system mapping using schemaLocation:
<xs:import
    schemaLocation="http://www.example.com/address/address.xsd"
    namespace="http://www.example.com/address"/>
 
This import requires a public mapping based on the namespace URI:
<xs:import
    namespace="http://www.example.com/phone-number"/>
```
```
<!DOCTYPE catalog
    PUBLIC "-//OASIS//DTD Entity Resolution XML Catalog V1.0//EN"
           "http://www.oasis-open.org/committees/entity/release/1.0/catalog.dtd">
<catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog">
    <public
        publicId="iris1.xsd"
        uri = "../../iris1/1.0/meta/xsd/iris1.xsd"/>
    <system
        systemId="http://www.example.com/address/address.xsd"
        uri = "../../iris1/1.0/meta/xsd/iris1.xsd"/>
</catalog>
```
### Generate epsiode files: episode epsFile
- Generated episode file can be used as jaxb as -b epsFile
- Generated episode file define the mapping bwtween xml nodes and class names. The mapping for the imported files may be redefined if not related episode files provided in -b.
- Generated and reused by xjc for the classes mapping; Also need to solve the import files via catalog. If the imported files are solved, the related classes will not be generated if epsiode files is used. 

### Use binding files: -b bindFile
- Customize classes mapping
- Simple type: 
- One epsiode file for one * -b file.epi *. Use generated -epsiode needs -extension.  
- schemaLocation: refer the local xsd file, node to specify the base node.
```
<jxb:bindings version="2.0"
      xmlns:jxb="http://java.sun.com/xml/ns/jaxb"
      xmlns:xs="http://www.w3.org/2001/XMLSchema" >

    <jxb:bindings schemaLocation="xlink.xsd" node="/xs:schema">

        <jxb:bindings node="//xs:attributeGroup[@name='locatorAttrs']">
            <jxb:bindings node=".//xs:attribute[@ref='xlink:title']">
                <jxb:property name="title1"/>
            </jxb:bindings>
        </jxb:bindings>

        <jxb:bindings node="//xs:attributeGroup[@name='arcAttrs']">
            <jxb:bindings node=".//xs:attribute[@ref='xlink:title']">
                <jxb:property name="title2"/>
            </jxb:bindings>
        </jxb:bindings>
    </jxb:bindings>

</jxb:bindings>
```

### For imported files; need generated epsiode file and related xsd file (from catalog file). With epsiode file ( -b \*.epi ), the classes from imported files will not be regenerated. 
