#pragma once
#include <cstdlib>

struct StringViewOutOfRange {};

class StringView {
public:
    StringView();
    StringView(const char *source);  // NOLINT
    explicit StringView(const char *cstyle, size_t length);
    char operator[](size_t idx) const;
    char At(size_t idx) const;
    char Front() const;
    char Back() const;
    size_t Size() const;
    size_t Length() const;
    const char *Data() const;
    bool Empty() const;
    void Swap(StringView &other);
    void RemovePrefix(size_t prefix_size);
    void RemoveSuffix(size_t suffix_size);
    StringView Substr(size_t pos, size_t count = -1);

private:
    const char *string_;
    size_t size_;
};
