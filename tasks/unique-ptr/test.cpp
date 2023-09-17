#include <catch.hpp>

// NOLINTBEGIN
struct Counters {
    Counters() {
        Reset();
    }

    void Reset() {
        ctor_ = intctor_ = dtor_ = copyctor_ = movector_ = copyoperator_ = moveoperator_ = method_ = 0;
    }

    void Check(int ctor, int intctor, int dtor, int copyctor, int movector, int copyoperator, int moveoperator,
               int method) {
        REQUIRE(ctor == ctor_);
        REQUIRE(intctor == intctor_);
        REQUIRE(dtor == dtor_);
        REQUIRE(copyctor == copyctor_);
        REQUIRE(movector == movector_);
        REQUIRE(copyoperator == copyoperator_);
        REQUIRE(moveoperator == moveoperator_);
        REQUIRE(method == method_);
    }

    int ctor_;
    int intctor_;
    int dtor_;
    int copyctor_;
    int movector_;
    int copyoperator_;
    int moveoperator_;
    int method_;
};

Counters counters;

class TestClass {
public:
    TestClass() {
        ++counters.ctor_;
    }
    explicit TestClass(int) {
        ++counters.intctor_;
    }
    TestClass(const TestClass&) {
        ++counters.copyctor_;
    }
    TestClass(TestClass&&) {
        ++counters.movector_;
    }
    ~TestClass() {
        ++counters.dtor_;
    }

    TestClass& operator=(const TestClass&) {
        ++counters.copyoperator_;
        return *this;
    }
    TestClass& operator=(TestClass&&) {
        ++counters.moveoperator_;
        return *this;
    }

    void Method() {
        ++counters.method_;
    }
};

#include "unique_ptr.h"

TEST_CASE("Empty", "[UniquePtr]") {
    counters.Reset();
    { UniquePtr<TestClass> ptr; }
    counters.Check(0, 0, 0, 0, 0, 0, 0, 0);
}

TEST_CASE("Simple", "[UniquePtr]") {
    counters.Reset();
    {
        UniquePtr<TestClass> ptr(new TestClass);
        counters.Check(1, 0, 0, 0, 0, 0, 0, 0);
        ptr.Reset();
        counters.Check(1, 0, 1, 0, 0, 0, 0, 0);
        ptr.Reset(new TestClass(1));
        counters.Check(1, 1, 1, 0, 0, 0, 0, 0);
        ptr.Reset(new TestClass(2));
        counters.Check(1, 2, 2, 0, 0, 0, 0, 0);
        ptr->Method();
        counters.Check(1, 2, 2, 0, 0, 0, 0, 1);
    }
    counters.Check(1, 2, 3, 0, 0, 0, 0, 1);
}

TEST_CASE("Move", "[UniquePtr]") {
    counters.Reset();
    {
        UniquePtr<TestClass> ptr(new TestClass);
        UniquePtr<TestClass> ptr2;
        counters.Check(1, 0, 0, 0, 0, 0, 0, 0);
        ptr2 = std::move(ptr);
        counters.Check(1, 0, 0, 0, 0, 0, 0, 0);
        ptr2 = std::move(ptr);
        counters.Check(1, 0, 1, 0, 0, 0, 0, 0);
        ptr.Reset();
        ptr2.Reset();
    }
    counters.Check(1, 0, 1, 0, 0, 0, 0, 0);
    counters.Reset();
    {
        UniquePtr<TestClass> ptr(new TestClass);
        UniquePtr<TestClass> ptr2(new TestClass(2));
        counters.Check(1, 1, 0, 0, 0, 0, 0, 0);
        ptr = std::move(ptr2);
        counters.Check(1, 1, 1, 0, 0, 0, 0, 0);
        UniquePtr<TestClass> ptr3(std::move(ptr));
        counters.Check(1, 1, 1, 0, 0, 0, 0, 0);
    }
    counters.Check(1, 1, 2, 0, 0, 0, 0, 0);
}
// NOLINTEND