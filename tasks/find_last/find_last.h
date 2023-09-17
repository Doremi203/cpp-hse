#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    auto res = last;
    while (first != last) {
        if (*first == val) {
            res = first;
        }
        ++first;
    }
    return res;
}
