# XSL 1.1 Nodes

# fo:root
```
(layout-master-set,declarations?,bookmark-tree?,(page-sequence|page-sequence-wrapper)+)
```

## layout-master-set
```
(simple-page-master|page-sequence-master|flow-map)+
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

###
