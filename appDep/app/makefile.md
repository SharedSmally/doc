# Makefile

## app
```
CXXFLAGS += -std=c++17 -I./ -lrt

SRCS=$(wildcard *.cc)
TEST_SRCS=$(wildcard *Test.cc)
OBJ_SRCS=$(filter-out ${TEST_SRCS}, ${SRCS})

TESTS=$(TEST_SRCS:.cc=)
OBJS=$(OBJ_SRCS:.cc=.o)

main: ${OBJS} ${TESTS}

%Test: %Test.cc ${OBJS}
  ${GCC} -o $@ $< ${CXXFLAGS} ${OBJS}
  
clean:
  ${RM} ${OBJS}
cleanall: clean
  ${RM} ${TESTS}

print:
  @echo " Tests: ${TESTS}"
  @echo " Objs: ${OBJS}"
```
