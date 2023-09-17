#pragma once

#include <algorithm>

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    auto second = begin;
    while (second < end) {
        if (*begin == value) {
            if (*second != value) {
                std::swap(*second, *begin++);
            }
        } else {
            ++begin;
        }
        ++second;
    }
    return begin;
}