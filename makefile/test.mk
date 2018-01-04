CPPFLAGS += -I./ -std=c++11

TEST_SRCS=$(wildcard test*.cc)
TESTS=$(TEST_SRCS:.cc=)

main:${TESTS}

test%:test%.cc
	${CXX} -o  $@ $< ${CPPFLAGS}
	
clean:
	${RM} -rf ${TESTS}	
  
