#include <catch.hpp>

#include <smart_ptr.h>

#include <string>

using std::string;

TEST_CASE("Empty shared") {
    SharedPtr<std::string> a;
    SharedPtr<std::string> b;
    b = a;
    SharedPtr<std::string> c(a);
    b = std::move(c);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("Reset shared") {
    string* ptr1 = new string("aba");
    string* ptr2 = new string("caba");
    SharedPtr<std::string> a(ptr1);
    SharedPtr<std::string> b(ptr2);
    REQUIRE(a.Get() == ptr1);
    REQUIRE(*b == *ptr2);
    a.Reset(nullptr);
    b = a;
}

TEST_CASE("Copy/move shared") {
    SharedPtr<std::string> a(new string("aba"));
    string* ptr;
    {
        SharedPtr<std::string> b(a);
        SharedPtr<std::string> c(a);
        ptr = c.Get();
    }
    REQUIRE(ptr == a.Get());
    REQUIRE(*ptr == "aba");

    SharedPtr<std::string> b(new string("caba"));
    {
        SharedPtr<std::string> c(b);
        SharedPtr<std::string> d(b);
        d = std::move(a);
        REQUIRE(*c == "caba");
        REQUIRE(*d == "aba");
        b.Reset(new string("test"));
        REQUIRE(*c == "caba");
    }
    REQUIRE(*b == "test");

    SharedPtr<std::string> end;
    {
        SharedPtr<std::string> d(new string("delete"));
        d = b;
        SharedPtr<std::string> c(std::move(b));
        REQUIRE(*d == "test");
        REQUIRE(*c == "test");
        c = end;
        d.Reset(new string("delete"));
        end = d;
    }

    REQUIRE(*end == "delete");
}

TEST_CASE("Empty weak") {
    WeakPtr<std::string> a;
    WeakPtr<std::string> b;
    a = b;
    WeakPtr<std::string> c(a);
    b = std::move(c);

    auto shared = b.Lock();
    REQUIRE(shared.Get() == nullptr);
}

TEST_CASE("Weak expiration") {
    WeakPtr<std::string>* a;
    {
        SharedPtr<std::string> b(new string("aba"));
        SharedPtr<std::string> c(b);
        a = new WeakPtr<std::string>(c);
        auto test = a->Lock();
        REQUIRE(*test == "aba");
        REQUIRE(!a->IsExpired());
    }
    REQUIRE(a->IsExpired());
    delete a;
}

TEST_CASE("Weak extends shared") {
    SharedPtr<std::string>* b = new SharedPtr<std::string>(new string("aba"));
    WeakPtr<std::string> c(*b);
    auto a = c.Lock();
    delete b;
    REQUIRE(!c.IsExpired());
    REQUIRE(*a == "aba");
}

TEST_CASE("Copy/move weak") {
    SharedPtr<std::string> a(new string("aba"));
    WeakPtr<std::string> b(a);
    WeakPtr<std::string> empty;
    WeakPtr<std::string> c(b);
    WeakPtr<std::string> d(a);
    REQUIRE(!c.IsExpired());
    c = empty;
    REQUIRE(c.IsExpired());

    b = std::move(c);
    auto locked = d.Lock();
    REQUIRE(*locked == "aba");

    WeakPtr<std::string> start(a);
    {
        SharedPtr<std::string> a2(a);
        WeakPtr<std::string> f(a2);
        auto cur_lock = f.Lock();
        REQUIRE(cur_lock.Get() == SharedPtr<std::string>(start).Get());
    }
}

TEST_CASE("Shared from weak") {
    SharedPtr<std::string>* x = new SharedPtr<std::string>(new string("aba"));
    WeakPtr<std::string> y(*x);
    delete x;
    REQUIRE(y.IsExpired());
    SharedPtr<std::string> z(y);
    REQUIRE(z.Get() == nullptr);
}
