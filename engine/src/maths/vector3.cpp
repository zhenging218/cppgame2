#include "maths/vector3.hpp"
#include "maths/quaternion.hpp"
#include <cmath>
#include <limits>
#include <numbers>

namespace cppengine {
    namespace {
        constexpr float epsilon = std::numeric_limits<float>::epsilon();
        constexpr float pi = std::numbers::pi;
    }

    Vector3::Vector3(Quaternion const &rotation) {

        float sinr_cosp = 2 * (rotation.w * rotation.i + rotation.j * rotation.k);
        float cosr_cosp = 1 - 2 * (rotation.i * rotation.i + rotation.j * rotation.j);

        float sinp = 2 * (rotation.w * rotation.j - rotation.k * rotation.i);

        float siny_cosp = 2 * (w * z + x * y);
        float cosy_cosp = 1 - 2 * (y * y + z * z);

        // roll, pitch, yaw
        x = std::atan2(sinr_cosp, cosr_cosp);
        y = std::abs(sinp) >= 1.f ? std::copysignf(pi, sinp) : std::asin(sinp);
        z = std::atan2(siny_cosp, cosy_cosp);
    }

    Vector3& Vector3::operator+=(Vector3 const& other) {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    Vector3& Vector3::operator-=(Vector3 const& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    Vector3& Vector3::operator*=(float v) {
        x *= v;
        y *= v;
        z *= v;

        return *this;
    }

    Vector3& Vector3::operator/=(float v) {
        x /= v;
        y /= v;
        z /= v;

        return *this;
    }

    float& Vector3::operator[](int i) {
        return idx[i];
    }

    float const& Vector3::operator[](int i) const {
        return idx[i];
    }

    Vector3 operator+(Vector3 const& lhs, Vector3 const& rhs) {
        return Vector3{ lhs } += rhs;
    }

    Vector3 operator-(Vector3 const& lhs, Vector3 const& rhs) {
        return Vector3{ lhs } -= rhs;
    }

    Vector3 operator*(Vector3 const& lhs, float v) {
        return Vector3{ lhs } *= v;
    }

    Vector3 operator*(float v, Vector3 const& rhs) {
        return Vector3{ rhs } *= v;
    }

    Vector3 operator/(Vector3 const& lhs, float v) {
        return Vector3{ lhs } /= v;
    }

    bool operator==(Vector3 const& lhs, Vector3 const& rhs) {
        return &lhs == &rhs || std::abs(lhs.x - rhs.x) < epsilon && std::abs(lhs.y - rhs.y) < epsilon && std::abs(lhs.z - rhs.z) < epsilon;
    }

    bool operator!=(Vector3 const& lhs, Vector3 const& rhs) {
        return !(lhs == rhs);
    }

    float dot(Vector3 const& lhs, Vector3 const& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    float magnitude(Vector3 const& v) {
        return std::sqrt(dot(v, v));
    }

    Vector3 normalise(Vector3 const& v) {
        return Vector3{ v } /= magnitude(v);
    }

    Vector3 cross(Vector3 const& lhs, Vector3 const& rhs) {
        return Vector3{
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

    std::ostream& operator<<(std::ostream& os, Vector3 const& v) {
        return os << v.x << ", " << v.y << ", " << v.z;
    }
}