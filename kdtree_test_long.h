// kdtree-test.h
#include <cxxtest/TestSuite.h>

#include "kdtree.h"

#include <iostream>
using namespace std;

class KDTreeLongTestSuite : public CxxTest::TestSuite 
{
	static double num_points;
	static double points[][2];
	static char *data[];
	static double num_nonpoints;
	static double nonpoints[][2];

	kdtree_t *kdt;

public:
	void setUp()
	{
		kdt = kdtree_new(0);
		for (int i = 0; i < num_points; i++) {
			kdtree_add(kdt, points[i][0], points[i][1], data[i]);
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

double KDTreeLongTestSuite::num_points = 5;
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
double KDTreeLongTestSuite::num_nonpoints = 4;
double KDTreeLongTestSuite::nonpoints[][2] = {
		{75, 82},
		{2, 8},
		{100, -2},
		{-1, -1},
	};

