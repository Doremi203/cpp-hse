#pragma once

#include <iostream>
#include <memory>

class Any {
private:
    struct HolderBase {
        virtual HolderBase* Clone() const = 0;

        virtual ~HolderBase() {
        }
    };

    template <class T>
    struct Holder : HolderBase {
    public:
        explicit Holder(T val) : value_(val) {
        }

        HolderBase* Clone() const final {
            return new Holder<T>(value_);
        }

        T value_;
    };

    HolderBase* held_;

public:
    Any();

    template <class T>
    explicit Any(const T& value) : held_(new Holder<T>(value)) {
    }

    template <class T>
    Any& operator=(const T& value) {
        delete held_;
        held_ = new Holder<T>(value);
        return *this;
    }

    Any(const Any& rhs);
    Any& operator=(Any rhs);
    ~Any();

    bool Empty() const;

    void Clear();
    void Swap(Any& rhs);

    template <class T>
    const T& GetValue() const {
        return dynamic_cast<Holder<T>&>(*held_).value_;
    }
};