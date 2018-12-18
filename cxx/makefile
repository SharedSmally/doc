SOURCES_CC = $(wildcard *.cc)

TESTS_CC = $(wildcard test*.cc)
TESTS = $(basename ${TESTS_CC}) 

OBJECTS_CC=$(filter-out $(TESTS_CC),$(SOURCES_CC))
OBJECTS=$(patsubst %.cc,%.o,$(OBJECTS_CC))

CPPFLAGS += -I./ -std=c++11 -std=c++1y
CXXFLAGS +=
LDFLAGS  += -lpthread

make: ${OBJECTS} test

test:${TESTS}

test%:test%.cc
	g++ -o $@ $< ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} 

clean:
	${RM} ${TESTS}

cleanall: clean
	${RM} ${OBJECTS}
	
print:
	@echo "Test Sources: " ${TESTS_CC}
	@echo "Test targets: " ${TESTS}
