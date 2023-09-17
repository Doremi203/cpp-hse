#include "segment.h"

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
