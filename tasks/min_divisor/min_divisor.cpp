#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return i;
        }
    }
    return number;
}
