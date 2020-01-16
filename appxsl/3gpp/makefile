# download 3gpp docs for 5G:
RELEASE=15 16
SERIES=29 38

main: ${RELEASE}

${RELEASE}:
        for series in ${SERIES}; do \
                ./x3gpp2mk.pl R$@_S$$series.txt R$@_S$$series.mk $@ $$series; \
                make -f R$@_S$$series.mk;  \
        done;

clean:
        ${RM} *.mk
