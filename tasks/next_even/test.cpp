#include <catch.hpp>
#include "next_even.h"

TEST_CASE("Simple") {
    REQUIRE(4 == NextEven(3));
    REQUIRE(4 == NextEven(2));
}
