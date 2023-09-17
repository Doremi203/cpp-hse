#include <catch.hpp>

#include "chocolate.h"

TEST_CASE("Simple") {
    REQUIRE(CanBreakSlices(2, 1, 1));
    REQUIRE(CanBreakSlices(4, 12, 8));

    REQUIRE(!CanBreakSlices(2, 2, 4));
    REQUIRE(!CanBreakSlices(3, 3, 7));
}