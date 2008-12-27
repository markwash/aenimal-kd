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
	}
	void tearDown()
	{
		kdtree_free(kdt);
	}
	void test_get_point()
	{
	}
	void test_add_and_get_points()
	{
	}
	void test_has()
	{
	}
	void test_size()
	{
	}
	void test_delete()
	{
	}
	void test_delete_backwards()
	{
	}
};

