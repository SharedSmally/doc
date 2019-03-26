GTEST_HOME=~/src/googletest-release-1.8.1/googletest

main: tests

tests:tests.cpp
        ${CXX} -o tests tests.cpp -I ${GTEST_HOME}/include -lm -L ${GTEST_HOME}/lib/.libs -lgtest -lpthread


# export LD_LIBRARY_PATH=${GTEST_HOME}/lib/.libs:${LD_LIBRARY_PATH}
$ ./tests
