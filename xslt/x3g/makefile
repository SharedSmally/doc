#################################################
# subdirs:
#  XDOC_HOME/x3gpp/download/$name/*.zip(*.html;*.xhtml):
#  XDOC_HOME/x3gpp/doc$name/vx.y.z/*.doc:
#  X3GPP_HOME/$category/$name/vx.y.z/(makefile;pom.xml;meta/)
#################################################
-include x3gpp.cfg
#################################################

#################################################
main: init x3gpp.cfg

init:
	@if [ ! -z "$(X3G_ZIP_DIR)" ]; then mkdir -p $(X3G_ZIP_DIR); fi
	@if [ ! -z "$(X3G_DOC_DIR)" ]; then mkdir -p $(X3G_DOC_DIR); fi
	 
x3gpp.cfg:x3gpp.xml
	xsl meta/x3gpp.xsl x3gpp.xml x3gpp.cfg

#################################################
cleanall:
	${RM} -rf x3gpp.cfg
	${RM} -rf ${SUBDIRS}

#################################################
cfg:
	for p in ${SUBDIRS}; do \
		cd $$p && make $@ && cd ../;  \
	done

gen:
	for p in ${SUBDIRS}; do \
		cd $$p && make $@ && cd ../;  \
	done

pkg:
	for p in ${SUBDIRS}; do \
		cd $$p && make $@ && cd ../;  \
	done

deploy:
	for p in ${SUBDIRS}; do \
		cd $$p && make $@ && cd ../;  \
	done
	
clean:
	for p in ${SUBDIRS}; do \
		cd $$p && make $@ && cd ../;  \
	done

#################################################
	
#################################################

	


	
