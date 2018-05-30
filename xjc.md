## xjc

### catalog file: -catalog *catalogfile*
- solve the import files: mapping http://xxx (systemId) to local file (uri). See [] 
```
<!DOCTYPE catalog
    PUBLIC "-//OASIS//DTD Entity Resolution XML Catalog V1.0//EN"
    "http://www.oasis-open.org/committees/entity/release/1.0/catalog.dtd">
<catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog">
    <system
        systemId="http://www.openmobilealliance.org/tech/profiles/rest_netapi_common-v1_0.xsd"
        uri="../../rcommon/v1.0.0/meta/xsd/rest_netapi_common-v1_0.xsd"/>

    <system systemId="http://www.w3.org/2001/xml"
        uri="../../common/v1.0.0/xml.xsd"/>

    <system systemId="http://www.w3.org/2001/XMLSchema"
        uri="../../common/v1.0.0/XMLSchema.xsd"/>
</catalog>
```
### epsiode files
- Generated and reused by xjc for the classes mapping

### binding files
- Customize classes mapping

- Simple type: 

