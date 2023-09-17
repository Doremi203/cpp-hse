#include <array>
#include <cassert>
#include <catch.hpp>
#include <vector>

#include "remove.h"

TEST_CASE("Simple") {
    std::vector<int> a{1, 2, 3, 1, 1, 4, 5, 1, 6, 1};
    REQUIRE(Remove(a.begin(), a.begin(), 1) == a.begin());

    REQUIRE(Remove(a.begin() + 1, a.begin() + 3, 1) == a.begin() + 3);

    REQUIRE(Remove(a.begin(), a.end(), 1) == a.begin() + 5);
}

TEST_CASE("Big") {
    const auto size = 1'000'002;
    std::vector<int> a;
    a.reserve(size);
    for (int i = 0; i < size; ++i) {
        a.push_back(i % 3);
    }
    REQUIRE(Remove(a.begin(), a.end(), 0) == a.begin() + 2 * size / 3);
}
