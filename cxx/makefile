TESTS_CC = $(wildcard test*.cc)
TESTS = $(basename ${TESTS_CC})

CPP_FLAGS += -std=c++11
CXX_FLAGS +=
LD_FLAGS  += -lpthread

make: test

test:${TESTS}

test%:test%.cc
        g++ -o $@ $< ${CPP_FLAGS} ${CXX_FLAGS} ${LD_FLAGS}

clean:
        ${RM} ${TESTS}

print:
        @echo "Test Sources: " ${TESTS_CC}
        @echo "Test targets: " ${TESTS}
