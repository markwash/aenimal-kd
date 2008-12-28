// kdtree-test.h
#include <cxxtest/TestSuite.h>

extern "C" {
#include "kdtree.h"
}

#include <iostream>
using namespace std;

class KDTreeBasicTestSuite : public CxxTest::TestSuite 
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
	void test_get_point()
	{
		TS_ASSERT_EQUALS(kdtree_get(kdt, 5.0, 5.0), "center"); 
	}
	void test_has()
	{
		TS_ASSERT(kdtree_has(kdt, 5.0, 5.0));
		TS_ASSERT(!kdtree_has(kdt, 0.0, 10.0));
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(kdtree_size(kdt), 1);
	}
	void test_delete()
	{
		kdtree_del(kdt, 5.0, 5.0);
		TS_ASSERT(!kdtree_has(kdt, 5.0, 5.0));
		TS_ASSERT_EQUALS(kdtree_size(kdt), 0);
	}
	void test_delete_backwards()
	{
		kdtree_add(kdt, 10, 10, "topright");
		kdtree_del(kdt, 5.0, 5.0);
		TS_ASSERT(kdtree_has(kdt, 10, 10));
		TS_ASSERT(!kdtree_has(kdt, 5.0, 5.0));
		TS_ASSERT_EQUALS(kdtree_size(kdt), 1);
		kdtree_del(kdt, 10, 10);
		TS_ASSERT(!kdtree_has(kdt, 10, 10));
		TS_ASSERT(!kdtree_has(kdt, 5.0, 5.0));
		TS_ASSERT_EQUALS(kdtree_size(kdt), 0);
	}
};

