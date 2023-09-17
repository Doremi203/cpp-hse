#pragma once

#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    Segment();

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    double Distance(Point) const;

    bool Degenerate() const;

    Segment& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Segment* Clone() const override;
};
}  // namespace geometry
