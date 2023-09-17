#include <catch.hpp>

#include "stack.h"

TEST_CASE("Simple") {
    Stack s;
    s.Push(0);
    s.Push(1);
    s.Push(2);
    REQUIRE(2 == s.Top());
    s.Pop();
    REQUIRE(1 == s.Top());
    s.Pop();
    REQUIRE(0 == s.Top());
    s.Pop();
    REQUIRE(s.Empty());
}

TEST_CASE("Empty") {
    Stack s;
    REQUIRE(s.Empty());
    REQUIRE(0u == s.Size());
    s.Push(1);
    REQUIRE(!s.Empty());
    REQUIRE(1u == s.Size());
}

TEST_CASE("Long") {
    Stack s;
    const int iterations = 5e4;
    for (int i = 0; i < iterations; ++i) {
        s.Push(i);
    }
    for (int i = 0; i < iterations; ++i) {
        REQUIRE(iterations - i - 1 == s.Top());
        s.Pop();
    }
    REQUIRE(true == s.Empty());
    REQUIRE(0u == s.Size());
}
