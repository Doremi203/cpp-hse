#pragma once

template <class T>
class UniquePtr {
public:
    explicit UniquePtr(T* ptr = nullptr) : ptr_(ptr) {
    }

    UniquePtr(const UniquePtr& unique_ptr) {
    }

    UniquePtr(UniquePtr&& ptr) noexcept : ptr_(ptr.ptr_) {
        ptr.ptr_ = nullptr;
    }

    ~UniquePtr() {
        delete ptr_;
    }

    void Reset(T* other_ptr = nullptr) {
        auto old_ptr = ptr_;
        ptr_ = other_ptr;
        if (old_ptr) {
            delete old_ptr;
        }
    }

    UniquePtr& operator=(UniquePtr&& unique_ptr) {
        if (this != &unique_ptr) {
            delete ptr_;
            ptr_ = unique_ptr.ptr_;
            unique_ptr.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    const T& operator*() const {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    const T* operator->() const {
        return ptr_;
    }
    // put all required methods and operators here

    // see http://en.cppreference.com/w/cpp/memory/unique_ptr
    // and test.cpp

private:
    T* ptr_;
};
