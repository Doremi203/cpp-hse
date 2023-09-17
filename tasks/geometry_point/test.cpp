#include <catch.hpp>

#include "point.h"
#include "segment.h"

void TestPoint(int64_t p_x, int64_t p_y, int64_t a_x, int64_t a_y, int64_t b_x, int64_t b_y, bool contains,
               bool crosses, int64_t moved_x, int64_t moved_y) {
    geometry::Point p(p_x, p_y);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s = geometry::Segment(a, b);
    REQUIRE(contains == p.ContainsPoint(a));
    REQUIRE(crosses == p.CrossesSegment(s));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = p.Clone();  // may return either raw or smart pointer
    auto moved_p = cloned_shape_ptr->Move(vector_ab);
    REQUIRE(moved_p.GetX() == moved_x);
    REQUIRE(moved_p.GetY() == moved_y);
    delete cloned_shape_ptr;
}

TEST_CASE("Point") {
    TestPoint(0, 0, -1, -1, 1, 1, false, true, 2, 2);
    TestPoint(1, 6, 3, 7, 5, 8, false, false, 3, 7);  // NOLINT
}
