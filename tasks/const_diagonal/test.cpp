#include <algorithm>
#include "catch.hpp"

#include "const_diagonal.h"
TEST_CASE("Simple") {
    TableType table;

    BuildDiagonalArray(table);

    TableType answer = {{0, 1, 3, 6, 10, 15, 21, 28, 36, 45},
                        {2, 4, 7, 11, 16, 22, 29, 37, 46, 55},
                        {5, 8, 12, 17, 23, 30, 38, 47, 56, 64},
                        {9, 13, 18, 24, 31, 39, 48, 57, 65, 72},
                        {14, 19, 25, 32, 40, 49, 58, 66, 73, 79},
                        {20, 26, 33, 41, 50, 59, 67, 74, 80, 85},
                        {27, 34, 42, 51, 60, 68, 75, 81, 86, 90},
                        {35, 43, 52, 61, 69, 76, 82, 87, 91, 94},
                        {44, 53, 62, 70, 77, 83, 88, 92, 95, 97},
                        {54, 63, 71, 78, 84, 89, 93, 96, 98, 99}
    };

    for (size_t line = 0; line < LINES; ++line) {
        REQUIRE(std::equal(table[line], table[line] + COLUMNS, answer[line]));
    }
}
