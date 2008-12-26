CXXFLAGS="-g"
CFLAGS="-g"

all: run_tests kdtree.o

run_tests: runner
	./runner

runner: runner.cpp kdtree.o
	g++ ${CXXFLAGS} -o $@ $^

runner.cpp: kdtree_test_basic.h kdtree_test_long.h
	cxxtestgen.py -o $@ --error-printer $^ 

clean:
	rm -f *.o runner runner.cpp
