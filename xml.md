## xml entities

### GENERAL entity declarations:
- INTERNAL (PARSED) GENERAL ENTITY Declaration: Generally reference text/data that an XML processor has to parse.
```
<!ENTITY name "entity_value">
```
entity value: any character that is not an '&', '%' or ' " ', a parameter entity reference ('%Name;'), an entity reference ('&Name;') or a Unicodeglossary character reference.
```
<?xml version="1.0" standalone="yes" ?>
<!DOCTYPE author [
  <!ENTITY js "Jo Smith">
]>
<author>&js;</author>
```
- EXTERNAL (PARSED) GENERAL ENTITY Declaration: Generally reference text/data that an XML processor has to parse, used to creat a common reference shared by multiple documents.
```
<!ENTITY name SYSTEM "URI">
<!ENTITY name PUBLIC "public_ID" "URI">
```
  - URI: In practice, this is a URL where the external parsed entity can be found.
  - public_ID: This may be used by an XML processor to generate an alternate URI where the external parsed entity can be found. If it cannot be found at this URI, the XML processor must use the normal URI.
```
<?xml version="1.0" standalone="no" ?>
<!DOCTYPE copyright [
  <!ENTITY c SYSTEM "http://www.xmlwriter.net/copyright.xml">
]>
<copyright>&c;</copyright>
<?xml version="1.0" standalone="no" ?>
<!DOCTYPE copyright [
  <!ENTITY c PUBLIC "-//W3C//TEXT copyright//EN" "http://www.w3.org/xmlspec/copyright.xml">
]>
<copyright>&c;</copyright>
```
- EXTERNAL (UNPARSED) GENERAL ENTITY Declaration: generally reference non-XML data that an XML processor does not have to parse.
```
<!ENTITY name SYSTEM "URI" NDATA name>
<!ENTITY name PUBLIC "public_ID" "URI" NDATA name>

<?xml version="1.0" standalone="no" ?>
<!DOCTYPE img [
  <!ENTITY logo SYSTEM "http://www.xmlwriter.net/logo.gif" NDATA gif>
  <!NOTATION gif PUBLIC "gif viewer">
]>
<img src="logo"/>
<?xml version="1.0" standalone="no" ?>
<!DOCTYPE img [
  <!ENTITY logo PUBLIC  "-//W3C//GIF logo//EN" "http://www.w3.org/logo.gif" NDATA gif>
  <!NOTATION gif PUBLIC "gif viewer">
]>
<img src="logo"/>
```
