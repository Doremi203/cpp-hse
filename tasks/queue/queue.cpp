#include "queue.h"

Node::Node(int32_t value, Node* next) {
    this->value = value;
    this->next = next;
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    if (size_ == 0) {
        front_ = new Node(value, nullptr);
        tail_ = front_;
    } else {
        tail_->next = new Node(value, nullptr);
        tail_ = tail_->next;
    }
    ++size_;
}

void Queue::Pop() {
    auto temp = front_;
    front_ = front_->next;
    delete temp;
    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (front_) {
        Pop();
    }
    size_ = 0;
}

bool Queue::Empty() const {
    return size_ == 0;
}