###########################################
CPPFLAGS += -I./ -std=c++11

CC_SRCS=$(wildcard *.cc)
TEST_SRCS=$(wildcard *Test.cc)
OBJ_SRCS=$(filter-out $(TEST_SRCS),$(CC_SRCS))

OBJS=$(OBJ_SRCS:.cc=.o)
TESTS=$(TEST_SRCS:.cc=)

debug: DEFINE += -DDEBUG
debug: CPPFLAGS += -g

opt:CPPFLAGS += -O2

.PHONY : clean

#CPPFLAGS= -fPIC -g
#LDFLAGS= -shared

###########################
-include lib.mk
LIBNAME=$(NAME)-${VERSION}.so
###########################################
main: build

build: ${OBJS} ${TEST_TARGETS}

%Test:%Test.cc 
	${CXX} -o $@ $< ${OBJS} -std=c++11 -lpthread -I./

#%.o:%.cc
#	g++ -c $@ $< ${OBJS} -std=c++11 -lpthread -I./

lib:${OBJS}
	${CXX} -shared -o ${LIBNAME} ${OBJS}
	
clean:
	${RM} -rf ${OBJS} *Test

init:
	@export NS=com.cpw.core
	@for cls in ${CLASSES}; do \
    	class $$cls ; \
	done
	
print:
	@echo SRCS: ${CC_SRCS}
	@echo OBJS: ${OBJS}
	@echo TESTS: ${TESTS}
	@echo CLASSES: ${CLASSES}
###########################################
#gcc -fPIC -g -c -Wall a.c
#gcc -shared -Wl,-soname,libmystuff.so.1 -o libmystuff.so.1.0.1 a.o b.o -lc
    
