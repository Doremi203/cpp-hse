#include "range.h"

#include <catch.hpp>
#include <vector>

// NOLINTBEGIN
TEST_CASE("Simple") {
    {
        std::vector<int> expected{2, 3, 4};
        REQUIRE(expected == Range(2, 5, 1));
    }
    {
        std::vector<int> expected{1, 3};
        REQUIRE(expected == Range(1, 5, 2));
    }
    {
        const int x = -9;
        const int y = 6;
        std::vector<int> expected{x, -4, 1, y};
        REQUIRE(expected == Range(-9, 10, 5));
    }
}

TEST_CASE("SimpleReverse") {
    {
        const int x = 5;
        std::vector<int> expected{x, 4, 3};
        REQUIRE(expected == Range(5, 2, -1));
    }
    {
        const int x = 5;
        std::vector<int> expected{x, 3};
        REQUIRE(expected == Range(5, 1, -2));
    }
    {
        const int x = 7;
        std::vector<int> expected{x};
        REQUIRE(expected == Range(7, 6, -3));
    }
}

TEST_CASE("Empty") {
    REQUIRE(Range(0, 0, 2).empty());
    REQUIRE(Range(2, 2, 1).empty());
    REQUIRE(Range(10, 10, -2).empty());
}

TEST_CASE("EmptyInf") {
    REQUIRE(Range(3, 7, -1).empty());
    REQUIRE(Range(3, 4, 0).empty());
    REQUIRE(Range(5, -5, 2).empty());
    REQUIRE(Range(3, -7, 0).empty());
}
// NOLINTEND
