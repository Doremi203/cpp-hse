#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> res;
    if (from > to && step < 0) {
        for (int i = from; i > to; i += step) {
            res.push_back(i);
        }
    } else if (from < to && step > 0) {
        for (int i = from; i < to; i += step) {
            res.push_back(i);
        }
    }
    return res;
}