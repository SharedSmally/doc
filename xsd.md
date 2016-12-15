
XSD
======

### XSD String Data Types
- xsd:anySimpleType
    - **xsd:QName**:  _[prefix_NCName : ]_local_NCName
    - **xsd:string**
        - **xsd:normalizedString** : no CR,LF,TAB, muitiple SPs
             - **xsd:token** : no leading/trailing SP and multiple SPs, coudl be one SP
                 - restricted by **xsd:language**
                 - restricted by **xsd:NMTOKEN**:  (no SP)
                      - used in list **xsd:NMTOKENS**
                 - **xsd:Name**: (XML Name, start with letter, underscore (\_), colon(:))
                      - **xsd:NCName**: (non-colonized name, no colon :)
                          - restricted by **xsd:ID** (unique within XML document)
                          - restricted by **xsd:IDREF**
                              - used in list xsd:IDREFS
                          - restricted by **xsd:ENTITY**
                              - used in list **xsd:ENTITIES**

- string:  xsd:string
 
   The generic string type

- NormalizedString: xsd:normalizedString (derived from xsd:string)

   The type xsd:normalizedString represents a character string that may contain any Unicode character allowed by XML. 
   The processor replaces each carriage return, line feed, and tab by a single space.

- Token: xsd:token (derived from xsd:normalizedString)

   The type xsd:token represents a character string that may contain any Unicode character allowed by XML. Certain characters, 
   namely the "less than" symbol (<) and the ampersand (&), must be escaped (using the entities &lt; and &amp;, respectively)
   when used in strings in XML instances. The processor replaces each carriage return, line feed, and tab by a single space.
   After this replacement, each group of consecutive spaces is collapsed into one space character, and all leading and trailing
   spaces are removed. 

   - language: xsd:language

  The type xsd:language represents a natural language identifier, generally used to indicate the language of a document or
  a part of a document.Values of the xsd:language type conform to RFC 3066 (two- or three-letter, (usually lowercase) language
  code that conforms to ISO 639, optionally followed by a hyphen and a two-letter, (usually uppercase) country code that conforms to ISO 3166)
   
   - NMTOKEN: xsd:NMTOKEN (derived from xsd:token); used by xsd:NMTOKENS
   
   The type xsd:NMTOKEN represents a single string token. xsd:NMTOKEN values may consist of letters, digits, periods (.), hyphens (\-),
   underscores (\_), and colons (:). They may start with any of these characters. xsd:NMTOKEN has a whiteSpace facet value of collapse,
   so any leading or trailing whitespace will be removed. However, no whitespace may appear within the value itself.

   - Name: xsd:Name (derived from xsd:token)
  
  The type **xsd:Name** represents an XML name, which can be used as an element-type name or attribute name, among other things.
  Specifically, this means that values must start with a letter, underscore(\_), or colon (:), and may contain only letters,
  digits, underscores (\_), colons (:), hyphens (\-), and periods (.). Colons should only be used to separate namespace prefixes
  from local names.
  
       - NCName: xsd:NCName (derived from xsd:Name for unqualified names; sub types:xsd:ID, xsd:IDREF, xsd:ENTITY )
       
   The type xsd:NCName represents an XML non-colonized name, which is simply a name that does not contain colons.
   An xsd:NCName value must start with either a letter or underscore (\_) and may contain only letters, digits, 
   underscores (\_), hyphens (\-), and periods (.).
   
            - ID: xsd:ID (derived from xsd:NCName)
   The type xsd:ID is used for an attribute that uniquely identifies an element in an XML document.
   An xsd:ID value must be an NCName. This means that it must start with a letter or underscore, and can only 
   contain letters, digits, underscores, hyphens, and periods.
                 - Their values must be unique within an XML instance, regardless of the attribute's name or its element name.
                 - A complex type cannot include more than one attribute of type xsd:ID, or any type derived from xsd:ID.
                 - xsd:ID attributes cannot have default or fixed values specified.
                 
            - IDREF: xsd:IDREF (derived from xsd:NCName); used by xsd:IDREFS
   The type xsd:IDREF is used for an attribute that references an ID. All attributes of type xsd:IDREF must reference 
   an xsd:ID in the same XML document.
   
            - ENTITY: xsd:ENTITY (derived from xsd:NCName); used by xsd:ENTITIES
   The type xsd:ENTITY represents a reference to an unparsed entity. The xsd:ENTITY type is most often used to include 
   information from another location that is not in XML format, such as graphics. An xsd:ENTITY value must be an NCName.
   An xsd:ENTITY value carries the additional constraint that it must match the name of an unparsed entity in a document
   type definition (DTD) for the instance.
   
- QName: xsd:QName (based on xsd:anySimpleType )

 The type xsd:QName represents an XML namespace-qualified name. A xsd:QName value consists of a prefix and a local part, 
separated by a colon, both of which are NCName values. _The prefix and colon are optional_, but if they are not present, 
it is assumed that either the name is namespace-qualified by other means (e.g., by a default namespace declaration), or
the name is not in a namespace.


   
