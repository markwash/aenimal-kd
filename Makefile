CXXFLAGS=-g
CFLAGS=-g

CXX_TESTS=\
kdtree_test_basic.h \
kdtree_private_test_basic.h \
kdtree_test_long.h \
simple_vector_test_basic.h \
kdtree_test_nn.h \
kdtree_test_iterate.h \

PY_TESTS=\
kdtree_test.py \
kdtree_test_nn.py \
kdtree_test_render.py \

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

python_test: python_build test_suite.py ${PY_TESTS}
	PYTHONPATH="./build/lib.win32-2.5/;./" python test_suite.py 

python_build: setup.py kdtree_module.c ${OBJS}
	python setup.py build -c mingw32

clean:
	rm -f *.o cxx_runner.exe cxx_runner.cpp
	rm -f *.pyc
	rm -rf build
