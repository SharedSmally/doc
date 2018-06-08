- Eliminate empty namespace :  xmlns=""
   1. In the stylesheet, define exclude-result-prefixes:
   ```
   <xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:jpw="http://www.jpw.com/xsl/app"
    exclude-result-prefixes="xsl xs jpw"
    version="2.0">
   ```
   2. In the output root node, set xmlns. Will not output xmlns if it is not in exclude-result-prefixes list.
   ```
   <catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog">
   ```
   3. In the child node, set the same xmlns as the root. Otherwise will output xmlns="":
   ```
    <public publicId ="{@namespace}" uri="{$uri}" xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog"/> 
    ```
