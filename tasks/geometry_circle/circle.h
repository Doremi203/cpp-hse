#pragma once

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Circle : public IShape {
private:
    Point centre_;
    int64_t radius_;

public:
    Circle();

    Circle(Point, int64_t);

    Circle& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Circle* Clone() const override;

    int64_t GetRadius() const;

    Point GetCenter() const;
};
}  // namespace geometry
