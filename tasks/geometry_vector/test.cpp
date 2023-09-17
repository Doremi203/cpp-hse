#include <catch.hpp>

#include "vector.h"

TEST_CASE("Vector") {
    const geometry::Vector a{1, 2};
    REQUIRE(a.GetX() == 1);
    REQUIRE(a.GetY() == 2);

    const geometry::Vector b{-2, 4};

    auto sum = a + b;
    REQUIRE(sum.GetX() == -1);
    REQUIRE(sum.GetY() == 6);

    auto diff = a - b;
    REQUIRE(diff.GetX() == 3);
    REQUIRE(diff.GetY() == -2);

    auto product = a * 2;
    REQUIRE(product.GetX() == 2);
    REQUIRE(product.GetY() == 4);

    auto ratio = product / 2;
    REQUIRE(a == ratio);

    auto scalar_mult = ScalarMult(a, b);

    REQUIRE(scalar_mult == 6);  // NOLINT

    auto vector_mult = VectorMult(a, b);

    REQUIRE(vector_mult == 8); // NOLINT

    auto length = Length(geometry::Vector(3, 4));

    REQUIRE(length == 5);
}