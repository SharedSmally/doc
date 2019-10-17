NAME=cpw
VERSION=1.0.0

ALL_cc=$(wildcard *.cc)
TESTS_cc=$(wildcard test*.cc)
TESTS=$(basename ${TESTS_cc})

LIBS_cc=$(filter-out $(TESTS_cc),$(ALL_cc))
LIBS_o=$(patsubst %.cc,%.o,${LIBS_cc})

CPPFLAGS += -I ./ -g

CXXFLAGS += -std=c++11 -DTEST -lpthread

main: ${LIBS_o} ${TESTS}

test%:test%.cc ${LIBS_o}
	g++ -o $@ $< -I ./ ${CXXFLAGS} ${LIBS_o}

clean:
	${RM} ${TESTS} ${LIBS_o}

print:
	@echo "library sources=${LIBS_cc}"
	@echo "library objects=${LIBS_o}"
	@echo "test sources=${TESTS_cc}"
	@echo "test targets=${TESTS}"
