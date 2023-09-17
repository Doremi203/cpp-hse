#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array() {
        size_ = 0;
        data_ = nullptr;
    }

    explicit Array(size_t size) {
        size_ = size;
        if (size_ == 0) {
            data_ = nullptr;
        }
        data_ = new T[size_];
    }

    Array(std::initializer_list<T> list) : Array(list.size()) {
        int i = 0;
        for (auto item : list) {
            data_[i++] = item;
        }
    }

    Array(const Array& other) : Array(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    Array& operator=(const Array& other) {
        if (*this == other) {
            return *this;
        }
        if (size_ != other.size_) {
            auto temp = new T[other.size_];
            delete[] data_;
            size_ = other.size_;
            data_ = temp;
        }
        std::copy(other.data_, other.data_ + other.size_, data_);
        return *this;
    }

    bool operator==(const Array& other) {
        if (size_ != other.size_) {
            return false;
        }
        for (int i = 0; i < other.size_; ++i) {
            if (other[i] != data_[i]) {
                return false;
            }
        }
        return true;
    }

    ~Array() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t size() const {  // NOLINT
        return size_;
    }

    class Iterator {
    public:
        explicit Iterator(T* current) : current_(current){};

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        T& operator*() {
            return *current_;
        }

        bool operator!=(const Iterator& other) {
            return current_ != other.current_;
        }

    private:
        T* current_;
    };

    Iterator begin() const {  // NOLINT
        return Iterator(&data_[0]);
    }

    Iterator end() const {  // NOLINT
        return Iterator(&data_[size_]);
    }
};
