main: cxx header

cxx: 
	for file in `ls *.cc` ; do \
		$(call update,$$file ) ; \
		$(call replace,$$file ) ; \
	done

header: 
	for file in `ls *.h` ; do \
		$(call update,$$file ) ; \
		$(call replace,$$file ) ; \
	done


define updateEcho
    echo "update file:" $(1)
endef

define update
    echo "update file:" $(1); \
    if [ ! -w $(1) ]; then /usr/local/bin/p4 edit $(1); fi
endef

define replace
    echo "replace file:" $(1); \
    sed -i 's/OMASUPL/SLP/g' $(1)
endef
