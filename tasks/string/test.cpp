#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string_view>

#include "cppstring.h"
#include "cppstring.h"  // check include guards

void CheckEqual(const String& actual, std::string_view expected) {
    REQUIRE(actual.Capacity() >= actual.Size());
    REQUIRE(actual.Size() == expected.size());
    REQUIRE(actual.Length() == expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

TEST_CASE("Default", "[Constructor]") {
    const String s;
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Data() == nullptr);
    REQUIRE(s.Empty());
    CheckEqual(String(s), "");
}

// NOLINTBEGIN
TEST_CASE("FillInitialization", "[Constructor]") {
    {
        const String s(0, 'z');
        REQUIRE(s.Size() == 0u);
        REQUIRE(s.Capacity() == 0u);
        REQUIRE(s.Data() == nullptr);
    }

    {
        const String s(5, 'a');
        CheckEqual(s, "aaaaa");
    }
}

TEST_CASE("From C String", "[Constructor]") {
    {
        const String s = "abacaba";
        CheckEqual(s, "abacaba");
    }

    {
        const String s = "";
        REQUIRE(s.Capacity() == 0u);
        CheckEqual(s, "");
    }
}

TEST_CASE("Copy Constructor", "[Constructor]") {
    {
        const String empty;
        const auto copy = empty;
        REQUIRE(empty.Size() == 0u);
        REQUIRE(empty.Capacity() == 0u);
        REQUIRE(empty.Data() == nullptr);
        REQUIRE(copy.Size() == 0u);
        REQUIRE(copy.Capacity() == 0u);
        REQUIRE(copy.Data() == nullptr);
    }

    {
        const String s = "abacaba";
        const auto copy = s;
        CheckEqual(copy, "abacaba");
        CheckEqual(s, "abacaba");
    }
}

TEST_CASE("Copy Assignment", "[Assignment]") {
    SECTION("Empty to empty") {
        const String empty;
        String s;
        s = empty;
        REQUIRE(empty.Size() == 0u);
        REQUIRE(empty.Capacity() == 0u);
        REQUIRE(empty.Data() == nullptr);
        REQUIRE(s.Size() == 0u);
        REQUIRE(s.Capacity() == 0u);
        REQUIRE(s.Data() == nullptr);
    }

    SECTION("Small to large") {
        const String small(10, 'a');
        String large(1000, 'b');
        large = small;
        CheckEqual(large, std::string(10, 'a'));
        CheckEqual(small, std::string(10, 'a'));
    }
}

TEST_CASE("DataAccess", "[Methods]") {
    String s = "abcdef";

    {
        REQUIRE(s.Front() == 'a');
        s.Front() = 'z';
        REQUIRE(std::as_const(s).Front() == 'z');
    }

    {
        REQUIRE(s.Back() == 'f');
        s.Back() = 'y';
        REQUIRE(std::as_const(s).Back() == 'y');
    }

    {
        REQUIRE(s[1] == 'b');
        s[1] = 'x';
        REQUIRE(std::as_const(s)[1] == 'x');
    }
}

TEST_CASE("Swap", "[String]") {
    auto a = String();
    auto b = String();
    a.Swap(b);
    CheckEqual(a, "");
    CheckEqual(b, "");

}

TEST_CASE("Append", "[String]") {
    SECTION("PushBack") {
        String s;
        std::string actual("a");
        s.PushBack('a');
        for (size_t size = 1u; size < 1'000'000; size *= 2u) {
            for (size_t i = 0u; i < size; ++i) {
                s.PushBack(static_cast<char>('a' + i % 26));
                actual.push_back(static_cast<char>('a' + i % 26));
            }
            REQUIRE(s.Capacity() >= size * 2);
            CheckEqual(s, actual);
        }
    }

    SECTION("+=") {
        const String other = "abacaba";
        String s;
        (s += other) += other;
        CheckEqual(s, "abacabaabacaba");
        std::string actual("abacabaabacaba");
        for (size_t i = 0; i < 100000; ++i) {
            s += other;
            actual += "abacaba";
        }
        CheckEqual(s, actual);
    }

    SECTION("+") {
        {
            const String a;
            const String b;
            CheckEqual(a + b, "");
        }
    }
}

TEST_CASE("Clear", "[String]") {
    SECTION("Clear") {
        String s;
        s.Clear();
        CheckEqual(s, "");

        s = "aba";
        s.Clear();
        CheckEqual(s, "");

        for (size_t size = 1u; size < 1'000'000; size *= 2u) {
            for (size_t i = 0u; i < size; ++i) {
                s.PushBack(static_cast<char>('a' + i % 26));
            }
            s.Clear();
            CheckEqual(s, "");
        }
    }

    SECTION("PopBack") {
        String s("abacaba");
        s.PopBack();
        s.PopBack();
        CheckEqual(s, "abaca");

        for (size_t size = 1u; size < 1'000'000; size *= 2u) {
            for (size_t i = 0u; i < size; ++i) {
                s.PushBack(static_cast<char>('a' + i % 26));
            }
            for (size_t i = 0u; i < size; ++i) {
                s.PopBack();
            }
            CheckEqual(s, "abaca");
        }
    }
}

TEST_CASE("Resize", "[String]") {
    SECTION("Resize") {
        String a;
        a.Resize(5, 'a');
        CheckEqual(a, "aaaaa");

        a.Resize(3, 'b');
        CheckEqual(a, "aaa");
    }

    SECTION("Reserve") {
        String a("abacaba");
        REQUIRE(a.Capacity() < 15);

        a.Reserve(20);
        REQUIRE(a.Capacity() >= 20);
        CheckEqual(a, "abacaba");
    }

    SECTION("ShrinkToFit") {
        String a("abacaba");
        a.Reserve(100);
        REQUIRE(a.Capacity() > a.Size());
        a.ShrinkToFit();
        REQUIRE(a.Capacity() == a.Size());
        CheckEqual(a, "abacaba");

        a.Resize(0, 'a');
        CheckEqual(a, "");
        REQUIRE(a.Capacity() > 0u);
        a.ShrinkToFit();
        REQUIRE(a.Size() == 0u);
        REQUIRE(a.Capacity() == 0u);

        a = "aba";
        CheckEqual(a, "aba");
        REQUIRE(a.Capacity() >= 3u);
    }
}

void CheckComparisonEqual(const String& lhs, const String& rhs) {
    REQUIRE(lhs == rhs);
    REQUIRE(lhs <= rhs);
    REQUIRE(lhs >= rhs);
    REQUIRE_FALSE(lhs != rhs);
    REQUIRE_FALSE(lhs < rhs);
    REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonLess(const String& lhs, const String& rhs) {
    REQUIRE_FALSE(lhs == rhs);
    REQUIRE(lhs <= rhs);
    REQUIRE_FALSE(lhs >= rhs);
    REQUIRE(lhs != rhs);
    REQUIRE(lhs < rhs);
    REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonGreater(const String& lhs, const String& rhs) {
    REQUIRE_FALSE(lhs == rhs);
    REQUIRE_FALSE(lhs <= rhs);
    REQUIRE(lhs >= rhs);
    REQUIRE(lhs != rhs);
    REQUIRE_FALSE(lhs < rhs);
    REQUIRE(lhs > rhs);
}

TEST_CASE("Comparisons", "[String]") {
    {
        String a;
        String b;
        CheckComparisonEqual(a, b);
    }

    {
        String a;
        String b(1, 'a');
        CheckComparisonLess(a, b);
        CheckComparisonGreater(b, a);
    }
}

TEST_CASE("Output", "[String]") {
    auto oss = std::ostringstream();
    oss << String("abacaba") << ' ' << String() << ' ' << String(5, 'a');
    REQUIRE(oss.str() == "abacaba  aaaaa");
}
// NOLINTEND