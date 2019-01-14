# XSL 1.1 Nodes

# fo:root
```
<fo:root accessiblity=""
   id="idstring"  index-class="string"  index-key="string"
   media-usage="">
   (layout-master-set,declarations?,bookmark-tree?,(page-sequence|page-sequence-wrapper)+)
</fo:root>
```

## layout-master-set
```
<fo:layout-master-set>
   (simple-page-master|page-sequence-master|flow-map)+
</fo:layout-master-set>
```

## page-sequence & wrapper
```
<fo:page-sequence
   flow-map-reference=""
   master-reference=""
   format=""
   letter-value=""
   grouping-separator=""
   grouping-size=""
   id="idstring"  index-class="string"  index-key="string"
   initial-page-number=""
   force-page-count=""
   reference-orientation=""
   country=""
   language=""
   writing-mode=""
         (title?,folio-prefix?,folio-suffix?,static-content*,flow+)
</page-sequence>

<fo:page-sequence-wrapper id="idstring"  index-class="string"  index-key="string">
    (page-sequence|page-sequence-wrapper)*
</fo:page-sequence-wrapper>

```

## fo:declarations
```
(color-profile)*
<color-profile src="" color-profile-name="" rendering-intent=""/>
```

## bookmark
```
<fo:bookmark-tree>
   (bookmark+)
</fo:bookmark-tree>

<fo:bookmark accessibility="" internalDest="" externalDest="" startingstate="">
   (bookmark-title,bookmark*)
</fo:bookmark>

<fo:bookmark-title accessibility="" color="" font-style="" font-weight="">
    (#PCDATA)
</ fo:bookmark-title>
```

## Pages
### fo:simple-page-master
```
< fo:simple-page-master margin=""
     master-name=""
     page-height=""
     page-width=""
     reference-orientation=""
     writing-mode=""
    >
    (region-body+,region-before?,region-after?,region-start?,region-end?)
</ fo:simple-page-master>

region body:
  margin=""  column-count="" column-gap=""
  border="" padding="" background=""
  clip="" display-align="" overflow=""
  region-name="" reference-orientation="" writing-mode=""

region-before,region-after,region-start,region-end:
  extent="" precedence=""
  border="" padding="" background="" 
  clip="" display-align="" overflow=""
  region-name="" reference-orientation="" writing-mode=""
```

### fo:page-sequence-master
```
<fo:page-sequence-master master-name="">
    (single-page-master-reference|repeatable-page-master-reference|repeatable-page-master-alternatives)+
</fo:page-sequence-master>

<fo:single-page-master-reference master-reference=""/>
<fo:repeatable-page-master-reference master-reference="" maximum-repeats=""/>
<fo:repeatable-page-master-alternatives  maximum-repeats="">
    (conditional-page-master-reference+)
</fo:repeatable-page-master-alternatives>

<fo:conditional-page-master-reference master-reference="" 
     page-position="" odd-or-even="" blank-or-not-blank=""/>
```

### fo:flow-map
```
<fo:flow-map flow-map-name="">
   (flow-assignment+)
</fo:flow-map>
<fo:flow-assignment>
   (flow-source-list,flow-target-list)
</fo:flow-assignment>
<fo:flow-source-list>
   (flow-name-specifier+)
</fo:flow-source-list>
<fo:flow-name-specifier flow-name-reference="">

<fo:flow-target-list>
   (region-name-specifier+)
</ fo:flow-target-list>
<fo:region-name-specifier region-name-reference=""/>
```
## page
### fo:page-sequence

### fo:flow
```
<fo:flow id="" index-class="" index-key="" flow-name="">
    (%block;)+
</fo:flow>

<fo:static-content id="" index-class="" index-key="" flow-name="">
    (%block;)+
</fo:static-content>
```
