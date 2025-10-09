#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <optional>

#include "primitives.hpp"
#include "concepts.hpp"
using namespace Primitives;

namespace Algorithms 
{
    // Get pseudoscalar 
    template<NumericType NT>
    NT cross(const Vector<NT>& vec1, const Vector<NT>& vec2)
    {
        return vec1.x * vec2.y - vec1.y * vec2.x;
    }

    template<NumericType NT>
    std::optional<Point<NT, 2>> intersection(const Segment<NT, 2>& seg1, const Segment<NT, 2>& seg2)
    {
        Vector<NT> vec1 = seg1.p2 - seg1.p1;
        Vector<NT> vec2 = seg2.p2 - seg2.p1;
        Vector<NT> vec3 = seg2.p1 - seg1.p1;
    
        auto det = vec1.y * vec2.x - vec1.x * vec2.y;
        
        if (!det)
        {
            return std::nullopt;
        }

        auto det1 = vec2.x * vec3.y - vec3.x * vec2.y;
        auto det2 = vec1.x * vec3.y - vec1.y * vec3.x;

        auto alpha = det1 / det;
        auto beta = det2 / det;

        if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1)
        {
            return std::nullopt;
        }

        return seg1.p1 + vec1 * alpha;
    }
}

#endif // ALGORITHMS_HPP