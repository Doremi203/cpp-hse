#include <catch.hpp>

#include <array>
#include <vector>
#include <list>

#include "reversed.h"
#include "reversed.h"  // check include guards

TEST_CASE("Empty", "[Reversed]") {
    const auto empty = std::vector<int>{};
    for ([[maybe_unused]] auto&& x : Reversed(empty)) {
        REQUIRE(false);
    }
}

TEST_CASE("Elementary", "[Reversed]") {
    auto lst = std::list{1, -1, 4, 0, 2};
    auto copy = lst;

    {
        int i = static_cast<int>(lst.size()) - 1;
        auto lst_it = lst.rbegin();
        auto copy_it = copy.rbegin();
        for (auto&& x : Reversed(lst)) {
            REQUIRE(x == *lst_it);
            ++x;
            ++(*copy_it);
            --i;
            ++lst_it;
            ++copy_it;
        }
        REQUIRE(i == -1);
        REQUIRE(lst_it == lst.rend());
        REQUIRE(copy_it == copy.rend());
        REQUIRE(lst == copy);
    }

    {
        int i = static_cast<int>(lst.size()) - 1;
        auto copy_it = copy.rbegin();
        const auto reversed = Reversed(std::as_const(lst));
        for (auto&& x : reversed) {
            REQUIRE((std::is_same_v<decltype(x), const int&>));
            REQUIRE(x == *copy_it);
            --i;
            ++copy_it;
        }
        REQUIRE(i == -1);
    }
}