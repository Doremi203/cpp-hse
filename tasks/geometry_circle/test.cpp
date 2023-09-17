#include <catch.hpp>

#include "circle.h"
#include "point.h"
#include "segment.h"

void TestCircle(int64_t center_x, int64_t center_y, int64_t radius, int64_t a_x, int64_t a_y, int64_t b_x,
                       int64_t b_y, bool contains, bool crosses, int64_t moved_center_x, int64_t moved_center_y) {
    geometry::Point center(center_x, center_y);
    geometry::Circle c(center, radius);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s_ab = geometry::Segment(a, b);
    REQUIRE(contains == c.ContainsPoint(a));
    REQUIRE(crosses == c.CrossesSegment(s_ab));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = c.Clone();  // may return either raw or smart pointer
    auto moved_c = cloned_shape_ptr->Move(vector_ab);
    REQUIRE(moved_c.GetCenter().GetX() == moved_center_x);
    REQUIRE(moved_c.GetCenter().GetY() == moved_center_y);
    REQUIRE(moved_c.GetRadius() == radius);
    delete cloned_shape_ptr;
}

// NOLINTBEGIN
TEST_CASE("Circle") {
    TestCircle(0, 0, 5, 0, 0, 5, 5, true, true, 5, 5);
    TestCircle(0, 0, 5, 9, 8, -5, 3, false, true, -14, -5);
}
// NOLINTEND