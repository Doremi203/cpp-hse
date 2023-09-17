#include "any.h"

#include <utility>

Any::Any() : held_() {
}

Any::Any(const Any& rhs) : held_(rhs.held_->Clone()) {
}

Any& Any::operator=(Any rhs) {
    delete held_;
    held_ = rhs.held_->Clone();
    return *this;
}

Any::~Any() {
    Clear();
}

bool Any::Empty() const {
    return held_ == nullptr;
}

void Any::Clear() {
    delete held_;
    held_ = nullptr;
}

void Any::Swap(Any& rhs) {
    std::swap(rhs.held_, held_);
}
