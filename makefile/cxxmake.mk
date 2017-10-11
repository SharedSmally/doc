CPPFLAGS += -I./ -std=c++11 -O2

CC_SRCS=$(wildcard *.cc)
TEST_SRCS=$(wildcard *Test.cc)
OBJ_SRCS=$(filter-out $(TEST_SRCS),$(CC_SRCS))

OBJS=$(OBJ_SRCS:.cc=.o)
TESTS=$(TEST_SRCS:.cc=)

main: build

build: ${OBJS} ${TEST_TARGETS}

%Test:%Test.cc
        g++ -o $@ $< ${OBJS} -std=c++11 -lpthread -I./

clean:
        ${RM} -rf ${OBJS} *Test

print:
        @echo SRCS: ${CC_SRCS}
        @echo OBJS: ${OBJS}
        @echo TESTS: ${TESTS}        
