#include <catch.hpp>
#include <vector>

#include "unique.h"

template <class T>
void Equal(const std::vector<T>& actual, const std::vector<T>& expected) {
    for (int i = 0; i < expected.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

// NOLINTBEGIN
TEST_CASE("Unique") {
    std::vector<int> a{1, 1, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7};

    REQUIRE(Unique(a.begin(), a.begin()) == a.begin());
    Equal(a, {1, 1, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7});

    REQUIRE(Unique(a.begin(), a.begin() + 12) == a.begin() + 7);
    Equal(a, {1, 2, 3, 4, 5, 6, 7});

    {
        const auto size = 1'000'000;
        std::vector<int> large(size);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < size / 10; ++j) {
                large[i * size / 10 + j] = i;
            }
        }
        REQUIRE(Unique(large.begin(), large.end()) == large.begin() + 10);
        Equal(large, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    }
}

// NOLINTEND