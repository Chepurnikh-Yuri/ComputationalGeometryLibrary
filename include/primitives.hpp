#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <array>
#include <vector>

#include "concepts.hpp"

namespace Primitives 
{
    template<NumericType NT, size_t D>
    struct Point 
    {
        std::array<NT, D> coordinates;
    };

    // Specialization for a two-dimensional Point
    template<NumericType NT>
    struct Point<NT, 2>
    {
        NT x, y;
    };

    template<NumericType NT, size_t D>
    struct Segment 
    {
        Point<NT, D> p1, p2;
    };

    // Specialization for a two-dimensional Segment
    template<NumericType NT>
    struct Segment<NT, 2>
    {
        Point<NT, 2> p1, p2;
    };

    template<NumericType NT>
    using Line2D = Segment<NT, 2>; 

    template <
        NumericType NT,
        size_t D,
        template<typename, typename ...> 
            class ContType = std::vector
        >
    struct Polyline 
    {
        ContType<Segment<NT, D>> segments;
    };

    // Two-dimensional polyline is polygon
    template <
        NumericType NT,
        template<typename, typename ...>
            class ContType = std::vector
        >
    using Polygon = Polyline<Segment<NT, 2>, 2>;
}

#endif // PRIMITIVES_HPP