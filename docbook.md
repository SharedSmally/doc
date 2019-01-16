# Docbook (https://docbook.org/)
## [Docbook xml] (https://docbook.org/)
The root element is [article](https://docbook.org/schemas/sdocbook/elements/article.html):
```
((title,subtitle?,titleabbrev?)?,
 articleinfo?,
 (((itemizedlist|orderedlist|variablelist|note|literallayout|
    programlisting|para|blockquote|mediaobject|informaltable|
    example|figure|table|sidebar|abstract|authorblurb|epigraph)+,
   section*)|
  section+),
 ((appendix)|
  bibliography)*)
```
## stqandard [v5.0](https://www.oasis-open.org/standards#dbv5.0)

## [Docbook xsl] (https://cdn.docbook.org/)

## [pandoc](http://pandoc.org/index.html): convert docbook xml to other format
```
$ pandoc --from docbook --to epub3 --output myDocbook.epub myDocbook.xml

$ pandoc --from docbook --to markdown --output myDocbook.md myDocbook.xml

$ pandoc --from docbook --to html --output myDocbook.html myDocbook.xml

$ pandoc --from docbook --to latex --output myDocbook.pdf myDocbook.xml
```
