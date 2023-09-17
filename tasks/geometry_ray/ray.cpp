#include "ray.h"

#include "line.h"
#include "segment.h"
#include "vector.h"

geometry::Ray::Ray() : start_(), end_() {
}

geometry::Ray::Ray(Point first, Point second) : start_(first), end_(second) {
}

geometry::Ray& geometry::Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Ray::ContainsPoint(const Point& point) const {
    return Line(start_, end_).ContainsPoint(point) && ScalarMult(point - start_, end_ - start_) >= 0;
}

bool geometry::Ray::CrossesSegment(const Segment& segment) const {
    auto d = end_ - start_;
    auto v1 = start_ - segment.GetStart();
    auto v2 = segment.GetEnd() - segment.GetStart();
    auto v3 = Vector(-d.GetY(), d.GetX());
    auto dom = static_cast<double>(ScalarMult(v2, v3));
    if (dom == 0) {
        return ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd());
    }
    auto t1 = static_cast<double>(VectorMult(v2, v1)) / dom;
    auto t2 = static_cast<double>(ScalarMult(v1, v3)) / dom;
    if (t1 >= 0 && 0 <= t2 && t2 <= 1) {
        return true;
    }
    return false;
}

geometry::Ray* geometry::Ray::Clone() const {
    return new geometry::Ray(*this);
}

geometry::Point geometry::Ray::GetStart() const {
    return start_;
}

geometry::Point geometry::Ray::GetEnd() const {
    return end_;
}
