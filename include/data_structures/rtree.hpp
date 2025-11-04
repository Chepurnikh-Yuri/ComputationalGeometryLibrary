#ifndef RTREE_HPP
#define RTREE_HPP

#include <cmath>

#include "concepts.hpp"

template<NumericType NT, size_t Dimension>
struct Rect 
{
    NT xmin, xmax, ymin, ymax;

    Rect() noexcept : xmin(0), xmax(0), ymin(0), ymax(0) { }

    Rect(NT xmin, NT ymax, NT xmax, NT ymin) noexcept :
        xmin(xmin), ymax(ymax), xmax(xmax), ymin(ymin) { }

    NT area() const noexcept { return (xmax - xmin) * (ymax - ymin); }

    bool isIntersectsWt(const Rect& other) const noexcept 
    {
        return !(
            xmax < other.xmin || 
            xmin > other.xmax ||
            ymax < other.ymin ||
            ymin > other.ymax
        );
    }

    bool isContain(const Rect& other) const noexcept 
    {
        return xmax >= other.xmax &&
            xmin <= other.xmin &&
            ymax >= other.ymax &&
            ymin <= other.ymin;
    }

    void enlargeToInclude(const Rect& other) noexcept 
    {
        xmin = std::min(xmin, other.xmin);
        xmax = std::max(xmax, other.xmax);
        ymin = std::min(ymin, other.ymin);
        ymax = std::max(ymax, other.ymax);
    }

    static Rect boundingFrame(const Rect& r1, const Rect& r2) noexcept 
    {
        return Rect(
            std::min(r1.xmin, r2.xmin),
            std::max(r1.ymax, r2.ymax),
            std::max(r1.xmax, r2.xmax), 
            std::min(r1.ymin, r2.ymin)
        );
    }

    double increaseSizeToFit(const Rect& other) const noexcept 
    {
        auto r = Rect::boundingFrame(*this, other);
        return r.area() - this->area();
    }

    double overlapArea(const Rect& other) const noexcept 
    {
        if (!this->isIntersectsWt(other))
            return 0;

        return (std::min(xmax, other.xmax) - std::max(xmin, other.xmin)) *
            (std::min(ymax, other.ymax) - std::max(ymin, other.ymin));
    }
};

#endif // RTREE_HPP