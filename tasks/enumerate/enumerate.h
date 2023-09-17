#pragma once

#include <functional>
#include <utility>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class T>
concept HasBeginEnd = requires(T a) {
    a.begin();
    a.end();
};

template <class T>
class MyIterator {
public:
    explicit MyIterator(T value) : iter_(value), number_() {
    }

    MyIterator& operator++() {
        ++iter_;
        ++number_;
        return *this;
    }

    bool operator!=(const MyIterator& other) {
        return iter_ != other.iter_;
    }

    auto operator*() {
        return std::make_pair(number_, std::ref(*iter_));
    }

private:
    T iter_;
    std::size_t number_;
};
template <HasBeginEnd Enumerable>
auto Enumerate(Enumerable& enumerable) {
    return IteratorRange(MyIterator(enumerable.begin()), MyIterator(enumerable.end()));
}