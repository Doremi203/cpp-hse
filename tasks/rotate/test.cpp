#include <catch.hpp>
#include <vector>

#include "rotate.h"

template <class T>
void Equal(const std::vector<T>& actual, const std::vector<T>& expected) {
    for (int i = 0; i < actual.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

// NOLINTBEGIN
TEST_CASE("Reverse") {
    std::vector<int> a{1, 2, 3, 4, 5};

    Reverse(a.begin(), a.begin() + 5);
    Equal(a, {5, 4, 3, 2, 1});
}

TEST_CASE("Rotate") {
    std::vector<int> a{1, 2, 3, 4, 5};
    Rotate(a.begin(), a.begin(), a.begin() + 5);
    Equal(a, {1, 2, 3, 4, 5});

    {
        const auto size = 1'000'000;
        std::vector<int> large(size);
    
        for (int i = 0; i < size; ++i) {
            large[i] = i;
        }
        const auto mid = size / 10;
        Rotate(large.begin(), large.begin() + mid, large.end());
        for (int i = mid; i < size; ++i) {
            REQUIRE(large[i - mid] == i);
        }
        for (int i = 0; i < mid; ++i) {
            REQUIRE(large[size - mid + i] == i);
        }
    }
}
// NOLINTEND