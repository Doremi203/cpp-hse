#include "catch.hpp"

#include "rational.h"


TEST_CASE("Simple") {
   Rational r(2, 4);
   REQUIRE(r.GetNumerator() == 1);
   REQUIRE(r.GetDenominator() == 2);

   Rational q(2, 3);

   auto s = r + q;

   REQUIRE(s > 1);
   REQUIRE(s.GetDenominator() == 6);
}
