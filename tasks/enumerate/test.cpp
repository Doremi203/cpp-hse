#include <array>
#include <catch.hpp>
#include <forward_list>
#include <vector>

#include "enumerate.h"
#include "enumerate.h"  // check include guards

TEST_CASE("Empty", "[Enumerate]") {
    const auto empty = std::vector<int>{};
    for ([[maybe_unused]] auto&& [i, x] : Enumerate(empty)) {
        REQUIRE(false);
    }
}

TEST_CASE("Elementary", "[Enumerate]") {
    {
        auto lst = std::forward_list{1, -1, 4, 0, 2};
        auto copy = lst;
        auto i = 0;
        auto lst_it = lst.begin();
        auto copy_it = copy.begin();
        for (auto&& [id, value] : Enumerate(lst)) {
            REQUIRE(value == *lst_it);
            REQUIRE(static_cast<int>(id) == i);
            ++value;
            ++(*copy_it);
            ++i;
            ++lst_it;
            ++copy_it;
        }
        REQUIRE(i == 5);
        REQUIRE(lst_it == lst.end());
        REQUIRE(copy_it == copy.end());
        REQUIRE(lst == copy);

        i = 0;
        copy_it = copy.begin();
        const auto enumerate = Enumerate(std::as_const(lst));
        for (auto&& [id, value] : enumerate) {
            REQUIRE((std::is_same_v<decltype(value), const int&>));
            REQUIRE(static_cast<int>(id) == i);
            REQUIRE(value == *copy_it);
            ++i;
            ++copy_it;
        }
        REQUIRE(i == 5);
    }
}
