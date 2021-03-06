
# XSLFO:
## [Tutorial](https://www.alt-soft.com/tutorial/)
## [Page Layout](https://www.webucator.com/tutorial/learn-xsl-fo/page-layout.cfm)

## Region:
XSL-FO uses the following elements to define the regions of a page:
- <fo:region-body> defines the body region
- <fo:region-before> defines the top region (header)
- <fo:region-after> defines the bottom region (footer)
- <fo:region-start> defines the left region (left sidebar)
- <fo:region-end> defines the right region (right sidebar)

The four other region tags take all the same attributes as <fo:region-body> except for the margin attributes. These regions do not have margins. They always sit on the edge of the simple-page-master rectangle. In addition, these region tags take two other attributes: extent and precedence.

- The extent attribute specifies the width of region-start and region-end and the height of region-before and region-after (assuming a portrait layout).
- region-before, region-after, region-start, and region-end is a part of the region-body. To avoid text in the region-body to overwrite text in the other regions, the region-body must have margins at least the size of these regions.
- The precedence attribute specifies which regions should sit on top. As you can see from the examples we have looked at thus far, by default region-start and region-end take precedence over region-before and region-after. The following code sample shows how to change this.

- The margin specified in the <fo:region-body> tag forces the region-body edges in one inch from the simple-page-master rectangle.
- The padding specified in the <fo:region-body> tag creates space between the content of the region-body and the edges of the region-body.



## bookmark-tree
```
  <fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format"> 
   ...
   <fo:bookmark-tree>
     <fo:bookmark internal-destination="s-1" starting-state="show">
       <fo:bookmark-title>Typical Xml2PDF workflow</fo:bookmark-title>
       <fo:bookmark internal-destination="ss-1_0">
         <fo:bookmark-title>Contents</fo:bookmark-title>
       </fo:bookmark>
       <fo:bookmark internal-destination="ss-1_1">
         <fo:bookmark-title>Why XML</fo:bookmark-title>
       </fo:bookmark>
       <fo:bookmark internal-destination="ss-1_2">
         <fo:bookmark-title>Why PDF</fo:bookmark-title>
       </fo:bookmark>
     </fo:bookmark>
   </fo:bookmark-tree>
  </fo:root>

  <fo:page-sequence master-reference="all-pages">
     ...
     <fo:flow flow-name="xsl-region-body">
       <fo:block id="s-1">Typical Xml2PDF workflow </fo:block>
       <fo:block id="ss-1_0">Table of Contents</fo:block>
       <fo:block id="ss-1_1">Why XML</fo:block>
       <fo:block>Extensible Markup Language (XML) is a simple and very flexible... </fo:block>
       <fo:block id="ss-1_2"> Why PDF </fo:block>
       <fo:block> Free Adobe Reader guarantees that PDF will be viewed identically.. </fo:block>
  </fo:page-sequence>
```

## link
```
   <fo:page-sequence master-reference="simple">
        <fo:flow flow-name="xsl-region-body">
			<fo:block space-after="10pt">
				Beatles
			</fo:block>
			<fo:list-block start-indent="20pt">
				<fo:list-item>
					<fo:list-item-label end-indent="label-end()">
						<fo:block font-weight="bold">
							<fo:character character="&#x2022;" />
						</fo:block>
					</fo:list-item-label>
					<fo:list-item-body start-indent="body-start()">
						<fo:block>
							<fo:basic-link 	external-destination="url('http://www.paulmccartney.com')" 
								color="blue" text-decoration="underline">
									Paul McCartney
							</fo:basic-link>
						</fo:block>
					</fo:list-item-body>
				</fo:list-item>
				<fo:list-item>
					<fo:list-item-label end-indent="label-end()">
						<fo:block font-weight="bold">
							<fo:character character="&#x2022;" />
						</fo:block>
					</fo:list-item-label>
					<fo:list-item-body start-indent="body-start()">
						<fo:block>
							<fo:basic-link 
								internal-destination="ss-1_1"   # block with id="ss-1_1" 
								color="blue" text-decoration="underline">
									John Lennon
							</fo:basic-link>
						</fo:block>
					</fo:list-item-body>
				</fo:list-item>
			</fo:list-block>
			
			<fo:block space-after="10pt">
				<fo:external-graphic src="url('Images/beatles.jpg')" width="340px" height="238px"/>
		        </fo:block>
             </fo:flow>
	</fo:page-sequence>
```
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
```
<fo:block margin-top="12pt">Table with row borders:</fo:block>
<fo:table>
 <fo:table-body>
  <fo:table-row border-width="4px" border-style="solid">
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>?</fo:block></fo:table-cell>
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>U+2602</fo:block></fo:table-cell>
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>Umbrella</fo:block></fo:table-cell>
  </fo:table-row>
  <fo:table-row border-width="4px" border-style="solid">
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>?</fo:block></fo:table-cell>
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>U+260E</fo:block></fo:table-cell>
   <fo:table-cell background-color="#ffccff" padding="8pt">
    <fo:block>Telephone</fo:block></fo:table-cell>
  </fo:table-row>
 </fo:table-body>
</fo:table>
<fo:block margin-top="12pt">Table with column borders:</fo:block>
<fo:table>
 <fo:table-column border-width="4px" border-style="solid"/>
 <fo:table-column border-width="4px" border-style="solid"/>
 <fo:table-column border-width="4px" border-style="solid"/>
 <fo:table-body>
  <fo:table-row>
   <fo:table-cell 
    padding="8pt"><fo:block>?</fo:block></fo:table-cell>
   <fo:table-cell 
    padding="8pt"><fo:block>U+262E</fo:block></fo:table-cell>
   <fo:table-cell 
    padding="8pt"><fo:block>Peace</fo:block></fo:table-cell>
  </fo:table-row>
  <fo:table-row>
   <fo:table-cell 
    padding="8pt"><fo:block>?</fo:block></fo:table-cell>
   <fo:table-cell 
    padding="8pt"><fo:block>U+262F</fo:block></fo:table-cell>
   <fo:table-cell 
    padding="8pt"><fo:block>Yin Yang</fo:block></fo:table-cell>
  </fo:table-row>
 </fo:table-body>
</fo:table> 
```
