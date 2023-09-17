#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int cur_num{0};
    for (int i = 0; i < COLUMNS; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            *(*(table + j) + i - j) = cur_num;
            cur_num++;
        }
    }
    for (int i = 1; i < COLUMNS; ++i) {
        for (int j = 0; j < COLUMNS - i; ++j) {
            *(*(table + i + j) + COLUMNS - j - 1) = cur_num;
            cur_num++;
        }
    }
}