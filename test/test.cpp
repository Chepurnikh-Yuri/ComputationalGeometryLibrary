#include <gtest/gtest.h>
#include "sum.hpp"

TEST(General, Sum)
{
    EXPECT_EQ(sum(1, 2), 3);
    EXPECT_NEAR(sum(1.1, 2.2), 3.3, 1e-9);
}