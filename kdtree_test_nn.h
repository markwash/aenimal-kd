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
	neighbor_t nb;

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
	void test_exact_center() 
	{
		kdtree_nn(kdt, 5.0, 5.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 5.0);
		TS_ASSERT_EQUALS(nb.y, 5.0);
		TS_ASSERT_EQUALS(nb.dist, 0.0);
		TS_ASSERT_EQUALS(nb.data, "center");
	}
	void test_near_center() {
		kdtree_nn(kdt, 6.0, 4.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 5.0);
		TS_ASSERT_EQUALS(nb.y, 5.0);
		TS_ASSERT_EQUALS(nb.dist, 2.0);
		TS_ASSERT_EQUALS(nb.data, "center");
	}
	void test_near_bottomleft()
	{
		kdtree_nn(kdt, 1.0, 1.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 0.0);
		TS_ASSERT_EQUALS(nb.y, 0.0);
		TS_ASSERT_EQUALS(nb.dist, 2.0);
		TS_ASSERT_EQUALS(nb.data, "bottomleft");
	}
	void test_near_left()
	{
		kdtree_nn(kdt, 1.0, 5.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 0.0);
		TS_ASSERT_EQUALS(nb.y, 5.0);
		TS_ASSERT_EQUALS(nb.dist, 1.0);
		TS_ASSERT_EQUALS(nb.data, "left");
	}
	void test_near_topleft()
	{
		kdtree_nn(kdt, 1.0, 9.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 0.0);
		TS_ASSERT_EQUALS(nb.y, 10.0);
		TS_ASSERT_EQUALS(nb.dist, 2.0);
		TS_ASSERT_EQUALS(nb.data, "topleft");
	}
	void test_near_top()
	{
		kdtree_nn(kdt, 5.0, 9.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 5.0);
		TS_ASSERT_EQUALS(nb.y, 10.0);
		TS_ASSERT_EQUALS(nb.dist, 1.0);
		TS_ASSERT_EQUALS(nb.data, "top");
	}
	void test_near_topright()
	{
		kdtree_nn(kdt, 7.6, 7.6, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 10.0);
		TS_ASSERT_EQUALS(nb.y, 10.0);
		TS_ASSERT_DELTA(nb.dist, 11.52, 0.001);
		TS_ASSERT_EQUALS(nb.data, "topright");
	}
	void test_near_right()
	{
		kdtree_nn(kdt, 15.0, 5.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 10.0);
		TS_ASSERT_EQUALS(nb.y, 5.0);
		TS_ASSERT_EQUALS(nb.dist, 25.0);
		TS_ASSERT_EQUALS(nb.data, "right");
	}
	void test_near_bottomright()
	{
		kdtree_nn(kdt, 7.6, 2.4, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 10.0);
		TS_ASSERT_EQUALS(nb.y, 0.0);
		TS_ASSERT_DELTA(nb.dist, 11.52, 0.001);
		TS_ASSERT_EQUALS(nb.data, "bottomright");
	}
	void test_near_bottom()
	{
		kdtree_nn(kdt, 5.0, 1.0, &nb, NULL);
		TS_ASSERT_EQUALS(nb.x, 5.0);
		TS_ASSERT_EQUALS(nb.y, 0.0);
		TS_ASSERT_EQUALS(nb.dist, 1.0);
		TS_ASSERT_EQUALS(nb.data, "bottom");
	}
	void tearDown()
	{
		kdtree_free(kdt);
	}
};

