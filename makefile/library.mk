NAME=foo
VERSION=1.0.0

LIB_NAME=${NAME}-${VERSION}
LIB_FULLNAME=lib${LIB_NAME}.so

CC_SRCS=$(wildcard *.cc)
CC_TEST_SRCS=$(wildcard test*.cc) main.cc
LIB_CC_SRCS=$(filter-out ${CC_TEST_SRCS},${CC_SRCS})

LIB_OBJS=$(patsubst %.cc,%.o,${LIB_CC_SRCS})

CPP_FLAGS+= -Wall -Werror -fpic

#main:tasks

tasks: ${LIB_FULLNAME} ${NAME}


${LIB_FULLNAME}:${LIB_OBJS}
        ${CXX} -shared -o $@ $<

%.o:%.cc
        ${CXX} ${CPP_FLAGS} -c -o $@  $<

clean:
        ${RM} -rf *.o *~

cleanall: clean
        ${RM} -rf *.so
        ${RM} -rf ${NAME}

${NAME}: main.cc
        ${CXX} -L./ -Wall -o $@ $< -l${LIB_NAME}

#LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH

print:
        @echo "cc sources:" ${CC_SRCS}
        @echo "cc test sources:" ${CC_TEST_SRCS}
        @echo "lib cc sources:" ${LIB_CC_SRCS}
        @echo "lib cc objs:" ${LIB_OBJS}
