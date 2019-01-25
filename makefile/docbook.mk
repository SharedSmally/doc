# targets
TARGETS = book article page

# From https://xmlgraphics.apache.org/fop/
FOP=~/app/fop-2.3/fop/fop
# From https://cdn.docbook.org/
DOC_XSL=~/app/docbook-xsl-snapshot/fo/docbook.xsl

# docbook spec: https://docbook.org/specs/
# docbook reference:https://tdg.docbook.org/ 
#   http://docbook.sourceforge.net/release/xsl/current/doc/
# http://sagehill.net/book-description.html
DOC_ARGS = -param header.rule 0 \
    -param footer.rule 0 \
    -param suppress.footer.navigation 1 \
    -param double.sided 1  \

# For only page, using section/sec1
#################################################
main: $(addsuffix .pdf, ${TARGETS})

%.pdf:%.xml 
  ${FOP} -xml $< -xsl ${DOC_XSL} -pdf $@ \
	${DOC_ARGS}

# Document root element for FO output must be one of the following elements:
#   appendix article bibliography book chapter colophon dedication glossary 
#   index part preface qandaset refentry reference sect1 section set setindex
