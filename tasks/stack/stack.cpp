#include "stack.h"

Node::Node(int32_t value, Node* previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    head_ = nullptr;
    size_ = 0;
}

Stack::~Stack() {
    Clear();
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    ++size_;
}

void Stack::Pop() {
    auto temp = head_->previous;
    delete head_;
    head_ = temp;
    --size_;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (head_) {
        Pop();
    }
}

bool Stack::Empty() const {
    return size_ == 0;
}
