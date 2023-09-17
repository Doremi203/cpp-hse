#pragma once
#include <algorithm>

template <class T>
class Vector {
public:
    class Iterator;

    Vector() : arr_(nullptr), capacity_(0), size_() {
    }

    explicit Vector(size_t size) : capacity_(size), size_(size) {
        if (size_ != 0) {
            arr_ = new T[capacity_];
            std::fill(arr_, arr_ + size_, 0);
        }
    }

    Vector(T* arr, size_t size) : arr_(arr), capacity_(size), size_(size) {
        if (size_ != 0) {
            arr_ = new T[capacity_];
            std::copy(arr, arr + size_, arr_);
        }
    }

    Vector(const Vector& other) : Vector(other.arr_, other.size_) {
    }

    Vector(std::initializer_list<T> list) : Vector() {
        if (list.size() != 0) {
            size_ = list.size();
            capacity_ = size_;
            arr_ = new T[capacity_];
            std::copy(list.begin(), list.end(), arr_);
        }
    }

    Vector(Vector&& other) : arr_(other.arr_), size_(other.size_) {
        other.arr_ = nullptr;
    }

    ~Vector() {
        delete[] arr_;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (capacity_ != other.capacity_) {
                delete[] arr_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                arr_ = new T[capacity_];
            }
            std::copy(other.arr_, other.arr_ + other.size_, arr_);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) {
        if (this != &other) {
            /*size_ = other.size_;
            capacity_ = other.capacity_;
            delete[] arr_;
            arr_ = other.arr_;
            other.arr_ = nullptr;*/
            Swap(other);
        }
        return *this;
    }

    void PushBack(T element) {
        if (size_ >= capacity_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            }
            Reserve(capacity_ * 2);
        }
        arr_[size_++] = element;
    }

    void PopBack() {
        --size_;
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        capacity_ = new_capacity;
        auto temp = new T[capacity_];
        if (arr_) {
            std::copy(arr_, arr_ + size_, temp);
        }
        delete[] arr_;
        arr_ = temp;
    }

    void Swap(Vector& other) {
        std::swap(arr_, other.arr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    const T& operator[](size_t idx) const {
        return arr_[idx];
    }

    T& operator[](size_t idx) {
        return arr_[idx];
    }

    bool operator==(const Vector& second) const {
        if (Size() != second.Size()) {
            return false;
        }
        for (int i = 0; i < second.Size(); ++i) {
            if (arr_[i] != second[i]) {
                return false;
            }
        }
        return true;
    }

    Iterator Begin() const {
        return Iterator(&arr_[0]);
    }

    Iterator End() const {
        return Iterator(&arr_[size_]);
    }

    Iterator begin() const {  // NOLINT
        return Begin();
    }

    Iterator end() const {  // NOLINT
        return End();
    }

    class Iterator : std::iterator<std::random_access_iterator_tag, T> {
    public:
        Iterator() : ptr_() {
        }

        explicit Iterator(T* ptr) : ptr_(ptr) {
        }

        T& operator*() {
            return *ptr_;
        }

        T* operator->() {
            return ptr_;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr_;
            return temp;
        }

        Iterator& operator+=(int value) {
            ptr_ += value;
            return *this;
        }

        Iterator operator+(int value) {
            auto temp = *this;
            return temp += value;
        }

        Iterator& operator-=(int value) {
            ptr_ -= value;
            return *this;
        }

        size_t operator-(Iterator& other) {
            return ptr_ - other.ptr_;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

    private:
        T* ptr_;
    };

private:
    T* arr_;
    size_t capacity_;
    size_t size_;
};
