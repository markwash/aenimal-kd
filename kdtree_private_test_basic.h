// kdtree-test.h
#include <cxxtest/TestSuite.h>

extern "C" {
#include "kdtree_private.h"
}

#include <iostream>
using namespace std;

class KDTreePrivateBasicTestSuite : public CxxTest::TestSuite 
{

	kdnode_t n, n1, n2;
	kdnode_t *head, *tail, *stk;

public:
	void setUp()
	{
		kdnode_init(&n, 5.0, 5.0, "center");
		head = (kdnode_t *) NULL;
		tail = (kdnode_t *) NULL;
		stk = (kdnode_t *) NULL;
		kdnode_init(&n1, 0.0, 0.0, "first");
		kdnode_init(&n2, 1.0, 1.0, "second");
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
		kdnode_list_pushback(&head, &tail, &n1); 
		TS_ASSERT_EQUALS(head, &n1);
		TS_ASSERT_EQUALS(tail, &n1);
		kdnode_list_pushback(&head, &tail, &n2);
		TS_ASSERT_EQUALS(head, &n1);
		TS_ASSERT_EQUALS(tail, &n2);
	
		TS_ASSERT_EQUALS(n1.next, &n2);
		TS_ASSERT_EQUALS(n2.prev, &n1);
	}
	void test_list_del()
	{
		kdnode_list_pushback(&head, &tail, &n1);
		kdnode_list_pushback(&head, &tail, &n2);
		kdnode_list_del(&head, &tail, &n1);
		TS_ASSERT_EQUALS(head, &n2);
		TS_ASSERT_DIFFERS(head, &n1);
		TS_ASSERT_EQUALS(tail, &n2);
		kdnode_list_del(&head, &tail, &n2);
		TS_ASSERT_EQUALS(head, (kdnode_t *) NULL);
		TS_ASSERT_EQUALS(tail, (kdnode_t *) NULL);
	}
	void test_stack_push()
	{
		kdnode_stack_push(&stk, &n1);
		TS_ASSERT_EQUALS(stk, &n1);
		kdnode_stack_push(&stk, &n2);
		TS_ASSERT_EQUALS(stk, &n2);
		TS_ASSERT_EQUALS(n2.stk, &n1);
	}
	void test_stack_pop()
	{
		kdnode_stack_push(&stk, &n1);
		kdnode_stack_push(&stk, &n2);
		kdnode_t *n;
		n = kdnode_stack_pop(&stk);
		TS_ASSERT_EQUALS(n, &n2);
		TS_ASSERT_EQUALS(stk, &n1);
		TS_ASSERT_EQUALS(n2.stk, (kdnode_t *) NULL);
		n = kdnode_stack_pop(&stk);
		TS_ASSERT_EQUALS(n, &n1);
		TS_ASSERT_EQUALS(stk, (kdnode_t *) NULL);
		TS_ASSERT_EQUALS(n1.stk, (kdnode_t *) NULL);
	}
	void tearDown()
	{
	}
};

