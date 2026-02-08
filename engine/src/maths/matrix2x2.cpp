#include "maths/vector2.hpp"
#include "maths/matrix2x2.hpp"

#include <cstring>
#include <limits>

namespace {
    static constexpr float epsilon = std::numeric_limits<float>::epsilon();
}

constexpr const Matrix2x2 Matrix2x2::identity{ 1.f, 0.f, 0.f, 1.f };

Matrix2x2& Matrix2x2::operator+=(Matrix2x2 const& other) {
    m00 += other.m00;
    m01 += other.m01;
    m10 += other.m10;
    m11 += other.m11;

    return *this;
}

Matrix2x2& Matrix2x2::operator-=(Matrix2x2 const& other) {
    m00 -= other.m00;
    m01 -= other.m01;
    m10 -= other.m10;
    m11 -= other.m11;

    return *this;
}

Matrix2x2& Matrix2x2::operator*=(Matrix2x2 const& other) {
    float result[] = {
        m00 * other.m00 + m01 * other.m10,
        m00 * other.m01 + m01 * other.m11,
        m10 * other.m00 + m11 * other.m10,
        m10 * other.m01 + m11 * other.m11
    };

    std::memcpy(idx, result, sizeof(result));

    return *this;
}

Matrix2x2& Matrix2x2::operator*=(float v) {
    m00 *= v;
    m01 *= v;
    m10 *= v;
    m11 *= v;

    return *this;
}

Matrix2x2& Matrix2x2::operator/=(float v) {
    m00 /= v;
    m01 /= v;
    m10 /= v;
    m11 /= v;

    return *this;
}

float& Matrix2x2::operator()(int row, int col) {
    return idx[row * 2 + col];
}

float const& Matrix2x2::operator()(int row, int col) const {
    return idx[row * 2 + col];
}

Matrix2x2 operator+(Matrix2x2 const& lhs, Matrix2x2 const& rhs) {
    return Matrix2x2{ lhs } += rhs;
}

Matrix2x2 operator-(Matrix2x2 const& lhs, Matrix2x2 const& rhs) {
    return Matrix2x2{ lhs } -= rhs;
}

Matrix2x2 operator*(Matrix2x2 const& lhs, Matrix2x2 const& rhs) {
    return Matrix2x2{ lhs } *= rhs;
}

Matrix2x2 operator*(Matrix2x2 const& lhs, float v) {
    return Matrix2x2{ lhs } *= v;
}

Matrix2x2 operator*(float v, Matrix2x2 const& rhs) {
    return Matrix2x2{ rhs } *= v;
}

Matrix2x2 operator/(Matrix2x2 const& lhs, float v) {
    return Matrix2x2{ lhs } /= v;
}

Vector2 operator*(Matrix2x2 const& lhs, Vector2 const& rhs) {
    return Vector2{
        lhs.m00 * rhs.x + lhs.m01 * rhs.y,
        lhs.m10 * rhs.x + lhs.m11 * rhs.y
    };
}

bool operator==(Matrix2x2 const& lhs, Matrix2x2 const& rhs) {
    return &lhs == &rhs ||
        std::abs(rhs.m00 - lhs.m00) < epsilon && std::abs(rhs.m01 - lhs.m01) < epsilon &&
        std::abs(rhs.m10 - lhs.m10) < epsilon && std::abs(rhs.m11 - lhs.m11) < epsilon;
}

bool operator!=(Matrix2x2 const& lhs, Matrix2x2 const& rhs) {
    return !(lhs == rhs);
}

float determinant(Matrix2x2 const& m) {
    // ad - cb
    return m.m00 * m.m11 - m.m01 * m.m10;
}

Matrix2x2 transpose(Matrix2x2 const& m) {
    return Matrix2x2{
        m.m00, m.m10, m.m01, m.m11
    };
}

std::ostream& operator<<(std::ostream& os, Matrix2x2 const& m) {
    return os << m.m00 << ", " << m.m01 << ", " << m.m10 << ", " << m.m11;
}