NAME=asn1

main: cfg deploy

-include ${NAME}.cfg

cfg: ${NAME}.cfg

${NAME}.cfg:${NAME}.xml
	xsl ./xjar.xsl $< $@

clean:
	rm -rf *.cfg
	rm -rf *.pom.xml
	
deploy: ${DEPLOY_TARGETS}
