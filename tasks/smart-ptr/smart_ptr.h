#pragma once

#include <string>

struct Counter {
    size_t weak_count;
    size_t strong_count;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    T* ptr_;
    Counter* counter_;

    void Erase() {
        if (counter_) {
            --counter_->strong_count;
            if (!counter_->strong_count) {
                delete ptr_;
                if (!counter_->weak_count) {
                    delete counter_;
                }
            }
        }
    }

public:
    friend class WeakPtr<T>;

    // SharedPtr() : ptr_(), counter_(new Counter{0, 1}) {
    // }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->strong_count;
    }

    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
    }

    explicit SharedPtr(const WeakPtr<T>& rhs) : ptr_(rhs.ptr_), counter_(rhs.counter_) {
        if (counter_->strong_count == 0) {
            ptr_ = nullptr;
        }
        ++counter_->strong_count;
    }

    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), counter_(new Counter{0, 1}) {
    }

    ~SharedPtr() {
        Erase();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (other.ptr_ != ptr_) {
            Erase();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->strong_count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) {
        if (ptr_ != other.ptr_) {
            Erase();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            other.ptr_ = nullptr;
            other.counter_ = nullptr;
        }
        return *this;
    }

    SharedPtr& operator=(T* ptr) {
        if (ptr != ptr_) {
            Erase();
            ptr_ = ptr;
            counter_ = new Counter{0, 1};
        }
        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    T* Get() const {
        return ptr_;
    }

    void Reset(T* ptr = nullptr) {
        if (ptr_ != ptr) {
            Erase();
            ptr_ = ptr;
            counter_ = new Counter{0, 1};
        }
    }
};

template <class T>
class WeakPtr {
    T* ptr_;
    Counter* counter_;

    void Erase() {
        if (counter_) {
            --counter_->weak_count;
            if (counter_->strong_count == 0 && counter_->weak_count == 0) {
                delete counter_;
            }
        }
    }

public:
    friend class SharedPtr<T>;

    WeakPtr() : ptr_(), counter_(new Counter{1, 0}) {
    }

    explicit WeakPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->weak_count;
    }

    WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->weak_count;
    }

    WeakPtr(WeakPtr&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
    }

    ~WeakPtr() {
        Erase();
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (ptr_ != other.ptr_) {
            Erase();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->weak_count;
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) {
        if (ptr_ != other.ptr_) {
            Erase();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ptr_ = nullptr;
            counter_ = nullptr;
        }
        return *this;
    }

    SharedPtr<T> Lock() {
        if (IsExpired()) {
            return SharedPtr<T>();
        }
        return SharedPtr(*this);
    }

    T* Get() const {
        return ptr_;
    }

    bool IsExpired() {
        return counter_->strong_count == 0;
    }
};
