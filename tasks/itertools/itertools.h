#pragma once
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

template <class T, class U>
struct ZipIterator {
    ZipIterator(T first, U second) : first_(first), second_(second) {
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }

    bool operator!=(const ZipIterator<T, U>& other) {
        return first_ != other.first_ && second_ != other.second_;
    }

    auto operator*() {
        return std::make_pair(*first_, *second_);
    }

private:
    T first_;
    U second_;
};

template <class T>
struct GroupIterator {
    GroupIterator(T start, T end) : cur_(start), end_(end) {
        GetCurEnd();
    }

    GroupIterator& operator++() {
        cur_ = cur_end_;
        GetCurEnd();
        return *this;
    }

    bool operator!=(const GroupIterator<T>& other) {
        return cur_ != other.cur_;
    }

    auto operator*() {
        return IteratorRange(cur_, cur_end_);
    }

private:
    T cur_;
    T cur_end_;
    T end_;

    void GetCurEnd() {
        auto temp = cur_;
        while (temp != end_ && *temp == *cur_) {
            ++temp;
        }
        cur_end_ = temp;
    }
};

template <class T>
struct RangeIterator {
    RangeIterator() : step_(1), value_() {
    }

    explicit RangeIterator(T value) : step_(1), value_(value) {
    }

    RangeIterator(T value, T step) : step_(step), value_(value) {
    }

    RangeIterator& operator++() {
        value_ += step_;
        return *this;
    }

    bool operator!=(const RangeIterator<T>& other) {
        return value_ < other.value_;
    }

    T& operator*() {
        return value_;
    }

private:
    T step_;
    T value_;
};

template <class T>
IteratorRange<RangeIterator<T>> Range(T end) {
    return IteratorRange<RangeIterator<T>>(RangeIterator<T>(), RangeIterator<T>(end));
}

template <class T>
IteratorRange<RangeIterator<T>> Range(T from, T end) {
    return IteratorRange<RangeIterator<T>>(RangeIterator<T>(from), RangeIterator<T>(end));
}

template <class T>
IteratorRange<RangeIterator<T>> Range(T from, T end, T step) {
    return IteratorRange<RangeIterator<T>>(RangeIterator<T>(from, step), RangeIterator<T>(end, step));
}

template <HasBeginEnd T, HasBeginEnd U>
auto Zip(const T& first, const U& second) {
    return IteratorRange(ZipIterator(first.begin(), second.begin()), ZipIterator(first.end(), second.end()));
}

template <HasBeginEnd T>
auto Group(const T& data) {
    return IteratorRange(GroupIterator(data.begin(), data.end()), GroupIterator(data.end(), data.end()));
}
