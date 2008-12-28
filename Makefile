CXXFLAGS=-g
CFLAGS=-g

TESTS=\
kdtree_test_basic.h \
kdtree_private_test_basic.h \
kdtree_test_long.h \
simple_vector_test_basic.h \
kdtree_test_nn.h \

OBJS=\
kdtree.o \
simple_vector.o \

all: run_tests kdtree.o

run_tests: runner
	./runner

runner: runner.cpp ${OBJS}
	g++ ${CXXFLAGS} -o $@ $^

runner.cpp: ${TESTS}
	cxxtestgen.py -o $@ --error-printer $^ 

clean:
	rm -f *.o runner runner.cpp
