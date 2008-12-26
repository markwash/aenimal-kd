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
		kdt->add(1.0, 5.0, "hello");
	}
	void tearDown()
	{
		delete kdt;
	}
	void test_get_point()
	{
		TS_ASSERT_SAME_DATA(kdt->get(1.0, 5.0), "hello", 6);
	}
	void test_add_and_get_points()
	{
		kdt->add(2.0, 3.0, "World");
		TS_ASSERT_SAME_DATA(kdt->get(2.0, 3.0), "World", 6);
		TS_ASSERT_SAME_DATA(kdt->get(1.0, 5.0), "hello", 6);
	}
	void test_has()
	{
		TS_ASSERT(kdt->has(1.0, 5.0));
		TS_ASSERT(!kdt->has(5.0, 1.0));
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(kdt->size(), 1)
	}
	void test_delete()
	{
		kdt->del(1.0, 5.0);
		TS_ASSERT(!kdt->has(1.0, 5.0));
	}
	void test_delete_backwards()
	{
		kdt->add(2.0, 3.0, "World");
		kdt->del(2.0, 3.0);
		TS_ASSERT(!kdt->has(2.0, 3.0));
		TS_ASSERT(kdt->has(1.0, 5.0));
		kdt->del(1.0, 5.0);
		TS_ASSERT(!kdt->has(1.0, 5.0));
	}
};

class KDTreeLongTestSuite : public CxxTest::TestSuite 
{
	KDTree *kdt;
	static int num_points;
	static double points[][2];
	static char *data[];
	static int num_nonpoints;
	static double nonpoints[][2];

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
double KDTreeLongTestSuite::points[][2] = {
		{0.1, 0.5},
		{1.0, 2.0},
		{-1.0, 2.0},
		{4.0, 3.3},
		{1.1, 3.0},
		{5.3, 8.2},
		{6.7, 2.0},
		{0.5, 9.0},
		{9.0, 5.0},
		{7.0, 6.0},
		{8.1, 2.2},
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
		{0.75, 0.82},
		{2.3, 8.2},
		{100.0, -2},
		{-1.0, -1.0},
	};

