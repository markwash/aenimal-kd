#include <cxxtest/TestSuite.h>

extern "C" {
#include "simple_vector.h"
}

#include <iostream>
using namespace std;

class VectorBasicTestSuite : public CxxTest::TestSuite 
{

	simple_vector_t *sv;

public:
	void setUp()
	{
		sv = simple_vector_new();
	}
	void test_blah()
	{
	}
	void tearDown()
	{
		simple_vector_free(sv);
	}
};

