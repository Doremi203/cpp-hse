#include <catch.hpp>
#include "hypotenuse.h"

TEST_CASE("Simple") {
    REQUIRE(5.0 == CalculateHypotenuse(3, 4));

    REQUIRE(13.0 == CalculateHypotenuse(5, 12));

    REQUIRE(1.4142135623730951 == CalculateHypotenuse(1, 1));
}
