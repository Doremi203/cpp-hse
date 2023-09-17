#include "line.h"

#include "segment.h"

geometry::Line::Line() : start_(0, 0), end_(0, 0) {
}

int64_t geometry::Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t geometry::Line::GetB() const {
    return -(end_.GetX() - start_.GetX());
}

int64_t geometry::Line::GetC() const {
    return GetA() * -start_.GetX() + GetB() * -start_.GetY();
}

geometry::Line::Line(Point start, Point end) : start_(start), end_(end) {
}
double geometry::Line::Distance(Point point) const {
    if (ContainsPoint(point)) {
        return 0;
    }
    return std::abs(static_cast<double>(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
           std::sqrt(static_cast<double>(GetA() * GetA() + GetB() * GetB()));
}
geometry::Line& geometry::Line::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool geometry::Line::ContainsPoint(const Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}
bool geometry::Line::CrossesSegment(const Segment& segment) const {
    if (VectorMult(end_ - start_, segment.GetStart() - start_) * VectorMult(end_ - start_, segment.GetEnd() - start_) >
        0) {
        return false;
    }
    return true;
}
geometry::Line* geometry::Line::Clone() const {
    return new geometry::Line(*this);
}