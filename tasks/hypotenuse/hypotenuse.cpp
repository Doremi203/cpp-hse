#include "hypotenuse.h"

double CalculateHypotenuse(int64_t a, int64_t b) {
    return sqrt(static_cast<double>(a * a + b * b));
};
