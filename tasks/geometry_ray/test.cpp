#include <catch.hpp>

#include "point.h"
#include "ray.h"
#include "segment.h"

void TestRay(int64_t start_x, int64_t start_y, int64_t end_x, int64_t end_y, int64_t a_x, int64_t a_y, int64_t b_x,
             int64_t b_y, bool contains, bool crosses, int64_t moved_start_x, int64_t moved_start_y,
             int64_t moved_vector_x, int64_t moved_vector_y) {
    geometry::Point start(start_x, start_y);
    geometry::Point end(end_x, end_y);
    geometry::Ray r(start, end);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s_ab = geometry::Segment(a, b);
    REQUIRE(contains == r.ContainsPoint(a));
    REQUIRE(crosses == r.CrossesSegment(s_ab));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = r.Clone();  // may return either raw or smart pointer
    auto moved_r = cloned_shape_ptr->Move(vector_ab);
    REQUIRE(moved_r.GetStart().GetX() == moved_start_x);
    REQUIRE(moved_r.GetStart().GetY() == moved_start_y);
    auto moved_vector = moved_r.GetEnd() - moved_r.GetStart();
    REQUIRE(moved_vector.GetX() == moved_vector_x);
    REQUIRE(moved_vector.GetY() == moved_vector_y);
    delete cloned_shape_ptr;
}

TEST_CASE("Ray") {
    TestRay(0, 0, 1, 1, 2, 2, 3, 2, true, true, 1, 0, 1, 1);
    TestRay(3, 7, 5, 8, 1, 6, 3, 8, false, false, 5, 9, 2, 1);  // NOLINT
}