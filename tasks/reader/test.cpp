#include <catch.hpp>

#include "reader.h"
#include "readers_util.h"
#include "utils.h"


TEST_CASE("StringReader") {
    REQUIRE(ReadAll(MakeStringReader("").get()).empty());
    REQUIRE("a" == ReadAll(MakeStringReader("a").get()));

    std::string big_string(1 << 15, 'f');  // NOLINT
    REQUIRE(big_string == ReadAll(MakeStringReader(big_string).get()));
}

TEST_CASE("LimitReader") {
    LimitReader l1(MakeStringReader(""), 0);
    REQUIRE(ReadAll(&l1).empty());

    LimitReader l2(MakeStringReader(" "), 0);
    REQUIRE(ReadAll(&l2).empty());

    LimitReader l3(MakeStringReader("ab"), 1);
    REQUIRE("a" == ReadAll(&l3));
}

TEST_CASE("TeeReader") {
    TeeReader t1({});
    REQUIRE(ReadAll(&t1).empty());

    TeeReader t2 = MakeTee({""});
    REQUIRE(ReadAll(&t2).empty());

    TeeReader t3 = MakeTee({"abc"});
    REQUIRE("abc" == ReadAll(&t3));

    TeeReader t4 = MakeTee({"abc", "def", "g"});
    REQUIRE("abcdefg" == ReadAll(&t4));

    TeeReader t5 = MakeTee({"abc", "", "def"});
    REQUIRE("abcdef" == ReadAll(&t5));

    TeeReader t6 = MakeTee({"abc", "", "", "", "", "def", "", ""});
    REQUIRE("abcdef" == ReadAll(&t6));
}

TEST_CASE("HexReader") {
    HexDecodingReader h1(MakeStringReader(""));
    REQUIRE(ReadAll(&h1).empty());

    HexDecodingReader h2(MakeStringReader("616263"));
    REQUIRE("abc" == ReadAll(&h2));

    std::string big_hex = "74657374666f6f626172";
    std::string answer = "testfoobar";
    for (int i = 0; i < 6; ++i) {
        big_hex += big_hex;
        answer += answer;
    }

    HexDecodingReader h3(MakeStringReader(big_hex));
    REQUIRE(answer == ReadAll(&h3));
}
