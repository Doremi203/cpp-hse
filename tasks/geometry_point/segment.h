#pragma once
#include "i_shape.h"
#include "point.h"

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

    Segment& Move(const Vector& vector) override {
        return *this;
    };

    bool ContainsPoint(const Point& point) const override {
        return false;
    }

    bool CrossesSegment(const Segment& segment) const override {
        return false;
    };

    Segment* Clone() const override {
        return nullptr;
    };
};
}  // namespace geometry
