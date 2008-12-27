// kdtree-test.h
#include <cxxtest/TestSuite.h>

extern "C" {
#include "kdtree_private.h"
}

#include <iostream>
using namespace std;

class KDTreePrivateBasicTestSuite : public CxxTest::TestSuite 
{

	kdnode_t n;

public:
	void setUp()
	{
		kdnode_init(&n, 5.0, 5.0, "center");
	}
	void test_compare()
	{
		TS_ASSERT_LESS_THAN(kdnode_cmp(&n, 0.0, 0.0, 0), 0);
		TS_ASSERT_LESS_THAN(kdnode_cmp(&n, 0.0, 10.0, 0), 0);
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 10.0, 0.0, 0));
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 10.0, 10.0, 0));

		TS_ASSERT_LESS_THAN(kdnode_cmp(&n, 0.0, 0.0, 1), 0);
		TS_ASSERT_LESS_THAN(kdnode_cmp(&n, 10.0, 0.0, 1), 0);
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 0.0, 10.0, 1));
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 10.0, 10.0, 1));

		TS_ASSERT_EQUALS(kdnode_cmp(&n, 5.0, 5.0, 0), 0);
		TS_ASSERT_EQUALS(kdnode_cmp(&n, 5.0, 5.0, 1), 0);

		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 5.0, 0.0, 0));
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 5.0, 10.0, 0));
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 0.0, 5.0, 1));
		TS_ASSERT_LESS_THAN(0, kdnode_cmp(&n, 10.0, 5.0, 1));
	}
	void tearDown()
	{
	}
};

