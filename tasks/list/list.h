#pragma once

#include <utility>

struct ListNode {
    ListNode(ListNode* next, ListNode* prev) : next_(next), prev_(prev) {
    }

    virtual ~ListNode() {
        delete next_;
    }

    ListNode* next_;
    ListNode* prev_;
};

template <class T>
struct ListNodeValue : ListNode {
    ListNodeValue(const T& el, ListNode* next, ListNode* prev) : ListNode(next, prev), value_(el) {
    }

    ListNodeValue(T&& el, ListNode* next, ListNode* prev) : ListNode(next, prev), value_(std::move(el)) {
    }

    T value_;
};

template <typename T>
class List {
public:
    class Iterator {
    public:
        explicit Iterator(ListNode* ptr) : ptr_(ptr) {
        }

        Iterator& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }

        Iterator operator++(int) {
            auto temp = *this;
            ptr_ = ptr_->next_;
            return temp;
        }

        Iterator& operator--() {
            ptr_ = ptr_->prev_;
            return *this;
        }

        Iterator operator--(int) {
            auto temp = *this;
            ptr_ = ptr_->prev_;
            return temp;
        }

        T& operator*() const {
            return static_cast<ListNodeValue<T>*>(ptr_)->value_;
        }

        T* operator->() const {
            return static_cast<ListNodeValue<T>*>(ptr_);
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }

    private:
        ListNode* ptr_;
    };

    List() : front_(nullptr), end_(nullptr), pseudo_end_(new ListNode(nullptr, nullptr)), size_() {
    }

    List(const List& other) : List() {
        for (auto& item : other) {
            PushBack(item);
        }
    }

    List(List&& other) : front_(other.front_), end_(other.end_), pseudo_end_(other.pseudo_end_), size_(other.size_) {
        other.front_ = nullptr;
        other.end_ = nullptr;
        other.pseudo_end_ = nullptr;
        other.size_ = 0;
    }

    ~List() {
        Clear();
    }

    void Clear() {
        if (size_) {
            end_->next_ = pseudo_end_;
            delete front_;
            size_ = 0;
        } else {
            delete pseudo_end_;
        }
        front_ = nullptr;
        end_ = nullptr;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            Clear();
            pseudo_end_ = new ListNode(nullptr, nullptr);
            size_ = 0;
            for (auto& item : other) {
                PushBack(item);
            }
        }
        return *this;
    }

    List& operator=(List&& other) {
        if (this != &other) {
            Clear();
            front_ = other.front_;
            end_ = other.end_;
            pseudo_end_ = other.pseudo_end_;
            size_ = other.size_;
            other.front_ = nullptr;
            other.end_ = nullptr;
            other.pseudo_end_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    std::size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        ListNode* node = new ListNodeValue<T>(elem, nullptr, end_);
        if (size_ == 0) {
            end_ = node;
            front_ = node;
        } else {
            end_->next_ = node;
            end_ = node;
        }
        end_->next_ = pseudo_end_;
        pseudo_end_->prev_ = end_;
        ++size_;
    }

    void PushBack(T&& elem) {
        ListNode* node = new ListNodeValue<T>(std::move(elem), nullptr, end_);
        if (size_ == 0) {
            end_ = node;
            front_ = node;
        } else {
            end_->next_ = node;
            end_ = node;
        }
        end_->next_ = pseudo_end_;
        pseudo_end_->prev_ = end_;
        ++size_;
    }

    void PushFront(const T& elem) {
        ListNode* node = new ListNodeValue<T>(elem, front_, nullptr);
        if (size_ == 0) {
            end_ = node;
            front_ = node;
        } else {
            front_->prev_ = node;
            front_ = node;
        }
        end_->next_ = pseudo_end_;
        pseudo_end_->prev_ = end_;
        ++size_;
    }

    void PushFront(T&& elem) {
        ListNode* node = new ListNodeValue<T>(std::move(elem), front_, nullptr);
        if (size_ == 0) {
            end_ = node;
            front_ = node;
        } else {
            front_->prev_ = node;
            front_ = node;
        }
        end_->next_ = pseudo_end_;
        pseudo_end_->prev_ = end_;
        ++size_;
    }

    T& Front() {
        return static_cast<ListNodeValue<T>*>(front_)->value_;
    }

    const T& Front() const {
        return static_cast<ListNodeValue<T>*>(front_)->value_;
    }

    T& Back() {
        return static_cast<ListNodeValue<T>*>(end_)->value_;
    }

    const T& Back() const {
        return static_cast<ListNodeValue<T>*>(end_)->value_;
    }

    void PopBack() {
        if (size_) {
            auto temp = end_->prev_;
            end_->next_ = nullptr;
            end_->prev_ = nullptr;
            delete end_;
            end_ = temp;
            pseudo_end_->prev_ = end_;
            if (end_) {
                end_->next_ = pseudo_end_;
            }
            --size_;
            if (IsEmpty()) {
                front_ = nullptr;
            }
        }
    }

    void PopFront() {
        if (size_) {
            if (size_ != 1) {
                auto temp = front_->next_;
                front_->next_ = nullptr;
                delete front_;
                front_ = temp;
                front_->prev_ = nullptr;
            } else {
                front_->next_ = nullptr;
                delete front_;
                front_ = nullptr;
                end_ = nullptr;
            }
            pseudo_end_->prev_ = end_;
            if (end_) {
                end_->next_ = pseudo_end_;
            }
            --size_;
        }
    }

    Iterator Begin() const {
        return Iterator(front_);
    }

    Iterator End() const {
        if (IsEmpty()) {
            return Iterator(end_);
        }
        return Iterator(pseudo_end_);
    }

    Iterator begin() const {  // NOLINT
        return Begin();
    }

    Iterator end() const {  // NOLINT
        return End();
    }

private:
    ListNode* front_;
    ListNode* end_;
    ListNode* pseudo_end_;
    std::size_t size_;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}