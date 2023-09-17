#include <catch.hpp>

#include "is_sorted_until.h"

struct NonCopyableInt {
    int x = 0;

    NonCopyableInt(int x) : x(x) {  // NOLINT (explicit)
    }

    NonCopyableInt(const NonCopyableInt&) = delete;
    NonCopyableInt(NonCopyableInt&&) = default;

    NonCopyableInt& operator=(const NonCopyableInt&) = delete;
    NonCopyableInt& operator=(NonCopyableInt&&) = default;

    [[nodiscard]] bool operator<(const NonCopyableInt& other) const noexcept {
        return x < other.x;
    }
};

TEST_CASE("Simple") {
    std::vector<int> data{{1, 1, 2, 2, 3, 3, 3, 2, 4, 5, 6}};  // NOLINT
    std::vector<NonCopyableInt> a;

    for (auto element : data) {
        a.emplace_back(element);
    }

    REQUIRE(IsSortedUntil(a.begin(), a.begin()) == a.begin());
    REQUIRE(IsSortedUntil(a.begin(), a.end()) == a.begin() + 7);
    REQUIRE(IsSortedUntil(a.begin(), a.begin() + 5) == a.begin() + 5);
}