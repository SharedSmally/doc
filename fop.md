## [W3 XSL](https://www.w3.org/Style/XSL/)
- XSL Transformations (XSLT)
- XML Path Language (XPath)
- XML Query Langyage (XQuery)
- XSL Formatting Objects (XSL-FO): [v1.1](https://www.w3.org/Style/XSL/https://www.w3.org/Style/XSL/)

## Tutorial
- [Apache FOP Quick Start](https://xmlgraphics.apache.org/fop/quickstartguide.html)
- [Tidy](http://www.html-tidy.org/): convert html to xhtml
- [fop in w3school](http://w3schools.sinsixx.com/xslfo/default.asp.htm)
- [xml to fop samples](https://www.antennahouse.com/xml-to-xsl-fo-stylesheets/)
     - [html2fo](https://www.antennahouse.com/XSLsample/sample-xsl-xhtml2fo/xhtml2fo.xsl)

## [Apache FOP](https://xmlgraphics.apache.org/fop/)
- Command: 
```
fop -xml name.xml -xsl name2fo.xsl -pdf name.pdf
```
- XSLT 2.0:
Specify the processor implementation used by FOP by adding a VM parameter to the start script where org.apache.fop.cli.Main is called. Example for Saxon:
```
-Djavax.xml.transform.TransformerFactory=net.sf.saxon.TransformerFactoryImpl
```

## XSL-FO
The *<fo:root>* object is the root (top) node for XSL-FO documents.

The children of the *<fo:root>* object are a single *<fo:layout-master-set>* object that holds all masters used in the document, an optional *<fo:declarations>* object, and one or more *<fo:page-sequence>* objects.

```
<?xml version="1.0" encoding="ISO-8859-1"?>
<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">

<fo:layout-master-set>
  <fo:simple-page-master master-name="A4">
    <!-- Page template goes here -->
  </fo:simple-page-master>
</fo:layout-master-set>

<fo:page-sequence master-reference="A4">
  <!-- Page content goes here -->
</fo:page-sequence>
</fo:root>
```

- Page templates
XSL-FO uses page templates called "Page Masters" to define the layout of pages. Each template must have a unique name:
```
<fo:simple-page-master master-name="intro">
  <fo:region-body margin="5in" />
</fo:simple-page-master>
<fo:simple-page-master master-name="left">
  <fo:region-body margin-left="2in" margin-right="3in" />
</fo:simple-page-master>
<fo:simple-page-master master-name="right">
  <fo:region-body margin-left="3in" margin-right="2in" />
</fo:simple-page-master>

<fo:simple-page-master master-name="A4"
 page-width="297mm" page-height="210mm"
 margin-top="1cm"   margin-bottom="1cm"
 margin-left="1cm"  margin-right="1cm">
  <fo:region-body   margin="3cm"/>
  <fo:region-before extent="2cm"/>
  <fo:region-after  extent="2cm"/>
  <fo:region-start  extent="2cm"/>
  <fo:region-end    extent="2cm"/>
</fo:simple-page-master>
```
    - XSL-FO Page Size
         - page-width defines the width of a page
         - page-height defines the height of a page
    - XSL-FO Page Margins
         - margin-top defines the top margin
         - margin-bottom defines the bottom margin
         - margin-left defines the left margin
         - margin-right defines the right margin
         - margin defines all four margins
    - XSL-FO Page Regions
         - region-body defines the body region
         - region-before defines the top region (header)
         - region-after defines the bottom region (footer)
         - region-start defines the left region (left sidebar)
         - region-end defines the right region (right sidebar)

- Page
 XSL-FO uses <fo:page-sequence> elements to define output pages.
  - Each output page refers to a page master which defines the layout.
  - Each output page has a <fo:flow> element defining the output.
  - Each output page is printed (or displayed) in sequence.
 XSL-FO pages are filled with content from the <fo:flow> element. 
  - The <fo:flow> element contains all the elements to be printed to the page.
  - When the page is full, the same page master will be used over (and over) again until all the text is printed.
 XSL-FO output is normally nested inside <fo:block> elements: "Blocks" of content "Flow" into "Pages" of the output media.
```
<fo:page-sequence>
  <fo:flow flow-name="xsl-region-body">
    <fo:block>
      <!-- Output goes here -->
    </fo:block>
  </fo:flow>
</fo:page-sequence>
```

- [Block](http://w3schools.sinsixx.com/xslfo/xslfo_blocks.asp.htm)
Blocks are sequences of output in rectangular boxes:
```
<fo:block
  border-width="1mm">
This block of output will have a one millimeter border around it.
</fo:block>
```

The common area properties:
- space before and space after: the empty space separating the block from the other blocks.
- margin:the empty area on the outside of the block. 
- border: the rectangle drawn around the external edge of the area. It can have different widths on all four sides. can also be filled with different colors and background images.
- padding: the area between the border and the content area
- content area: contains the actual content like text, pictures, graphics, or whatever.
```
<fo:block
    font-size="14pt" font-family="verdana" color="red"
    space-before="5mm" space-after="5mm">
title
</fo:block>
<fo:block
    text-indent="5mm"
    font-family="verdana" font-size="12pt"
    space-before="5mm" space-after="5mm">
contents
</fo:block>
```

- Table
There are nine XSL-FO objects used to create tables:
   - fo:table-and-caption
   - fo:table
   - fo:table-caption
   - fo:table-column
   - fo:table-header
   - fo:table-footer
   - fo:table-body
   - fo:table-row
   - fo:table-cell
XSL-FO uses the <fo:table-and-caption> element to define a table. It contains a <fo:table> and an optional <fo:caption> element.

The <fo:table> element contains optional <fo:table-column> elements, an optional <fo:table-header> element, a <fo:table-body> element, and an optional <fo:table-footer> element. Each of these elements has one or more <fo:table-row> elements, with one or more <fo:table-cell> elements:
```
<fo:table-and-caption>
<fo:table>
<fo:table-column column-width="25mm"/>
<fo:table-column column-width="25mm"/>

<fo:table-header>
  <fo:table-row>
    <fo:table-cell>
      <fo:block font-weight="bold">Car</fo:block>
    </fo:table-cell>
    <fo:table-cell>
      <fo:block font-weight="bold">Price</fo:block>
    </fo:table-cell>
  </fo:table-row>
</fo:table-header>

<fo:table-body>
  <fo:table-row>
    <fo:table-cell>
      <fo:block>Volvo</fo:block>
    </fo:table-cell>
    <fo:table-cell>
      <fo:block>$50000</fo:block>
    </fo:table-cell>
  </fo:table-row>
  <fo:table-row>
    <fo:table-cell>
      <fo:block>SAAB</fo:block>
    </fo:table-cell>
    <fo:table-cell>
      <fo:block>$48000</fo:block>
    </fo:table-cell>
  </fo:table-row>
</fo:table-body>
</fo:table>
</fo:table-and-caption>
```

- List
There are four XSL-FO objects used to create lists:
  - fo:list-block: the whole list
  - fo:list-item: each item in the list
  - fo:list-item-label: the label for the list-item - typically an <fo:block> containing a number, character, etc.
  - fo:list-item-body: the content/body of the list-item - typically one or more <fo:block> objects
```
<fo:list-block>
<fo:list-item>
 <fo:list-item-label>
   <fo:block>*</fo:block>
 </fo:list-item-label>
 <fo:list-item-body>
   <fo:block>Volvo</fo:block>
 </fo:list-item-body>
</fo:list-item>

<fo:list-item>
 <fo:list-item-label>
   <fo:block>*</fo:block>
 </fo:list-item-label>
 <fo:list-item-body>
   <fo:block>Saab</fo:block>
 </fo:list-item-body>
</fo:list-item>
</fo:list-block>
```


### FOP XSLT
```
<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0"
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:fo="http://www.w3.org/1999/XSL/Format">
  <xsl:output method="xml" indent="yes"/>
  
  <xsl:template match="/">
    <fo:root>
      <fo:layout-master-set>
        <fo:simple-page-master master-name="A4-portrait"
              page-height="29.7cm" page-width="21.0cm" margin="2cm">
          <fo:region-body/>
        </fo:simple-page-master>
      </fo:layout-master-set>
      
      <fo:page-sequence master-reference="A4-portrait">
        <fo:flow flow-name="xsl-region-body">
          <fo:block>
            Hello, <xsl:value-of select="name"/>!
          </fo:block>
        </fo:flow>
      </fo:page-sequence>
    </fo:root>
  </xsl:template>
</xsl:stylesheet>
```

## [XSL-FO nodes](http://w3schools.sinsixx.com/xslfo/xslfo_reference.asp.htm)
```
<fo:root>
  	Contents:layout-master-set,declarations?, page-sequence+
 </fo:root>
```
### Layout
```
<fo:layout-master-set>
	Contents:(simple-page-master|page-sequence-master)+
</fo:layout-master-set>

<fo:simple-page-master>
	Contents:(region-body,region-before?, region-after?,region-start?,region-end?)
</fo:simple-page-master>

<fo:page-sequence-master>
	Contents:(single-page-master-reference|	repeatable-page-master-reference| repeatable-page-master-alternatives)+
</fo:page-sequence-master>

<fo:single-page-master-reference master-reference=""/>
<fo:repeatable-page-master-reference master-reference="" maximum-repeats=""/>
<fo:repeatable-page-master-alternatives maximum-repeats="">
	Contents:(conditional-page-master-reference+)
</fo:repeatable-page-master-alternatives>
<fo:conditional-page-master-reference blank-or-not-blank="" master-reference="" odd-or-even="" page-postion=""/>
```
### Page
```
<fo:page-sequence>
	Contents:title?,static-content*,flow
</fo:page-sequence>

<fo:title>
	Contents:(#PCDATA|bidi-override|character|external-graphic| instream-foreign-object|inline|inline-container|leader|page-number|page-number-citation|basic-link| multi-toggle)*
</fo:title>

<fo:static-content flow-name="">
  Contents:(block|block-container| table-and-caption|table|list-block)+
</fo:static-content>

<fo:flow flow-name="">
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:flow>
```
### Block
```
<fo:block-container>
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:block-container>

<fo:block>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|
	page-number-citation|basic-link|multi-toggle| block|block-container|table-and-caption|table|list-block)*
</fo:block>
```

### Table
```
<fo:table-and-caption>
	Contents:(table-caption?,table)  
</fo:table-and-caption>

<fo:table>
	Contents:(table-column*,table-header?, table-footer?,table-body+)
</fo:table>

<fo:table-caption>
	Contents:(block|block-container|list-block)+
</fo:table-caption>

<fo:table-header>
	Contents:(table-row+|table-cell+)
</fo:table-header>

<fo:table-footer>
	Contents:(table-row+|table-cell+)
</fo:table-footer>

<fo:table-body>
	Contents:(table-row+|table-cell+)
</fo:table-body>

<fo:table-row>
	Contents:(table-cell+)
</fo:table-row>

<fo:table-cell>
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:table-cell>

<fo:table-column/>
```
### list
```
<fo:list-block>
	Contents:(list-item+)
</fo:list-block>

<fo:list-item>
  Contents:(list-item-label,list-item-body)
</fo:list-item>

<fo:list-item-label>
	Contents:(block|block-container| table-and-caption|table|list-block| list-item)+
</fo:list-item-label>

<fo:list-item-body>
	Contents:(block|block-container| table-and-caption|table|list-block| list-item)+
</fo:list-item-body>
```

### inline
```
<fo:inline-container>
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:inline-container>

<fo:inline>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:inline>
```
### Multi
```
<fo:multi-switch auto-restore="" id="" role="" source-document="">
	Contents:(multi-case+)
</fo:multi-switch>

<fo:multi-case>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:multi-case>

<fo:multi-toggle id="" role="" source-document="" switch-to="">
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|	page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption| table|list-block)*
</fo:multi-toggle>

<fo:multi-properties>
	Contents:(multi-property-set+,wrapper)
</fo:multi-properties>

<fo:multi-property-set active-state="" id=""/>

<fo:wrapper id="">
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:wrapper>
```

### Misc
```
<fo:page-number attrs=""/>
<fo:page-number-citation attrs=""/>

<fo:character attrs=""/>
<fo:initial-property-set attrs=""/>
<fo:external-graphic attrs=""/>
<fo:instream-foreign-object attrs="">
	 Contents:(non-XSL namespace (a common format is SVG))
</fo:instream-foreign-object>

<fo:float float="" clear="">
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:float>

<fo:declarations>
	Contents:(color-profile)+
</fo:declarations>
<fo:color-profile color-profile-name="" rendering-intent="" src=""/>

<fo:marker>
	Contents:(#PCDATA|bidi-override| character|external-graphic| instream-foreign-object|inline| inline-container|leader|page-number|page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:marker>
<fo:retrieve-marker retrieve-boundary="" retrieve-class-name="" retrieve-position="">

<fo:leader>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|page-number|page-number-citation|basic-link|multi-toggle)*
</fo:leader>

<fo:footnote>
	Contents:(inline|footnote-body)
</fo:footnote>
<fo:footnote-body>
	Contents:(block|block-container|table-and-caption|table|list-block)+
</fo:footnote-body>

<fo:basic-link>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|page-number|page-number-citation|	basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:basic-link>

<fo:bidi-override>
	Contents:(#PCDATA|bidi-override|character|external-graphic|instream-foreign-object|inline|inline-container|leader|page-number|page-number-citation|basic-link|multi-toggle|block|block-container|table-and-caption|table|list-block)*
</fo:bidi-override>
```
