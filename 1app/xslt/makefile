XSL=~/bin/xsl
#XMLS := $(wildcard xml/*.xml)
XMLS := $(shell find xml -name "*.xml")
#HTMLS := $(XMLS: xml/%.xml=html/%.html)
HTMLS :=$(patsubst xml/%.xml,html/%.html,$(XMLS))

#.PHONY: ${HTMLS} help

main: test  #targets

targets: ${HTMLS}
#	@echo "Dependencies for $@ are: $^"

html/%.html:xml/%.xml
	${XSL} xsl/bootstrap.xsl $< $@

clean:
	${RM} -rf html/**

help: ## Show this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
	
list: # list targets
	${shell make -pn | grep -E '^[a-zA-Z0-9_-]+:([^=]|$)' | cut -d: -f1)

test: clean html/page1.html
	more html/page1.html
	
print:
	@echo "XML files: ${XMLS}"
	@echo "HTML files: ${HTMLS}"
