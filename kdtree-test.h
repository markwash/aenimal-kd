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
		kdt = new KDTree();
		kdt->add(1, 5, "hello");
	}
	void tearDown()
	{
		delete kdt;
	}
	void test_get_point()
	{
		TS_ASSERT_SAME_DATA(kdt->get(1, 5), "hello", 6);
	}
	void test_add_and_get_points()
	{
		kdt->display();
		kdt->add(2, 3, "World");
		kdt->display();
		TS_ASSERT_SAME_DATA(kdt->get(2, 3), "World", 6);
		TS_ASSERT_SAME_DATA(kdt->get(1, 5), "hello", 6);
	}
	void test_has()
	{
		TS_ASSERT(kdt->has(1, 5));
		TS_ASSERT(!kdt->has(5, 1));
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(kdt->size(), 1)
	}
	void test_delete()
	{
		kdt->del(1, 5);
		TS_ASSERT(!kdt->has(1, 5));
	}
	void test_delete_backwards()
	{
		kdt->add(2, 3, "World");
		kdt->del(2, 3);
		TS_ASSERT(!kdt->has(2, 3));
		TS_ASSERT(kdt->has(1, 5));
		kdt->del(1, 5);
		TS_ASSERT(!kdt->has(1, 5));
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
		kdt = new KDTree();
		for (int i = 0; i < num_points; i++) {
			kdt->add(points[i][0], points[i][1], data[i]);
		}
	}
	void test_get_points()
	{
		for (int i = 0; i < num_points; i++) {
			TS_ASSERT_EQUALS(kdt->get(points[i][0], points[i][1]), data[i]);
		}
	}
	void test_has()
	{
		for (int i = 0; i < num_points; i++) {
			TS_ASSERT(kdt->has(points[i][0], points[i][1]));
		}
		for (int i = 0; i < num_nonpoints; i++) {
			TS_ASSERT(!kdt->has(nonpoints[i][0], nonpoints[i][1]));
		}
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(kdt->size(), num_points);
	}
	void test_delete()
	{
		for (int i = 0; i < num_points; i++) {
			kdt->del(points[i][0], points[i][1]);
			TS_ASSERT(!kdt->has(points[i][0], points[i][1]));
			for (int j = i+1; j < num_points; j++) {
				TS_ASSERT(kdt->has(points[j][0], points[j][1]));
			}
		}
	}
	void test_delete_backwards()
	{
		cout << endl;
		kdt->display();
		for (int i = num_points-1; i >= 0; i--) {
			kdt->del(points[i][0], points[i][1]);
			kdt->display();
			TS_ASSERT(!kdt->has(points[i][0], points[i][1]));
			for (int j = 0; j < i; j++) {
				cout << i << ", " << j << endl;
				TS_ASSERT(kdt->has(points[j][0], points[j][1]));
			}
		}
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

