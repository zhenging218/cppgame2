#include "maths/vector2.hpp"
#include <cmath>
#include <limits>

namespace {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
}

Vector2& Vector2::operator+=(Vector2 const& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(Vector2 const& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
}

Vector2& Vector2::operator/=(float v) {
    x /= v;
    y /= v;
    return *this;
}

float& Vector2::operator[](int i) {
    return idx[i];
}

float const& Vector2::operator[](int i) const {
    return idx[i];
}

Vector2 operator+(Vector2 const& lhs, Vector2 const& rhs) {
    return Vector2{ lhs } += rhs;
}

Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs) {
    return Vector2{ lhs } -= rhs;
}

Vector2 operator*(float v, Vector2 const& rhs) {
    return Vector2{ rhs } *= v;
}

Vector2 operator*(Vector2 const& lhs, float v) {
    return Vector2{ lhs } *= v;
}

Vector2 operator/(Vector2 const& lhs, float v) {
    return Vector2{ lhs } /= v;
}

bool operator==(Vector2 const& lhs, Vector2 const& rhs) {
    return &lhs == &rhs || std::abs(rhs.x - lhs.x) < epsilon && std::abs(rhs.y - lhs.y) < epsilon;
}

bool operator!=(Vector2 const& lhs, Vector2 const& rhs) {
    return !(lhs == rhs);
}

float dot(Vector2 const& lhs, Vector2 const& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float magnitude(Vector2 const& v) {
    return std::sqrt(dot(v, v));
}

Vector2 normalise(Vector2 const& v) {
    return Vector2{ v } / magnitude(v);
}

std::ostream& operator<<(std::ostream& os, Vector2 const& v) {
    return os << v.x << ", " << v.y;
}