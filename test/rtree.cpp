#include <gtest/gtest.h>

#include "rtree.hpp"

TEST(RTree, Rect) 
{
    Rect<int, 2> r1(2, 6, 6, 2);
    Rect<int, 2> r2(4, 5, 9, 3);

    EXPECT_TRUE(r1.area() == 16);
    EXPECT_TRUE(r2.area() == 10);

    EXPECT_TRUE(r1.isIntersectsWt(r2));

    EXPECT_FALSE(r1.isContain(r2));

    auto fr = Rect<int, 2>::boundingFrame(r1, r2);
    EXPECT_TRUE(fr.xmin == 2);
    EXPECT_TRUE(fr.xmax == 9);
    EXPECT_TRUE(fr.ymin == 2);
    EXPECT_TRUE(fr.ymax == 6);

    EXPECT_TRUE(r1.increaseSizeToFit(r2) == 12);

    EXPECT_TRUE(r1.overlapArea(r2) == 4);

    r1.enlargeToInclude(r2);
    EXPECT_TRUE(r1.xmin == 2);
    EXPECT_TRUE(r1.xmax == 9);
    EXPECT_TRUE(r1.ymin == 2);
    EXPECT_TRUE(r1.ymax == 6);
}