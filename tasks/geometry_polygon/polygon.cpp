#include "polygon.h"

#include "line.h"
#include "segment.h"

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
};
}  // namespace geometry

geometry::Ray::Ray() : start_(), end_() {
}

geometry::Ray::Ray(Point first, Point second) : start_(first), end_(second) {
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
geometry::Ray& geometry::Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

geometry::Ray* geometry::Ray::Clone() const {
    return new geometry::Ray(*this);
}

geometry::Polygon::Polygon() : points_(), num_points_() {
}

geometry::Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points.size()) {
}

geometry::Polygon& geometry::Polygon::Move(const Vector& vector) {
    for (auto& point : points_) {
        point.Move(vector);
    }
    return *this;
}

bool geometry::Polygon::ContainsPoint(const Point& point) const {
    int intersections{};
    auto ray = Ray(point, Point(point.GetX() + 1, point.GetY()));
    for (int i = 0; i < num_points_; ++i) {
        auto p2 = i == num_points_ - 1 ? points_[0] : points_[i + 1];
        auto segment = Segment(points_[i], p2);
        if (segment.ContainsPoint(point)) {
            return true;
        } else if (points_[i].GetY() == p2.GetY()) {
            continue;
        } else if (point.GetY() == std::max(points_[i].GetY(), p2.GetY())) {
            continue;
        } else if (ray.CrossesSegment(segment)) {
            ++intersections;
        }
    }
    return intersections % 2 != 0;
}

bool geometry::Polygon::CrossesSegment(const Segment& segment) const {
    for (int i = 0; i < num_points_ - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}
geometry::Polygon* geometry::Polygon::Clone() const {
    return new Polygon(*this);
}
