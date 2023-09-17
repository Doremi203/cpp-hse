#include <catch.hpp>

#include "reduce_fraction.h"

TEST_CASE("Simple") {
    REQUIRE(ReduceFraction(1, 2) == 3);
    REQUIRE(ReduceFraction(2, 4) == 3);
    REQUIRE(ReduceFraction(5, 15) == 4);
    REQUIRE(ReduceFraction(13, 23) == 36);
}

TEST_CASE("Big values") {
    int64_t lhs = 3672847903;
    int64_t rhs = 7072514279;
    REQUIRE(ReduceFraction(lhs, rhs) == lhs + rhs);
}
