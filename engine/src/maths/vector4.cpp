#include "maths/vector4.hpp"
#include <cmath>
#include <limits>

namespace {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
}

Vector4& Vector4::operator+=(Vector4 const& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4& Vector4::operator-=(Vector4 const& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4& Vector4::operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;

    return *this;
}

Vector4& Vector4::operator/=(float v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;

    return *this;
}

float& Vector4::operator[](int i) {
    return idx[i];
}

float const& Vector4::operator[](int i) const {
    return idx[i];
}

Vector4 operator+(Vector4 const& lhs, Vector4 const& rhs) {
    return Vector4{ lhs } += rhs;
}

Vector4 operator-(Vector4 const& lhs, Vector4 const& rhs) {
    return Vector4{ lhs } -= rhs;
}

Vector4 operator*(Vector4 const& lhs, float v) {
    return Vector4{ lhs } *= v;
}

Vector4 operator*(float v, Vector4 const& rhs) {
    return Vector4{ rhs } *= v;
}

Vector4 operator/(Vector4 const& lhs, float v) {
    return Vector4{ lhs } /= v;
}

bool operator==(Vector4 const& lhs, Vector4 const& rhs) {
    return &lhs == &rhs || std::abs(rhs.x - lhs.x) < epsilon && std::abs(rhs.y - lhs.y) < epsilon && std::abs(rhs.z - lhs.z) < epsilon && std::abs(rhs.w - lhs.w) < epsilon;
}

bool operator!=(Vector4 const& lhs, Vector4 const& rhs) {
    return !(lhs == rhs);
}

float dot(Vector4 const& lhs, Vector4 const& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

float magnitude(Vector4 const& v) {
    return std::sqrt(dot(v, v));
}

Vector4 normalise(Vector4 const& v) {
    return Vector4{ v } /= magnitude(v);
}

std::ostream& operator<<(std::ostream& os, Vector4 const& v) {
    return os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
}