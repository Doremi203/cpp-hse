#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t a_0 = 0;
    int64_t a_1 = 1;
    int64_t temp = 1;
    if (n == a_0) {
        return 0;
    }
    if (n == a_1) {
        return 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        temp = a_0 + a_1;
        a_0 = a_1;
        a_1 = temp;
    }
    return temp;
}
