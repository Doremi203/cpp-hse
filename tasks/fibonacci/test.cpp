#include <catch.hpp>

#include "fibonacci.h"

TEST_CASE("Simple") {
    REQUIRE(CalculateNthFibonacci(0) == 0);
    REQUIRE(CalculateNthFibonacci(1) == 1);
    REQUIRE(CalculateNthFibonacci(2) == 1);
    REQUIRE(CalculateNthFibonacci(3) == 2);
    REQUIRE(CalculateNthFibonacci(4) == 3);
    REQUIRE(CalculateNthFibonacci(5) == 5);
    REQUIRE(CalculateNthFibonacci(6) == 8);
}

TEST_CASE("Big values") {
    REQUIRE(CalculateNthFibonacci(80) == 23416728348467685);
}
