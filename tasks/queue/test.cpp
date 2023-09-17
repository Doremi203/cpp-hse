#include <catch.hpp>

#include "queue.h"

TEST_CASE("Simple") {
    Queue s;
    s.Push(0);
    s.Push(1);
    s.Push(2);
    REQUIRE(0 == s.Front());
    s.Pop();
    REQUIRE(1 == s.Front());
    s.Pop();
    REQUIRE(2 == s.Front());
    s.Pop();
    REQUIRE(s.Empty());
}

TEST_CASE("Empty") {
    Queue s;
    REQUIRE(s.Empty());
    REQUIRE(0u == s.Size());
    s.Push(1);
    REQUIRE(!s.Empty());
    REQUIRE(1u == s.Size());
}

TEST_CASE("Long") {
    Queue s;
    const int iterations = 5e4;
    for (int i = 0; i < iterations; ++i) {
        s.Push(i);
    }
    for (int i = 0; i < iterations; ++i) {
        REQUIRE(i == s.Front());
        s.Pop();
    }
    REQUIRE(true == s.Empty());
    REQUIRE(0u == s.Size());
}
