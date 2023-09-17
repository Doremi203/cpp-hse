#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int cur_num{0};
    int** res = new int*[lines];
    for (int i = 0; i < columns; ++i) {
        res[i] = new int[columns];
        for (int j = 0; j < i + 1; ++j) {
            *(*(res + j) + i - j) = cur_num;
            ++cur_num;
        }
    }
    for (int i = 1; i < columns; ++i) {
        for (int j = 0; j < columns - i; ++j) {
            *(*(res + i + j) + columns - j - 1) = cur_num;
            ++cur_num;
        }
    }
    return res;
}