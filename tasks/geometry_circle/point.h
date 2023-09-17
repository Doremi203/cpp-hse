#pragma once

#include "i_shape.h"

namespace geometry {
class Point : public IShape {
public:
    int64_t GetX() const;

    int64_t GetY() const;

    void SetX(int64_t);

    void SetY(int64_t);

    Point& Move(const Vector&) override;

    bool ContainsPoint(const Point&) const override;

    bool CrossesSegment(const Segment&) const override;

    Point* Clone() const override;

    Point() = default;

    Point(int64_t, int64_t);

    Vector operator-(Point other) const;

private:
    int64_t x_coord_;
    int64_t y_coord_;
};
}  // namespace geometry
