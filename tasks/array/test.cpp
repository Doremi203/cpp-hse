#include <catch.hpp>

#include "array.h"

TEST_CASE("Empty") {
    Array<int> a;
    REQUIRE(a.size() == 0);
}

TEST_CASE("Constructor from other array") {
    Array<int> a{1, 2, 3};

    Array<int> b(a);

    REQUIRE(b.size() == 3);

    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 3);

    Array c{3, 3};

    REQUIRE(c[0] == 3);
    REQUIRE(c[1] == 3);

    b = c;

    REQUIRE(b.size() == 2);

    REQUIRE(b[0] == 3);
    REQUIRE(b[1] == 3);
}


TEST_CASE("Test initializer list") {
    Array<int> a{1, 2, 3};
    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 2);
    REQUIRE(a[2] == 3);

    a[0] = 3;

    REQUIRE(a[0] == 3);
}

TEST_CASE("Test const") {
    const Array<int> a{1, 2};

    REQUIRE(a.size() == 2);

    REQUIRE(a[0] == 1);
    REQUIRE(a[1] == 2);
}

TEST_CASE("Test Iteration") {
    Array<int> a{0, 1, 2, 3, 4};

    size_t current = 0;

    for (auto element : a) {
        REQUIRE(element == current);
        ++current;
    }
}