#include <catch.hpp>
#include <cstring>

#include "cstring.h"

bool SameSign(int x, int y) {
    return (x >= 0) ^ (y < 0);
}

TEST_CASE("Strlen") {
    const char* a = "";
    const char* b = "a";
    const char* c = "a#b$c\n0\t";

    REQUIRE(Strlen(a) == std::strlen(a));
    REQUIRE(Strlen(b) == std::strlen(b));
    REQUIRE(Strlen(c) == std::strlen(c));
}

TEST_CASE("Strcmp") {
    const char a[] = "";
    const char aa[] = "";
    const char b[] = "abca";
    const char bb[] = "abca";

    REQUIRE(SameSign(Strcmp(a, a), std::strcmp(a, a)));
    REQUIRE(SameSign(Strcmp(a, aa), std::strcmp(a, aa)));
    REQUIRE(SameSign(Strcmp(b, b), std::strcmp(b, b)));
    REQUIRE(SameSign(Strcmp(b, bb), std::strcmp(b, bb)));
}

TEST_CASE("Strncmp") {
    const char a[] = "";
    const char aa[] = "";
    const char b[] = "abca";

    REQUIRE(SameSign(Strncmp(a, a, 0), std::strncmp(a, a, 0)));
    REQUIRE(SameSign(Strncmp(a, aa, 100), std::strncmp(a, aa, 100)));
    REQUIRE(SameSign(Strncmp(b, b, 100), std::strncmp(b, b, 100)));
}

TEST_CASE("Strchr") {
    const char* a = "";
    const char* b = "k#ba$ca\nb\t0e";

    REQUIRE(Strchr(a, 'a') == std::strchr(a, 'a'));
    REQUIRE(Strchr(a, '\0') == std::strchr(a, '\0'));
    REQUIRE(Strchr(b, 'd') == std::strchr(b, 'd'));
}

TEST_CASE("Strrchr") {
    const char* a = "";

    REQUIRE(Strrchr(a, 'a') == std::strrchr(a, 'a'));
    REQUIRE(Strrchr(a, '\0') == std::strrchr(a, '\0'));
}

TEST_CASE("Strspn") {
    const char* a = "";
    const char* b = "abc";

    REQUIRE(Strspn(a, a) == std::strspn(a, a));
    REQUIRE(Strspn(b, b) == std::strspn(b, b));
    REQUIRE(Strspn(b, a) == std::strspn(b, a));
}

TEST_CASE("Strcspn") {
    const char* a = "";
    const char* b = "abc";

    REQUIRE(Strcspn(a, a) == std::strcspn(a, a));
    REQUIRE(Strcspn(b, b) == std::strcspn(b, b));
    REQUIRE(Strcspn(b, a) == std::strcspn(b, a));
}

TEST_CASE("Strpbrk") {
    const char* a = "";
    const char* b = "abc";
    REQUIRE(Strpbrk(a, a) == std::strpbrk(a, a));
    REQUIRE(Strpbrk(b, b) == std::strpbrk(b, b));
    REQUIRE(Strpbrk(b, a) == std::strpbrk(b, a));
}

TEST_CASE("Strstr") {
    const char* a = "";
    const char* b = "aabc";
    REQUIRE(Strstr(a, a) == std::strstr(a, a));
    REQUIRE(Strstr(b, b) == std::strstr(b, b));
}

TEST_CASE("Strcpy") {
    const char* a = "";
    char c[10] = "defg";

    REQUIRE(std::strcmp("fg", Strcpy(c, c + 2)) == 0);
    REQUIRE(std::strcmp("f", Strcpy(c + 1, a) - 1) == 0);
}

TEST_CASE("Strncpy") {
    const char* a = "";
    char c[10] = "defg";

    REQUIRE(std::strcmp("fg", Strncpy(c, c + 2, 5)) == 0);
    REQUIRE(std::strcmp("f", Strncpy(c + 1, a, 5) - 1) == 0);
}

TEST_CASE("Strcat") {
    const char* a = "";
    const char* b = "abc";
    char c[10]{};

    REQUIRE(std::strcmp("", Strcat(c, a)) == 0);
    REQUIRE(std::strcmp("abc", Strcat(c, b)) == 0);
}

TEST_CASE("Strncat") {
    const char* a = "";
    const char* b = "abc";
    char c[10]{};

    REQUIRE(std::strcmp("", Strncat(c, a, 5)) == 0);
    REQUIRE(std::strcmp("ab", Strncat(c, b, 2)) == 0);
}
