// kdtree-test.h
#include <cxxtest/TestSuite.h>

#include "kdtree.h"

#include <iostream>
using namespace std;

class KDTreeBasicTestSuite : public CxxTest::TestSuite 
{
	KDTree *kdt;

public:
	void setUp()
	{
	}
	void tearDown()
	{
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

class KDTreeLongTestSuite : public CxxTest::TestSuite 
{
	KDTree *kdt;
	static int num_points;
	static int points[][2];
	static char *data[];
	static int num_nonpoints;
	static int nonpoints[][2];

public:
	void setUp()
	{
	}
	void test_get_points()
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

int KDTreeLongTestSuite::num_points = 5;
int KDTreeLongTestSuite::points[][2] = {
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
int KDTreeLongTestSuite::nonpoints[][2] = {
		{75, 82},
		{2, 8},
		{100, -2},
		{-1, -1},
	};

