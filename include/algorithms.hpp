#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <optional>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>

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

    // class-functor
    template <
        NumericType NT,
        template<typename, typename ...>
            class ContType = std::vector
        >
    struct SweepLine 
    {
        inline static NT currY = 0;

        struct IsectWtSegms 
        {
            Point<NT, 2> point;
            Segment<NT, 2> segment1, segment2;
        };

        struct Event 
        {
            NT y;
            bool above { false };
            Segment<NT, 2> segment;
        };

        // class-functor
        struct StatusCmp 
        {
            NT xAtY(const Segment<NT, 2>& s, NT y) const 
            {
                // if they are parallel, return the smallest
                if (s.p1.y == s.p2.y)
                {
                    return s.p1.y < s.p2.y;
                }
    
                return s.p1.x + ((y - s.p1.y) * (s.p2.x - s.p1.x) / (s.p2.y - s.p1.y));
            }

            bool operator()(const Segment<NT, 2>& s1, const Segment<NT, 2>& s2) const 
            {
                auto x1 = xAtY(s1, SweepLine<NT>::currY);
                auto x2 = xAtY(s2, SweepLine<NT>::currY);

                if (x1 != x2)
                {
                    return x1 < x2;
                }

                // tie-breacker
                // since the segment addresses 
                // will obviously be different
                return &x1 < &x2;
            }
        };

        ContType<IsectWtSegms> operator()(const ContType<Segment<NT, 2>>& segments)
        {
            if (segments.size() <= 1) 
            {
                return { };
            }

            auto queueCmp = [](const Event& e1, const Event& e2) 
            {
                return e1.y < e2.y;
            };
            
            // events are the projection of segment endpoints onto
            // the y-axis (in our case, but also possible on the x-axis)
            std::vector<Event> events;
            events.reserve(segments.size() * 2);

            for (const auto& s : segments)
            {
                auto [below, above] = std::minmax(s.p1.y, s.p2.y);

                events.emplace_back(Event { below, false, s });
                events.emplace_back(Event { above, true, s });
            }

            // status is the current segments intersecting 
            // with the sweep line
            std::set<Segment<NT, 2>, StatusCmp> status;

            ContType<IsectWtSegms> result;

            auto neighborsIsect = [&](auto it) 
            {
                if (it != status.begin())
                {
                    auto prev = std::prev(it);
                    auto optIsect = intersection(*prev, *it);
                    
                    if (optIsect.has_value())
                    {
                        result.push_back(IsectWtSegms { optIsect.value(), *prev, *it });
                    }
                }

                auto next = std::next(it);

                if (next != status.end())
                {
                    auto optIsect = intersection(*next, *it);
                    
                    if (optIsect.has_value())
                    {
                        result.push_back(IsectWtSegms { optIsect.value(), *next, *it });
                    }
                }
            };

            // in my case, the sweep line descends from top to bottom
            for (const auto& event : events)
            {        
                if (event.above)
                {
                    auto [it, inserted] = status.insert(event.segment);

                    if (inserted)
                    {
                        neighborsIsect(it);
                    }
                }

                else 
                {
                    auto it = status.find(event.segment);

                    if (it != status.end())
                    {
                        neighborsIsect(it);
                        status.erase(it);
                    }
                }

                SweepLine::currY = event.y;
            }

            return result;
        }
    };
}

#endif // ALGORITHMS_HPP