// kdtree-test.h
#include <cxxtest/TestSuite.h>

extern "C" {
#include "kdtree.h"
}

#include <iostream>
using namespace std;

class KDTreeIterateTestSuite : public CxxTest::TestSuite 
{

	kdtree_t *kdt;
	kdtree_iter_ctx_t *ctx;
	double x, y;
	const void *data;

public:
	void setUp()
	{
		kdt = kdtree_new(0);
		kdtree_add(kdt, 5.0, 5.0, "center");
		kdtree_add(kdt, 0.0, 5.0, "left");
		kdtree_add(kdt, 0.0, 10.0, "topleft");
		kdtree_add(kdt, 5.0, 10.0, "top");
		kdtree_add(kdt, 10.0, 10.0, "topright");
		kdtree_add(kdt, 10.0, 5.0, "right");
		kdtree_add(kdt, 10.0, 0.0, "bottomright");
		kdtree_add(kdt, 5.0, 0.0, "bottom");
		kdtree_add(kdt, 0.0, 0.0, "bottomleft");
		ctx = kdtree_iter_ctx_new(kdt);
	}
	void tearDown()
	{
		kdtree_iter_ctx_free(ctx);
		kdtree_free(kdt);
	}
	void test_iterate()
	{
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 5.0);
		TS_ASSERT_EQUALS(y, 5.0);
		TS_ASSERT_EQUALS(data, "center");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 0.0);
		TS_ASSERT_EQUALS(y, 5.0);
		TS_ASSERT_EQUALS(data, "left");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 0.0);
		TS_ASSERT_EQUALS(y, 10.0);
		TS_ASSERT_EQUALS(data, "topleft");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 5.0);
		TS_ASSERT_EQUALS(y, 10.0);
		TS_ASSERT_EQUALS(data, "top");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 10.0);
		TS_ASSERT_EQUALS(y, 10.0);
		TS_ASSERT_EQUALS(data, "topright");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 10.0);
		TS_ASSERT_EQUALS(y, 5.0);
		TS_ASSERT_EQUALS(data, "right");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 10.0);
		TS_ASSERT_EQUALS(y, 0.0);
		TS_ASSERT_EQUALS(data, "bottomright");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 5.0);
		TS_ASSERT_EQUALS(y, 0.0);
		TS_ASSERT_EQUALS(data, "bottom");
		TS_ASSERT_DIFFERS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(x, 0.0);
		TS_ASSERT_EQUALS(y, 0.0);
		TS_ASSERT_EQUALS(data, "bottomleft");
		TS_ASSERT_EQUALS(ctx, (kdtree_iter_ctx_t *) NULL);

		kdtree_iter_ctx_next(&ctx, &x, &y, &data);
		TS_ASSERT_EQUALS(ctx, (kdtree_iter_ctx_t *) NULL);
	}
};

