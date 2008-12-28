#include <cxxtest/TestSuite.h>

extern "C" {
#include "simple_vector.h"
}

#include <iostream>
using namespace std;

class VectorBasicTestSuite : public CxxTest::TestSuite 
{

	simple_vector_t *sv;

public:
	void setUp()
	{
		sv = simple_vector_new(sizeof(int), 1, 4);
	}
	void test_size()
	{
		TS_ASSERT_EQUALS(simple_vector_size(sv), 1);
	}
	void test_cap()
	{
		TS_ASSERT_EQUALS(simple_vector_cap(sv), 4);
	}
	void test_set_and_get()
	{
		int value = 38;
		simple_vector_set(sv, 0, &value);
		value = 0;
		simple_vector_get(sv, 0, &value);
		TS_ASSERT_EQUALS(value, 38);
	}
	void test_get_ref()
	{
		int value = 72;
		simple_vector_set(sv, 0, &value);
		int *pvalue;
		pvalue = (int *) simple_vector_get_ref(sv, 0);
		TS_ASSERT_EQUALS(*pvalue, 72);
	}
	void test_ref_persist()
	{
		int value = 27;
		simple_vector_set(sv, 0, &value);
		int *pvalue;
		pvalue = (int *) simple_vector_get_ref(sv, 0);
		size_t cap = simple_vector_cap(sv);
		for (cap *= 2 ; cap < 1000000; cap *= 2) {
			simple_vector_recap(sv, cap);
			TS_ASSERT_EQUALS(simple_vector_get_ref(sv, 0), pvalue);
		}
	}
	void test_recap()
	{
		simple_vector_recap(sv, 10);
		TS_ASSERT_EQUALS(simple_vector_cap(sv), 10);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 1);
	}
	void test_recap_lower()
	{
		size_t cap = simple_vector_cap(sv);
		simple_vector_recap(sv, 1);
		TS_ASSERT_EQUALS(simple_vector_cap(sv), cap);
	}
	void test_resize()
	{
		simple_vector_resize(sv, 10);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 10);
		TS_ASSERT_LESS_THAN_EQUALS(10, simple_vector_cap(sv));
	}
	void test_grow()
	{
		simple_vector_grow(sv, 3);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 4);
		TS_ASSERT_EQUALS(simple_vector_cap(sv), 4);
		simple_vector_grow(sv, 1);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 5);
		TS_ASSERT_LESS_THAN_EQUALS(5, simple_vector_cap(sv));
	}
	void test_shrink()
	{
		simple_vector_shrink(sv, 1);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 0);
		TS_ASSERT_EQUALS(simple_vector_cap(sv), 4);
	}
	void test_pushback()
	{
		int value = 32;
		simple_vector_pushback(sv, &value);
		TS_ASSERT_EQUALS(simple_vector_size(sv), 2);
		value = 0;
		simple_vector_get(sv, 1, &value);
		TS_ASSERT_EQUALS(value, 32);
	}
	void test_last()
	{
		int value = 99;
		simple_vector_pushback(sv, &value);
		value = 98;
		simple_vector_pushback(sv, &value);
		value = 0;
		simple_vector_last(sv, &value);
		TS_ASSERT_EQUALS(value, 98);
	}
	void test_last_ref()
	{
		int value = 99;
		simple_vector_pushback(sv, &value);
		int *pvalue;
		pvalue = (int *) simple_vector_last_ref(sv);
		TS_ASSERT_EQUALS(*pvalue, 99);
	}
	void tearDown()
	{
		simple_vector_free(sv);
	}
};

