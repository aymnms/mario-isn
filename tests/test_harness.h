#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <math.h>
#include <stdio.h>

static int g_test_count = 0;
static int g_test_failures = 0;

#define ASSERT_TRUE(cond)                                                    \
    do {                                                                     \
        g_test_count++;                                                     \
        if (!(cond)) {                                                       \
            g_test_failures++;                                              \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        }                                                                     \
    } while (0)

#define ASSERT_EQ_INT(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_NEAR(a, b, eps) ASSERT_TRUE(fabs((a) - (b)) < (eps))

#endif
