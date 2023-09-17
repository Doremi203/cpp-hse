#include "factorization.h"

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> res;
    int64_t copy = x;
    for (int64_t i = 2; i * i <= copy; ++i) {
        int counter{0};
        while (x % i == 0) {
            ++counter;
            x /= i;
        }
        if (counter > 0) {
            res.emplace_back(i, counter);
        }
    }
    if (x != 1) {
        res.emplace_back(x, 1);
    }
    return res;
}
