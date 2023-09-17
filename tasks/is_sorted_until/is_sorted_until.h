#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    while (begin < end) {
        if (*(begin + 1) < *begin++) {
            return begin;
        }
    }
    return end;
}
