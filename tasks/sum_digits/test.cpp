#include <catch.hpp>

#include "sum_digits.h"

TEST_CASE("Simple") {
    REQUIRE(SumOfDigits(1) == 1);
    REQUIRE(SumOfDigits(12) == 3);
    REQUIRE(SumOfDigits(1111111111) == 10);
}
