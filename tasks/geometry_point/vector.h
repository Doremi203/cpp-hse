#pragma once

#include <cmath>

namespace geometry {
class Vector {
private:
    int64_t x_coord_;
    int64_t y_coord_;

public:
    Vector();

    Vector(int64_t x, int64_t y);

    int64_t GetX() const;

    int64_t GetY() const;

    Vector operator+(const Vector& other) const;

    Vector operator-(const Vector& other) const;

    Vector operator+() const;

    Vector operator-() const;

    Vector operator*(int64_t number) const;

    Vector operator/(int64_t number) const;

    Vector& operator+=(const Vector& other);

    Vector& operator-=(const Vector& other);

    Vector& operator*=(int64_t number);

    Vector& operator/=(int64_t number);

    bool operator==(const Vector& other) const;

    friend int64_t ScalarMult(const Vector& first, const Vector& second);

    friend int64_t VectorMult(const Vector& first, const Vector& second);

    friend double Length(const Vector& vector);
};
}  // namespace geometry
