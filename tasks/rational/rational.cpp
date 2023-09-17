#include "rational.h"

Rational::Rational() {
    numer_ = 0;
    denom_ = 1;
}

Rational::Rational(int value) {
    numer_ = value;
    denom_ = 1;
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (!denom) {
        throw RationalDivisionByZero{};
    }
    auto gcd = std::gcd(numer, denom);
    numer_ = static_cast<int>(numer / gcd);
    denom_ = static_cast<int>(denom / gcd);
    if (denom < 0) {
        numer_ = -numer_;
        denom_ = -denom_;
    }
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_, lhs.denom_ * rhs.denom_);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.numer_, lhs.denom_ * rhs.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int num{};
    int den{1};
    is >> num;
    if (is.peek() == '/') {
        is.get();
        is >> den;
    }
    ratio.Set(num, den);
    return is;
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio);
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (!rhs.GetNumerator()) {
        throw RationalDivisionByZero{};
    }
    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    auto temp = lhs;
    return temp += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    auto temp = lhs;
    return temp -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    auto temp = lhs;
    return temp *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    auto temp = lhs;
    return temp /= rhs;
}

Rational operator++(Rational& ratio, int) {
    auto temp = ratio;
    ++ratio;
    return temp;
}

Rational operator--(Rational& ratio, int) {
    auto temp = ratio;
    --ratio;
    return temp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() > rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs <= rhs && lhs >= rhs;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs > rhs;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}
