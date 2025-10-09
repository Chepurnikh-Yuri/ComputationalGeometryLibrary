#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <array>
#include <vector>
#include <cmath>

#include "concepts.hpp"

#define EPSILON 1e-9

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

        bool operator==(const Point& other) const 
        {
            if constexpr (std::integral<NT>)
            {
                return x == other.x && y == other.y;
            }
            else if constexpr (std::floating_point<NT>)
            {
                return std::fabs(x - other.x) <= EPSILON &&
                       std::fabs(y - other.y) <= EPSILON;
            }
        }

        Point operator+(const Point& other) const 
        {
            return { x + other.x, y + other.y };
        }

        Point operator-(const Point& other) const 
        {
            return { x - other.x, y - other.y };
        }

        Point operator*(NT num) const 
        {
            return { x * num, y * num };
        }
    };

    template<NumericType NT>
    using Vector = Point<NT, 2>;

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