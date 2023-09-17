#include <catch.hpp>

#include "sort.h"

TEST_CASE("Simple") {
    {
        std::vector<int> a{1, 3, 2};
        std::vector<int> expected_result{1, 2, 3};
        Sort(a.begin(), a.end());
        REQUIRE(std::equal(a.begin(), a.end(), expected_result.begin(), expected_result.end()));
    }

    {
        std::vector<int> a{1, -3, 2};
        std::vector<int> expected_result{1, 2, -3};
        Sort(a.begin(), a.end(), [](int lhs, int rhs) { return std::abs(lhs) < std::abs(rhs); });
        REQUIRE(std::equal(a.begin(), a.end(), expected_result.begin(), expected_result.end()));
    }

    {
        std::vector<std::string> a{"ab", "a", "b", "aaa"};
        std::vector<std::string> expected_result = a;
        Sort(a.begin(), a.end());
        std::sort(expected_result.begin(), expected_result.end());
        REQUIRE(std::equal(a.begin(), a.end(), expected_result.begin(), expected_result.end()));
    }
}

// NOLINTBEGIN
TEST_CASE("Other types") {
    {
        int a[5] = {1, 5, 3, 4, 2};
        int expected_result[5] = {1, 2, 3, 4, 5};
        Sort(a, a + 5);
        REQUIRE(std::equal(a, a + 5, expected_result, expected_result + 5));
    }
}
// NOLINTEND

struct Int {
    int value;

    Int(const Int& other) = delete;
    Int operator=(const Int& other) = delete;

    Int(Int&& other) {
        std::swap(value, other.value);
    }

    Int& operator=(Int&& other) {
        std::swap(value, other.value);
        return *this;
    }

    explicit Int(int value) : value(value){};

    bool operator<(const Int& other) const {
        return value < other.value;
    }
};

// NOLINTBEGIN
TEST_CASE("No copy constructor") {
    std::vector<Int> a;
    a.emplace_back(1);
    a.emplace_back(-10);
    a.emplace_back(-4);
    a.emplace_back(-6);
    Sort(a.begin(), a.end());
    REQUIRE(a[0].value == -10);
    REQUIRE(a[1].value == -6);
    REQUIRE(a[2].value == -4);
    REQUIRE(a[3].value == 1);
}
// NOLINTEND