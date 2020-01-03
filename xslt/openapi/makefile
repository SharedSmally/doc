FTP_BASE=https://www.3gpp.org/ftp/specs/archive/OpenAPI/
# https://www.3gpp.org/ftp/specs/archive/OpenAPI/Rel-15/
# https://www.3gpp.org/ftp/specs/archive/OpenAPI/Rel-16/

RELS=15 16

main: index

download:
	@for rel in ${RELS} ; do \
		mkdir -p REL-$$rel ; \
		wget ${FTP_BASE}/REL-$$rel/ -O REL-$$rel/index.html ; \
	done

index:
	@for rel in ${RELS} ; do \
		cp REL-$$rel/index.html REL-$$rel/tmp.xml; \
		$(call make_index_xml,REL-$$rel/tmp.xml ); \
		xsl makefile.xsl REL-$$rel/tmp.xml REL-$$rel/makefile; \
	done
	
cleanall:
	@for rel in ${RELS} ; do \
		rm -rf REL-$$rel ; \
	done
	

define make_index_xml
    sed -i 's/<br>/<br\/>/g' $(1); \
    sed -i 's/<hr>/<hr\/>/g' $(1)
endef
