#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
public:
    StringOutOfRange() : std::out_of_range("StringOutOfRange") {
    }
};

class String {
    size_t size_;
    size_t capacity_;
    char *data_;

public:
    String();
    String(size_t size, char symbol);
    String(const char *src);  // NOLINT
    String(const char *src, size_t size);
    ~String();
    String(const String &other);
    String &operator=(const String &other);
    const char &operator[](size_t idx) const;
    char &operator[](size_t idx);
    const char &At(size_t idx) const;
    char &At(size_t idx);
    const char &Front() const;
    char &Front();
    const char &Back() const;
    char &Back();
    const char *Data() const;
    char *Data();
    const char *CStr() const;
    char *CStr();
    bool Empty() const;
    size_t Size() const;
    size_t Length() const;
    size_t Capacity() const;
    void Clear();
    void Swap(String &other);
    void PopBack();
    void PushBack(char c);
    void Resize(size_t new_size, char symbol);
    void Reserve(size_t new_capacity);
    void ShrinkToFit();
    int Compare(const String &other) const;
    String &operator+=(const String &other);
    friend String operator+(const String &first, const String &second);
};
#endif  // STRING_H

std::ostream &operator<<(std::ostream &stream, const String &string);
bool operator==(const String &first, const String &second);
bool operator!=(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
void SafeCpy(char *dest, const char *src, size_t len);