#pragma once

#include <set>

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return begin;
    }
    auto second = begin;
    for (; begin < end; ++begin) {
        if (*begin != *second) {
            std::swap(*begin, *++second);
        }
    }
    return ++second;
}