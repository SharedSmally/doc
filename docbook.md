# Docbook
- [asciidoc](http://asciidoc.org/): converts an AsciiDoc text file to HTML or DocBook 
    a2x : A toolchain manager for AsciiDoc (converts Asciidoc text files to other file formats) 
- [DocBook] to pdf:
- [cover page design](http://doccookbook.sourceforge.net/html/en/dbc.fo.cover.html)

A makefile sample:
```
# targets
TARGETS = book article page

# From https://xmlgraphics.apache.org/fop/
FOP=~/app/fop-2.3/fop/fop
# From https://cdn.docbook.org/
FOP_XSL=~/app/docbook-xsl-snapshot/fo/docbook.xsl
XHTML_XSL=~/app/docbook-xsl-snapshot/xhtml/docbook.xsl

# docbook spec: https://docbook.org/specs/
# docbook reference:https://tdg.docbook.org/ 
#   http://docbook.sourceforge.net/release/xsl/current/doc/
# http://sagehill.net/book-description.html
DOC_ARGS = -param header.rule 0 \
           -param footer.rule 0 \
	   -param suppress.footer.navigation 1 \
	   -param double.sided 1  \

PDF_TARGETS = $(addsuffix .pdf, ${TARGETS})
HTML_TARGETS = $(addsuffix .html, ${TARGETS})
#################################################
main: 

pdf: ${PDF_TARGETS}

html: ${HTML_TARGETS}

%.pdf:%.xml 
	${FOP} -xml $< -xsl ${FOP_XSL} -pdf $@ \
	${DOC_ARGS}

%.html:%.xml 
    xsltproc -o $@ ${XHTML_XSL} $<

clean:
    rm -rf *.html *.pdf
```

Book sample
```
<?xml version="1.0" encoding="UTF-8"?>

<book xmlns='http://docbook.org/ns/docbook'>
  <title>An Example Book</title>
  <titleabbrev>Example</titleabbrev>
  <info>
    <legalnotice><para>No notice is required.</para></legalnotice>
    <author><personname>
      <firstname>Norman</firstname><surname>Walsh</surname>
    </personname></author>
  </info>

  <dedication>
     <para>
      This book is dedicated to you.
     </para>
  </dedication>

  <preface>
    <title>Foreword</title>
    <para>
        Some content is always required.
    </para>
  </preface>

  <chapter>
    <title>A Chapter</title>
    <para>
        Content is required in chapters too.
    </para>
  </chapter>

  <appendix>
    <title>Optional Appendix</title>
    <para>
        Appendixes are optional.
    </para>
 </appendix>
</book>
```

## [Docbook xml](https://docbook.org/)
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
## standard [v5.0](https://www.oasis-open.org/standards#dbv5.0)

## Examples
### keycombo-keysym
```
<para>
   You can exit from GNU Emacs with<menuchoice>
   <shortcut><keycombo><keysym>C-x</keysym><keysym>C-c</keysym></keycombo></shortcut>
   <guimenu>Files</guimenu><guimenuitem>Exit Emacs</guimenuitem></menuchoice>.
</para>
<para>
   The <keycap>F1</keycap> key on an IBM PC keyboard generates the
   scan code <keycode>0x3B</keycode> when pressed.  This value
   is defined as <keysym>KEY_F1</keysym> in 
   <filename class="headerfile">keyboard.h</filename>.
</para>
```
### guimeniitem
```
<para os="windows">You can exit most Windows applications by selecting
   <guimenuitem><accel>Q</accel>uit</guimenuitem> or
   <guimenuitem>E<accel>x</accel>it</guimenuitem> from
   the <guimenu><accel>F</accel>ile</guimenu> menu.
</para>
```

### mouse
```
<para>
   Select a region of text by dragging the mouse pointer with the
   <mousebutton>left</mousebutton> mouse button depressed.  Copy the
   selected text to a new location by placing the mouse pointer at the
   desired position and pressing the <mousebutton>middle</mousebutton>
   button.
</para>
```

### [Cover Page](http://doccookbook.sourceforge.net/html/en/dbc.fo.cover.html) from titlepage.templates.xml
##### Recto (Right) Page

This is the main page and the content appears in the following order:

    - the book title, from /book/title or /book/info/title
    - the book subtitle, from /book/subtitle or /book/info/subtitle
    - the book's author, from /book/info/author|corpauth/authorgroup
    - the edition, from /book/info/edition*
    - the itemmset, from /book/info/itermset

##### Verso (Left) Page

This usually holds the imprint and the content appears in the following order:

    - the book's title and subtitle in a smaller font size
    - the author, from /book/info/author
    - the edition, from /book/info/edition
    - othercredit
    - pubdate
    - copyright
    - abstract
    - some legal text (copyright), from /book/info/legalnotice
    - the ISBN, from /book/info/biblioid with class and the value isbn

### footnote
```
<para>An annual percentage rate (<abbrev>APR</abbrev>) of 13.9%<footnote>
   <para>The prime rate, as published in the <citetitle>Wall Street
   Journal</citetitle> on the first business day of the month,
   plus 7.0%.</para></footnote>
   will be charged on all balances carried forward.
</para>
```

### link - tag - anchor - olink -  : xref

## [Docbook xsl](https://cdn.docbook.org/): 
Goto https://github.com/docbook/xslt10-stylesheets/releases; and download docbook-xsl-snapshot.tar.gz

## [pandoc](http://pandoc.org/index.html): convert docbook xml to other format
```
$ pandoc --from docbook --to epub3 --output myDocbook.epub myDocbook.xml

$ pandoc --from docbook --to markdown --output myDocbook.md myDocbook.xml

$ pandoc --from docbook --to html --output myDocbook.html myDocbook.xml

$ pandoc --from docbook --to latex --output myDocbook.pdf myDocbook.xml
```
