#include <array>
#include <catch.hpp>

#include "copy.h"

template <class T>
void Equal(const std::vector<T>& actual, const std::vector<T>& expected) {
    for (int i = 0; i < actual.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

// NOLINTBEGIN
TEST_CASE("Copy") {
    std::vector<int> src{1, 2, 3};
    std::vector<int> dest{5, 6, 7, 8};

    REQUIRE(Copy(src.begin() + 1, src.begin() + 1, dest.begin()) == dest.begin());
    Equal(dest, {5, 6, 7, 8});

    REQUIRE(Copy(src.begin(), src.begin() + 3, dest.begin()) == dest.begin() + 3);
    Equal(dest, {1, 2, 3, 8});
}

TEST_CASE("CopyBackward") {
    std::vector<int> src{1, 2, 3};
    std::vector<int> dest{5, 6, 7, 8};

    REQUIRE(CopyBackward(src.begin() + 1, src.begin() + 1, dest.begin()) == dest.begin());
    Equal(dest, {5, 6, 7, 8});

    REQUIRE(CopyBackward(src.begin(), src.begin() + 3, dest.begin() + 3) == dest.begin());
    Equal(dest, {1, 2, 3, 8});
}
//// NOLINTEND