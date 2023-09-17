#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
Iterator Partition(Iterator first, Iterator last, Comparator comparator) {
    auto pivot = std::prev(last, 1);
    auto temp = first;
    for (Iterator i = first; i != pivot; ++i) {
        if (comparator(*i, *pivot)) {
            std::swap(*i, *temp++);
        }
    }
    std::swap(*pivot, *temp);
    return temp;
}

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    if (begin < end) {
        auto temp = Partition(begin, end, comparator);
        Sort(begin, temp, comparator);
        Sort(++begin, end, comparator);
    }
}