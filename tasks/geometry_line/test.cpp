#include <catch.hpp>

#include "line.h"
#include "point.h"
#include "segment.h"

int64_t Det(int64_t ax, int64_t ay, int64_t bx, int64_t by) {
    return ax * by - ay * bx;
}

void TestLine(int64_t start_x, int64_t start_y, int64_t end_x, int64_t end_y, int64_t a_x, int64_t a_y, int64_t b_x, int64_t b_y, bool contains, bool crosses, int64_t a_line, int64_t b_line, int64_t c_line) {
    geometry::Point start(start_x, start_y);
    geometry::Point end(end_x, end_y);
    geometry::Line l(start, end);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s = geometry::Segment(a, b);
    REQUIRE(contains == l.ContainsPoint(a));
    REQUIRE(crosses == l.CrossesSegment(s));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = l.Clone();
    auto moved_l = cloned_shape_ptr->Move(vector_ab);
    auto ab_det = Det(moved_l.GetA(), moved_l.GetB(), a_line, b_line);
    auto ac_det = Det(moved_l.GetA(), moved_l.GetC(), a_line, c_line);
    REQUIRE(ab_det * ab_det + ac_det * ac_det == 0);
    delete cloned_shape_ptr;
}

TEST_CASE("Line") {
    TestLine(0, 0, 0, 1, 1, 1,2, 1, false, false, 1, 0, -1);
    TestLine(3, 7, 5, 8, 1, 6, 3, 8, true, true, 1, -2, 13); // NOLINT
}