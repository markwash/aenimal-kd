// kdtree-test.h
#include <cxxtest/TestSuite.h>

extern "C" {
#include "kdtree.h"
}

#include <iostream>
using namespace std;

class KDTreeNNTestSuite : public CxxTest::TestSuite 
{

	kdtree_t *kdt;

public:
	void setUp()
	{
		kdt = kdtree_new(0);
		kdtree_add(kdt, 5.0, 5.0, "center");
	}
	void tearDown()
	{
		kdtree_free(kdt);
	}
};

