// kdtree-test.h
#include <cxxtest/TestSuite.h>

#include "kdtree.h"

#include <iostream>
using namespace std;

class KDTreeLongTestSuite : public CxxTest::TestSuite 
{
	static int num_points;
	static double points[][2];
	static char *data[];
	static int num_nonpoints;
	static double nonpoints[][2];

	kdtree_t *kdt;

public:
	void setUp()
	{
		kdt = kdtree_new(0);
		for (int i = 0; i < num_points; i++) {
			kdtree_add(kdt, points[i][0], points[i][1], data[i]);
			kdtree_internal_check(kdt);
		}
	}
	void test_get_points()
	{
		for (int i = 0; i < num_points; i++) {
			TS_ASSERT_EQUALS(kdtree_get(kdt, points[i][0], points[i][1]), data[i]);
		}
	}
	void test_has()
	{
		for (int i = 0; i < num_points; i++) {
			TS_ASSERT(kdtree_has(kdt, points[i][0], points[i][1]));
		}
		for (int i = 0; i < num_nonpoints; i++) {
			TS_ASSERT(!kdtree_has(kdt, nonpoints[i][0], nonpoints[i][1]));
		}
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(kdtree_size(kdt), num_points);
	}
	void test_delete()
	{
		for (int i = 0; i < num_points; i++) {
			kdtree_del(kdt, points[i][0], points[i][1]);
			kdtree_internal_check(kdt);
			TS_ASSERT(!kdtree_has(kdt, points[i][0], points[i][1]));
			for (int j = i + 1; j < num_points; j++) {
				TS_ASSERT(kdtree_has(kdt, points[j][0], points[j][1]));
			}
		}
	}
	void test_delete_backwards()
	{
		for (int i = num_points-1; i >= 0; i--) {
			kdtree_del(kdt, points[i][0], points[i][1]);
			kdtree_internal_check(kdt);
			TS_ASSERT(!kdtree_has(kdt, points[i][0], points[i][1]));
			for (int j = i - 1; j >= 0; j--) {
				TS_ASSERT(kdtree_has(kdt, points[j][0], points[j][1]));
			}
		}
	}
	void test_internal_check()
	{
		kdtree_internal_check(kdt);
	}

};

int KDTreeLongTestSuite::num_points = 11;
double KDTreeLongTestSuite::points[][2] = {
		{1, 5},
		{1, 2},
		{-1, 2},
		{4, 3},
		{1, 3},
		{5, 8},
		{6, 2},
		{0, 9},
		{9, 5},
		{7, 6},
		{8, 2},
	};
char *KDTreeLongTestSuite::data[] = {
		"one",
		"two",
		"red",
		"blue",
		"three",
		"four",
		"shut",
		"door",
		"five",
		"six",
		"up",
		"sticks",
	};
int KDTreeLongTestSuite::num_nonpoints = 4;
double KDTreeLongTestSuite::nonpoints[][2] = {
		{75, 82},
		{2, 8},
		{100, -2},
		{-1, -1},
	};

