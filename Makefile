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

all: run_tests ${OBJS} 

run_tests: cxx_test python_test

cxx_test: cxx_runner
	./cxx_runner

cxx_runner: cxx_runner.cpp ${OBJS}
	g++ ${CXXFLAGS} -o $@ $^

cxx_runner.cpp: ${CXX_TESTS}
	cxxtestgen.py -o $@ --error-printer $^ 

python_test: python_build kdtree_test.py
	cd build/lib.win32-2.5/; python ../../kdtree_test.py 

python_build: setup.py kdtree_module.c ${OBJS}
	python setup.py build -c mingw32

clean:
	rm -f *.o cxx_runner.exe cxx_runner.cpp
	rm -rf build
