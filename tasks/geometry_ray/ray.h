#pragma once

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Ray : public IShape {
private:
    Point start_;
    Point end_;

public:
    Ray();

    Ray(Point first, Point second);

    Ray& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Ray* Clone() const override;

    Point GetStart() const;

    Point GetEnd() const;
};
}  // namespace geometry
