# Makefile
## Tutorial
- https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

## app makefile
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

## lib makefile
```
NAME=cpw
VERSION=1.0.0

CXXFLAGS += -std=c++17 -I./ -lrt

SRCS=$(wildcard *.cc)
TEST_SRCS=$(wildcard *Test.cc)
OBJ_SRCS=$(filter-out ${TEST_SRCS}, ${SRCS})

OBJS=$(OBJ_SRCS:.cc=.o)

LIB_NAME=lib${NAME}-${VERSION}.so
LIB_FULL_NAME=lib${NAME}-${VERSION}.so

main: ${OBJS} ${TESTS}

%Test: ${OBJS}
  ${GCC} -shared -o ${LIB_FULL_NAME} $<
  
clean:
  ${RM} ${OBJS}
cleanall: clean
  ${RM} ${TESTS}

print:
  @echo " lib: ${LIB_FULL_NAME}"
  @echo " Objs: ${OBJS}"
```
```
