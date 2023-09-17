#pragma once

#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
public:
    Rational();

    Rational(int value);  // NOLINT

    Rational(int numer, int denom);

    int GetNumerator() const;

    int GetDenominator() const;

    void SetNumerator(int value);

    void SetDenominator(int value);

    friend Rational& operator+=(Rational& lhs, const Rational& rhs);

    friend Rational& operator*=(Rational& lhs, const Rational& rhs);

    friend Rational& operator++(Rational& ratio);  // faster than += 1

    friend Rational& operator--(Rational& ratio);

    friend std::istream& operator>>(std::istream& is, Rational& ratio);

private:
    void Set(int64_t numer, int64_t denom);

    int numer_;
    int denom_;
};

Rational operator+(const Rational& ratio);

Rational operator-(const Rational& ratio);

Rational& operator-=(Rational& lhs, const Rational& rhs);

Rational& operator/=(Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);

Rational operator-(const Rational& lhs, const Rational& rhs);

Rational operator*(const Rational& lhs, const Rational& rhs);

Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator++(Rational& ratio, int);

Rational operator--(Rational& ratio, int);

bool operator<(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& ratio);