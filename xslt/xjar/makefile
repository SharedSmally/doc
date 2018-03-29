main: cfg

-include xjar.cfg

cfg: xjar.cfg

xjar.cfg:xjar.xml
	xsl ./xjar.xsl $< $@

clean:
	rm -rf *.cfg
	rm -rf *.pom.xml
	
deploy: ${DEPLOY_TARGETS}
