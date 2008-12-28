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
	kdnode_t *head, *tail;

public:
	void setUp()
	{
		kdnode_init(&n, 5.0, 5.0, "center");
		head = NULL;
		tail = NULL;
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
	void test_list_pushback()
	{
		kdnode_t n1, n2;
		kdnode_init(&n1, 0.0, 0.0, "first");
		kdnode_init(&n2, 1.0, 1.0, "second");
		kdnode_list_pushback(&head, &tail, &n1); 
		TS_ASSERT_EQUALS(head, &n1);
		TS_ASSERT_EQUALS(tail, &n1);
		kdnode_list_pushback(&head, &tail, &n2);
		TS_ASSERT_EQUALS(head, &n1);
		TS_ASSERT_EQUALS(tail, &n2);
	}
	void tearDown()
	{
	}
};

