
# XSLFO
## 	Page numbers and its references in XSL-FO
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
