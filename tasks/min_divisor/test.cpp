#include <catch.hpp>
#include <chrono>

#include "min_divisor.h"

TEST_CASE("Simple") {
    REQUIRE(MinDivisor(3) == 3);
    REQUIRE(MinDivisor(2) == 2);
    REQUIRE(MinDivisor(6) == 2);
    REQUIRE(MinDivisor(12) == 2);
    REQUIRE(MinDivisor(9) == 3);
}

TEST_CASE("Big prime") {
    const int64_t prime = 753454267;
    auto start = std::chrono::system_clock::now();
    REQUIRE(MinDivisor(prime) == prime);
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    REQUIRE(duration < 100);
}
