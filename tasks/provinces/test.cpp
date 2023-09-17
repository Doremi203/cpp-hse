#include <catch.hpp>
#include <numeric>

#include "provinces.h"

// NOLINTBEGIN
TEST_CASE("Simple") {
    REQUIRE(3 == CountPassports({1, 2}));

    REQUIRE(10 == CountPassports({1, 2, 4}));
}

TEST_CASE("Stress") {
    std::vector<int> provinces(1e6);
    std::iota(provinces.begin(), provinces.end(), 1);
    REQUIRE(9839463073984 == CountPassports(provinces));
}
// NOLINTEND