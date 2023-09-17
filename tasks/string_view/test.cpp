#include <catch.hpp>

#include "string_view.h"

void Equal(const StringView& actual, const char* expected, size_t n) {
    REQUIRE(actual.Data() == expected);
    REQUIRE(actual.Size() == n);
    REQUIRE(actual.Length() == n);
    REQUIRE(actual.Empty() == (n == 0));
    for (size_t i = 0; i < n; ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

TEST_CASE("Default", "[Constructor]") {
    const StringView sv;
    Equal(sv, nullptr, 0);
}

TEST_CASE("From C String", "[Constructor]") {
    const char* str = "aba";
    const StringView sv = str;
    Equal(sv, str, 3);
}

TEST_CASE("Copy", "[Constructor]") {
    const char* str = "abacaba";
    const StringView sv(str + 2, 4);
    const auto copy = sv;
    Equal(sv, str + 2, 4);
    Equal(copy, str + 2, 4);
}

TEST_CASE("DataAccess", "[Methods]") {
    static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>().Front()), char>);
    static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>().Back()), char>);
    static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>().At(0)), char>);
    static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>()[0]), char>);

    const StringView sv = "abcdef";

    REQUIRE(sv.Front() == 'a');
    REQUIRE(sv.Back() == 'f');
    REQUIRE(sv[1] == 'b');
    REQUIRE(sv.At(2) == 'c');
    REQUIRE_THROWS_AS(sv.At(6), StringViewOutOfRange);
}

// NOLINTBEGIN
TEST_CASE("RemovePrefix", "[Modifications]") {
    const char* str = "some_test_string";
    StringView sv = str;

    sv.RemovePrefix(5);
    Equal(sv, str + 5, 11);
}

TEST_CASE("RemoveSuffix", "[Modifications]") {
    const char* str = "some_test_string";
    StringView sv = str;

    sv.RemoveSuffix(5);
    Equal(sv, str, 11);
}

TEST_CASE("Substr", "[Modifications]") {
    const char* str = "some_test_string";
    StringView sv = str;

    Equal(sv.Substr(0, 5), str, 5);
    Equal(sv, str, 16);
}

TEST_CASE("Swap", "[Modifications]") {
    const char* str = "some_test_string";
    StringView sv = str;

    sv.Substr(2, 7).Swap(sv);
    Equal(sv, str + 2, 7);
}
// NOLINTEND
