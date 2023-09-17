#include "segment.h"

#include "line.h"

geometry::Segment::Segment() : start_(), end_() {
}

geometry::Segment::Segment(Point first, Point second) : start_(first), end_(second) {
}

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}

double geometry::Segment::Distance(geometry::Point point) const {
    auto v1 = end_ - start_;
    auto v2 = point - end_;
    auto v3 = point - start_;
    if (ScalarMult(-v1, v2) * ScalarMult(v1, v3) < 0) {
        return std::min(Length(v2), Length(v3));
    }
    return Line(start_, end_).Distance(point);
}

bool geometry::Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}

geometry::Segment& geometry::Segment::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Segment::ContainsPoint(const Point& point) const {
    return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const Segment& segment) const {
    if (VectorMult(end_ - start_, segment.start_ - start_) * VectorMult(end_ - start_, segment.end_ - start_) > 0 ||
        VectorMult(segment.end_ - segment.start_, start_ - segment.start_) *
                VectorMult(segment.end_ - segment.start_, end_ - segment.start_) >
            0) {
        return false;
    }
    auto line = Line(start_, end_);
    if (line.ContainsPoint(segment.start_) && line.ContainsPoint(segment.end_)) {
        if (!(segment.start_.CrossesSegment(*this) || segment.end_.CrossesSegment(*this) ||
              start_.CrossesSegment(segment) || end_.CrossesSegment(segment))) {
            return false;
        }
    }
    return true;
}

geometry::Segment* geometry::Segment::Clone() const {
    return new geometry::Segment(*this);
}
