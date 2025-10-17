#include <iostream>
#include <vector>
#include "algorithms.hpp"

using namespace Algorithms;

int main()
{
    std::vector<Segment<double, 2>> segments {
        { { 1, 1 }, { 4, 4 } },
        { { 1, 3 }, { 4, 2 } },
        { { 2.5, 2 }, { 2.5, 3 } },
        { { 1, 5 }, { 3, 7 } },
        { { 1, 6 }, { 3, 6 } },
    };

    Point<double, 2> isect1 { 2.5, 2.5 }; 
    Point<double, 2> isect2 { 2, 6 };

    SweepLine<double> sl;
    auto result = sl(segments);

    for (const auto& iseg : result)
    {
        std::cout << "Intersection: " << iseg.point << ", " <<
                     "Segment #1: " << iseg.segment1.p1 << " " << iseg.segment1.p2 << ", " <<
                     "Segment #2: " << iseg.segment2.p1 << " " << iseg.segment2.p2 << std::endl;
    }

    std::vector<Segment<double, 2>> dummy;
    auto emptyResult = sl(dummy);

    std::cout << "emptyResult is empty: " << (emptyResult.empty() ? "true" : "false");
}