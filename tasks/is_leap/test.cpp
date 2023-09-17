#include <catch.hpp>
#include "is_leap.h"

TEST_CASE("Simple") {
    REQUIRE(IsLeap(2008));
    REQUIRE(IsLeap(2004));
    REQUIRE(IsLeap(2024));

    REQUIRE(IsLeap(1008));
    REQUIRE(IsLeap(1932));

    REQUIRE(!IsLeap(2005));
    REQUIRE(!IsLeap(2006));
    REQUIRE(!IsLeap(2023));

    REQUIRE(IsLeap(2000));
    REQUIRE(!IsLeap(2100));
    REQUIRE(!IsLeap(2300));
}
