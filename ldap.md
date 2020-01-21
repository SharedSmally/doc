# LDAP


*top* is an abstract object class that is the parent of every LDAP object class. It is the one that defines 
that every object in LDAP must have an objectClass attribute. The LDAP entries always has "objectClass = top".

## Sample of \*.ldif file
- [auth using ldap in Spring](https://spring.io/guides/gs/authenticating-ldap/)


## 
- [Schema, Class and Attribute](https://www.zytrax.com/books/ldap/ch3/)
- [LDIF] (https://gerardnico.com/security/ldap/attribute)
- [Object Classes and Attributes](https://www.zytrax.com/books/ldap/ape/)
- [Class Types](http://www.ldapexplorer.com/en/manual/107060000-ldap-object-classes.htm)
    - Structural Class 
    - Abstract Classes
    - Auxiliary Classes
    
## objectClass definition
```
ObjectClassDescription = "(" whsp
 numericoid whsp      ; ObjectClass identifier
 [ "NAME" qdescrs ]
 [ "DESC" qdstring ]
 [ "OBSOLETE" whsp ]
 [ "SUP" oids ]       ; Superior ObjectClasses
 [ ( "ABSTRACT" / "STRUCTURAL" / "AUXILIARY" ) whsp ]
                      ; default structural
 [ "MUST" oids ]      ; AttributeTypes
 [ "MAY" oids ]       ; AttributeTypes
  extensions 
	whsp ")"  
```
sample
```
objectclass ( 2.5.6.2 NAME 'country' DESC 'RFC2256: a country'
  SUP top STRUCTURAL
  MUST c
  MAY ( searchGuide $ description ) )
```

## Attribute definition
```
AttributeTypeDescription = "(" whsp
   numericoid whsp     ; AttributeType identifier
 [ "NAME" qdescrs ]             ; name used in AttributeType
 [ "DESC" qdstring ]            ; description
 [ "OBSOLETE" whsp ]
 [ "SUP" oid ]                  ; derived from this other
                                ; AttributeType
 [ "EQUALITY" woid              ; Matching Rule name
 [ "ORDERING" woid              ; Matching Rule name
 [ "SUBSTR" woid ]              ; Matching Rule name
 [ "SYNTAX" whsp noidlen whsp ] ; Syntax OID
 [ "SINGLE-VALUE" whsp ]        ; default multi-valued
 [ "COLLECTIVE" whsp ]          ; default not collective
 [ "NO-USER-MODIFICATION" whsp ]; default user modifiable
 [ X-ORDERED whsp type ]        ; non-standard - default not X-ORDERED
 [ "USAGE" whsp AttributeUsage ]; default userApplications
 extensions
 whsp ")"
```
sample
```
attributetype ( 2.5.4.41 NAME 'name'
  EQUALITY caseIgnoreMatch
  SUBSTR caseIgnoreSubstringsMatch
  SYNTAX 1.3.6.1.4.1.1466.115.121.1.15{32768} )
  
attributetype ( 2.5.4.3 NAME ( 'cn' 'commonName' ) SUP name )  
```
