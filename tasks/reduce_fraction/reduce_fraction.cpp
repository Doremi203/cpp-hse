#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t r = 0;
    int64_t x = numerator;
    int64_t y = denominator;
    while ((r = (x % y)) > 0) {
        x = y;
        y = r;
    }
    return (numerator + denominator) / y;
}
