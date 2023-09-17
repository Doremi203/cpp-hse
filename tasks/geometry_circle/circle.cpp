#include "circle.h"

#include "line.h"
#include "segment.h"

geometry::Circle::Circle() : centre_(), radius_() {
}

geometry::Circle::Circle(Point point, int64_t radius) : centre_(point), radius_(radius) {
}

geometry::Circle& geometry::Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}

bool geometry::Circle::ContainsPoint(const Point& point) const {
    return (centre_.GetX() - point.GetX()) * (centre_.GetX() - point.GetX()) +
               (centre_.GetY() - point.GetY()) * (centre_.GetY() - point.GetY()) <=
           radius_ * radius_;
}

bool geometry::Circle::CrossesSegment(const Segment& segment) const {
    if (radius_ == 0) {
        return centre_.CrossesSegment(segment);
    }
    if (segment.Degenerate()) {
        return ContainsPoint(segment.GetStart());
    }
    auto r = static_cast<double>(radius_);
    return segment.Distance(centre_) == r ||
           (segment.Distance(centre_) < r &&
            !(Length(segment.GetStart() - centre_) < r && Length(segment.GetEnd() - centre_) < r));
}
geometry::Circle* geometry::Circle::Clone() const {
    return new geometry::Circle(*this);
}
int64_t geometry::Circle::GetRadius() const {
    return radius_;
}
geometry::Point geometry::Circle::GetCenter() const {
    return centre_;
}
