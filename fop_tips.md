
# XSLFO:
## [Tutorial](https://www.alt-soft.com/tutorial/)
## Page numbers and its references in XSL-FO
To incert the current page number the <fo:page-number> is used. See a simple example below:
```
   <fo:static-content flow-name="xsl-region-after">
     <fo:block text-align="center">
       Page <fo:page-number/>
     </fo:block>
   </fo:static-content>
```
If you want to make a reference to a certain page use <fo:page-number-citation>. A referenced page must have a unique id. See the example below:
```
   ...
   <fo:block>
     ...Illegal drugs present a very big problem for the Government. 
     You can see the statistics on page <fo:page-number-citation ref-id="stat"/>. 
   </fo:block>
   ...
   <fo:table id="stat">
     ....
   </fo:table>
```
To get the total number of pages in the document there are two methods:

You can use the <fo:page-number-citation-last> element.
```
   <fo:static-content flow-name="xsl-region-after">
     <fo:block text-align="center">
       Page <fo:page-number/> of <fo:page-number-citation-last/>
     </fo:block>
   </fo:static-content>
```
And it is also possible to use already known <fo:page-number> element. In this case you should place an empty <fo:block> element at the end of the text and then make a reference to its page number.
```
<fo:static-content flow-name="xsl-region-after">
     <fo:block text-align="center">
       Page <fo:page-number/> of <fo:page-number-citation ref-id="end"/>
     </fo:block>
   </fo:static-content>
   ...
   <fo:block id="end"/>
```

## XSLFO initial-page-number inserting blank page
 Where there are 2 <fo:page-sequence> defined and you are setting the second to an initial number 1 and it falls on an even page; Usually odd page numbers are on the opposite side of even numbered pages, so the parser adds a blank page to the first page sequence to keep the numbering system in order.

To override this behaviour you need to add force-page-count="no-force" to the first sequence :
```
<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <fo:layout-master-set>
        <fo:simple-page-master master-name="my-master">
            <fo:region-body/>
        </fo:simple-page-master>
    </fo:layout-master-set>
    <fo:page-sequence master-reference="my-master" force-page-count="no-force">
        <fo:flow flow-name="xsl-region-body">
            <fo:block>First Sequence</fo:block>
        </fo:flow>
    </fo:page-sequence>
    <fo:page-sequence master-reference="my-master" initial-page-number="1">
        <fo:flow flow-name="xsl-region-body">
            <fo:block>Second sequence</fo:block>
        </fo:flow>
    </fo:page-sequence>
</fo:root>
```
## Marker
Markers are used to produce running headers or footers and dynamic table headers or footers. There are two XSL-FO elements used to create markers:
- <fo:marker>
- <fo:retreive-marker>
The <fo:marker> is used first to undicate the element. It can be used with block- or inline-level formatting objects and should be placed inside <fo:flow> only. The <fo:marker> should also be the initial child of its parent element. The <fo:marker> has only one attribute - marker-class-name - used as an identifier when retrieving an element.
- The <fo:retreive-marker> is used as a descendant of an <fo:static-content> element to match an <fo:marker> found in the <fo:flow>.
- The <fo:retreive-table-marker> has the same functionality as the <fo:retreive-marker>. The only difference is that it is used for tables.

```
   <fo:static-content flow-name="header">
     <fo:block text-align="right">
       <fo:retrieve-marker retrieve-class-name="chapter"/>
     </fo:block>
   </fo:static-content>
   <fo:flow flow-name="contents" font-family="Calibri" font-size="12pt">
     <fo:block>
       <fo:marker marker-class-name="chapter">
         Chapter 1.
       </fo:marker>
       <fo:block font-weight="bold">
         Chapter 1.
       </fo:block>
       <fo:block>
         This chapter containt the information about...
       </fo:block>
     </fo:block>
   </fo:flow>
  ``` 

## Rotate text
Rotates the at 90 degree but counterclockwise:
```
<fo:block-container reference-orientation="90" space-before="20pt">
<fo:block text-align="right"> 
Some text
</fo:block>
</fo:block-container>
```
## Add watermark
You can add an image to the page background by using background-image= on <region-body>. XSL-FO does not support rendering text as a background.

or Using SVG
```
<fo:block-container z-index="-1" position="absolute" left="5pt" top="5pt" width="100%" height="100%">
   <fo:block>
       <fo:instream-foreign-object>
           <svg xmlns="http://www.w3.org/2000/svg" width="680" height="920">
               <text font-family="Arial Black" font-size="55pt" style="fill:rgb(255,192,192)" x="-10" y="300" width="680" text-anchor="middle" transform="rotate(-54, 340, 15)">Watermark Sample Here</text>
           </svg>
        </fo:instream-foreign-object>
    </fo:block>
</fo:block-container>
```

## Add Table: Apach not support table-and-caption
```
        <fo:flow flow-name="xsl-region-body">
            <fo:block>         
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
            </fo:block>

   <fo:table>
     <fo:table-column column-width="20%"/>
     <fo:table-column column-width="80%"/>
     <fo:table-body>
       <fo:table-row>
         <fo:table-cell>
           <fo:block margin="12pt" font-weight="bold" font-size="8pt">
		     Serif 8pt:
           </fo:block>
         </fo:table-cell>
         <fo:table-cell>
           <fo:block margin="12pt" font-size="8pt">
		     The quick brown fox jumps over the lazy dog!
           </fo:block>
         </fo:table-cell>
       </fo:table-row>
       <fo:table-row>
         <fo:table-cell>
           <fo:block margin="12pt" font-weight="bold" font-size="8pt">
		     Serif 36pt:
           </fo:block>
         </fo:table-cell>
         <fo:table-cell>
           <fo:block margin="12pt" font-size="36pt">
		     The quick brown fox jumps over the lazy dog!
           </fo:block>
         </fo:table-cell>
       </fo:table-row>
     </fo:table-body>
   </fo:table>
```
