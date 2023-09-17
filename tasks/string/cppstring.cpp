#include "cppstring.h"

String::String() : size_(0), capacity_(0), data_(nullptr) {
}

String::String(size_t size, char symbol) : String() {
    if (size != 0) {
        size_ = size;
        capacity_ = size * 2;
        data_ = new char[capacity_];
        std::fill(data_, data_ + size, symbol);
    }
}

String::String(const char* src) : size_(0) {
    while (*src++ != '\0') {
        ++size_;
    }
    capacity_ = size_ * 2;
    data_ = new char[capacity_];
    std::copy(src - size_ - 1, src, data_);
}

String::String(const char* src, size_t size) {
    size_ = size;
    capacity_ = size_ * 2;
    data_ = new char[capacity_];
    std::copy(src, src + size_, data_);
}

String::~String() {
    delete[] data_;
}

String::String(const String& other) : String() {
    if (other.size_ != 0) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
}

String& String::operator=(const String& other) {
    if (!(*this == other)) {
        if (capacity_ != other.capacity_) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new char[capacity_];
        }
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    return *this;
}

const char& String::operator[](size_t idx) const {
    return data_[idx];
}

char& String::operator[](size_t idx) {
    return data_[idx];
}

const char& String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

char& String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

const char& String::Front() const {
    return *data_;
}

char& String::Front() {
    return *data_;
}

const char& String::Back() const {
    return data_[size_ - 1];
}

char& String::Back() {
    return data_[size_ - 1];
}

const char* String::Data() const {
    return data_;
}

char* String::Data() {
    return data_;
}

const char* String::CStr() const {
    data_[size_] = '\0';
    return data_;
}

char* String::CStr() {
    data_[size_] = '\0';
    return data_;
}

bool String::Empty() const {
    return size_ == 0;
}

size_t String::Size() const {
    return size_;
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    size_ = 0;
}

void String::Swap(String& other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

void String::PopBack() {
    --size_;
}

void String::PushBack(char c) {
    if (++size_ >= capacity_) {
        if (capacity_ == 0) {
            capacity_ = size_;
        }
        Reserve(capacity_ * 2);
    }
    data_[size_ - 1] = c;
}

void String::Resize(size_t new_size, char symbol) {
    auto temp = size_;
    if (new_size > temp) {
        Reserve(new_size * 2);
        for (int i = 0; i < new_size - temp; ++i) {
            PushBack(symbol);
        }
    } else {
        size_ = new_size;
    }
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity < capacity_) {
        return;
    }
    capacity_ = new_capacity;
    auto temp = new char[capacity_];
    if (data_) {
        std::copy(data_, data_ + size_, temp);
    }
    delete[] data_;
    data_ = temp;
}

void String::ShrinkToFit() {
    if (size_ == 0) {
        capacity_ = 0;
    } else {
        capacity_ = size_;
    }
}

int String::Compare(const String& other) const {
    if (*this == other) {
        return 0;
    } else if (*this < other) {
        return -1;
    }
    return 1;
}

String& String::operator+=(const String& other) {
    for (int i = 0; i < other.size_; ++i) {
        PushBack(other[i]);
    }
    return *this;
}
String operator+(const String& first, const String& second) {
    auto temp = first;
    return temp += second;
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
    for (int i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}

bool operator==(const String& first, const String& second) {
    if (first.Size() != second.Size()) {
        return false;
    }
    for (int i = 0; i < second.Size(); ++i) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const String& first, const String& second) {
    return !(first == second);
}

bool operator>(const String& first, const String& second) {
    return first >= second && first != second;
}

bool operator<(const String& first, const String& second) {
    return std::lexicographical_compare(first.Data(), first.Data() + first.Size(), second.Data(),
                                        second.Data() + second.Size());
}

bool operator>=(const String& first, const String& second) {
    return !(first < second);
}

bool operator<=(const String& first, const String& second) {
    return !(first > second);
}

void SafeCpy(char* dest, const char* src, size_t len) {
}