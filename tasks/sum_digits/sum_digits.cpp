#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    int64_t sum = 0;
    const auto k = 10;
    while (number) {
        sum += number % k;
        number /= k;
    }
    return sum;
}