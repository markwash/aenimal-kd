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
		kdtree_add(kdt, 0.0, 0.0, "bottomleft");
		kdtree_add(kdt, 0.0, 5.0, "left");
		kdtree_add(kdt, 0.0, 10.0, "topleft");
		kdtree_add(kdt, 5.0, 10.0, "top");
		kdtree_add(kdt, 10.0, 10.0, "topright");
		kdtree_add(kdt, 10.0, 5.0, "right");
		kdtree_add(kdt, 10.0, 0.0, "bottomright");
		kdtree_add(kdt, 5.0, 0.0, "bottom");
	}
	void test_exact_center() {
	}
	void tearDown()
	{
		kdtree_free(kdt);
	}
};

