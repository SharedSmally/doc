NAME=cpw.kafka
VERSION=1.0.0
LIBNAME=lib${NAME}-${VERSION}.so

KAFKA_HOME=~/TSDK/librdkafka-0.9.4

ALL_cc=$(wildcard *.cc)
TESTS_cc=$(wildcard test*.cc)
TESTS=$(basename ${TESTS_cc})

LIBS_cc=$(filter-out $(TESTS_cc),$(ALL_cc))
LIBS_o=$(patsubst %.cc,%.o,${LIBS_cc})

CPPFLAGS += -std=c++17 -fPIC
CPPFLAGS += -I . -I ${KAFKA_HOME}/include 
LDFLAGS += -L ${KAFKA_HOME}/lib -lrdkafka -lrdkafka++
#LDFLAGS += -L./ -lcpw.odbc-1.0.0
LDFLAGS += -L ./ -lcpw.kafka

CXXFLAGS +=  -DTEST -lpthread

#main: ${LIBS_o} ${TESTS}
main: ${LIBNAME} ${TESTS}

#test%:test%.cc ${LIBS_o}
#	g++ -o $@ $< ${CPPFLAGS} ${CXXFLAGS} ${LIBS_o} ${LDFLAGS}
test%:test%.cc ${LIBNAME}
	${CXX} -o $@ $< ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS}

clean:
	${RM} ${TESTS} ${LIBS_o}

cleanall: clean
	${RM} ${LIBNAME}
	${RM} lib${NAME}.so
	${RM} lib${NAME}.so.1

lib:${LIBNAME}
	
${LIBNAME}: ${LIBS_o}
	${CXX} -shared -Wl,-soname,lib${NAME}.so.1 -o $@ ${LIBS_o} 
	ln -sf ${LIBNAME} lib${NAME}.so
	ln -sf ${LIBNAME} lib${NAME}.so.1

print:
	@echo "library sources=${LIBS_cc}"
	@echo "library objects=${LIBS_o}"
	@echo "test sources=${TESTS_cc}"
	@echo "test targets=${TESTS}"

env:
	@echo "export LD_LIBRARY_PATH=.:${KAFKA_HOME}/lib:"'\${LD_LIBRARY_PATH}'
