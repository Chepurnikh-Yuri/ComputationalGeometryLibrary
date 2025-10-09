#include <vector>
#include <gtest/gtest.h>
#include "algorithms.hpp"

using namespace Algorithms;

namespace VectorTests 
{
    Point<double, 2> p1 { 2, 2 },
        p2 { 5, 5 }, 
        p3 { 3, 4 },
        p4 { 7, 4 },
        dst { 4, 4 }; 

    Segment<double, 2> s1 = { p1, p2 };
    Segment<double, 2> s2 = { p3, p4 };

    Vector<double> v1 = p2 - p1;
    Vector<double> v2 = p4 - p3;

    TEST(Vector, Cross)
    {
        EXPECT_EQ(cross(v1, v2), -12);
    }

    TEST(Vector, Intersection)
    {
        auto ip = intersection(s1, s2);
        ASSERT_TRUE(ip.has_value());
        
        EXPECT_EQ(ip.value(), dst);
    }
}
