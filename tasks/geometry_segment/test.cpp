#include <catch.hpp>

#include "point.h"
#include "segment.h"

void TestSegment(int64_t start_x, int64_t start_y, int64_t end_x, int64_t end_y, int64_t a_x, int64_t a_y, int64_t b_x,
                 int64_t b_y, bool contains, bool crosses, int64_t moved_start_x, int64_t moved_start_y,
                 int64_t moved_end_x, int64_t moved_end_y) {
    geometry::Point start(start_x, start_y);
    geometry::Point end(end_x, end_y);
    geometry::Segment s(start, end);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s_ab = geometry::Segment(a, b);
    REQUIRE(contains == s.ContainsPoint(a));
    REQUIRE(crosses == s.CrossesSegment(s_ab));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = s.Clone();  // may return either raw or smart pointer
    auto moved_s = cloned_shape_ptr->Move(vector_ab);
    REQUIRE(moved_s.GetStart().GetX() == moved_start_x);
    REQUIRE(moved_s.GetStart().GetY() == moved_start_y);
    REQUIRE(moved_s.GetEnd().GetX() == moved_end_x);
    REQUIRE(moved_s.GetEnd().GetY() == moved_end_y);
    delete cloned_shape_ptr;
}

TEST_CASE("Segment") {
    TestSegment(0, -1, 0, 1, 0, 0, 0, 1, true, true, 0, 0, 0, 2);
    TestSegment(4, 2, 4, 5, 4, 2, 4, 5, true, true, 4, 5, 4, 8);  // NOLINT
}