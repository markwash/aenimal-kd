CXXFLAGS=-g
CFLAGS=-g

CXX_TESTS=\
kdtree_test_basic.h \
kdtree_private_test_basic.h \
kdtree_test_long.h \
simple_vector_test_basic.h \
kdtree_test_nn.h \

OBJS=\
kdtree.o \
simple_vector.o \

all: run_tests kdtree.o

run_tests: cxx_runner
	./cxx_runner

cxx_runner: cxx_runner.cpp ${OBJS}
	g++ ${CXXFLAGS} -o $@ $^

cxx_runner.cpp: ${CXX_TESTS}
	cxxtestgen.py -o $@ --error-printer $^ 

clean:
	rm -f *.o cxx_runner.exe cxx_runner.cpp
