#include <catch.hpp>

#include "point.h"
#include "polygon.h"
#include "segment.h"

void TestPolygon(const std::vector<int64_t>& coordinates, int64_t a_x, int64_t a_y, int64_t b_x, int64_t b_y,
                 bool contains, bool crosses, const std::vector<int64_t>& moved_coordinates) {
    std::vector<geometry::Point> points;
    for (size_t index = 0; index * 2 + 1 < coordinates.size(); ++index) {
        points.emplace_back(coordinates[2 * index], coordinates[2 * index + 1]);
    }
    REQUIRE(points.size() * 2 == coordinates.size());
    geometry::Polygon polygon(points);
    geometry::Point a(a_x, a_y);
    geometry::Point b(b_x, b_y);
    auto s_ab = geometry::Segment(a, b);
    REQUIRE(contains == polygon.ContainsPoint(a));
    REQUIRE(crosses == polygon.CrossesSegment(s_ab));
    auto vector_ab = b - a;
    const auto cloned_shape_ptr = polygon.Clone();  // may return either raw or smart pointer
    auto moved_polygon = cloned_shape_ptr->Move(vector_ab);
    auto moved_points = moved_polygon.GetPoints();
    for (size_t index = 0; index < moved_points.size(); ++index) {
        REQUIRE(moved_points[index].GetX() == moved_coordinates[2 * index]);
        REQUIRE(moved_points[index].GetY() == moved_coordinates[2 * index + 1]);
    }

    delete cloned_shape_ptr;
}

// NOLINTBEGIN
TEST_CASE("Polygon") {
    TestPolygon({0, 0, 3, 0, 3, 3, 0, 3}, 1, 1, 2, 2, true, false, {1, 1, 4, 1, 4, 4, 1, 4});
    TestPolygon({1, 1, 10, 2, 2, 8}, 2, 3, 2, 1, true, true, {1, -1, 10, 0, 2, 6});
}
// NOLINTEND