#include "maths/quaternion.hpp"

#include <cmath>

#include "maths/matrix4x4.hpp"
#include "maths/vector3.hpp"

#include <cstdlib>
#include <cstring>
#include <limits>

namespace {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    float magnitudeImpl(float i, float j, float k, float w) {
        return std::sqrt(i * i + j * j + k * k + w * w);
    }
}

namespace cppengine {


    constexpr const Quaternion Quaternion::identity{};

    Quaternion::Quaternion(Vector3 const &eulerAngles) : Quaternion() {
        float cx = std::cos(eulerAngles.x * 0.5f);
        float sx = std::sin(eulerAngles.x * 0.5f);
        float cy = std::cos(eulerAngles.y * 0.5f);
        float sy = std::sin(eulerAngles.y * 0.5f);
        float cz = std::cos(eulerAngles.z * 0.5f);
        float sz = std::sin(eulerAngles.z * 0.5f);

        i = sx * cy * cz - cx * sy * sz;
        j = cx * sy * cz + sx * cy * sz;
        k = cx * cy * sz - sx * sy * cz;
        w = cx * cy * cz + sx * sy * sz;
    }

    Quaternion::Quaternion(Matrix4x4 const &rotation) : Quaternion() {
        float trace = rotation.m00 + rotation.m11 + rotation.m22;

        if(trace > 0.f) {
            float s = 0.5f / std::sqrt(trace + 1.f);
            w = 0.25f / s;
            i = (rotation.m21 - rotation.m12) * s;
            j = (rotation.m02 - rotation.m20) * s;
            k = (rotation.m10 - rotation.m01) * s;
        } else {
            if(rotation.m00 > rotation.m11 && rotation.m00 > rotation.m22) {
                float s = 2.f * std::sqrt(1.f + rotation.m00 - rotation.m11 - rotation.m22);
                w = (rotation.m21 - rotation.m12) / s;
                i = 0.25f * s;
                j = (rotation.m01 + rotation.m10) / s;
                k = (rotation.m02 + rotation.m20) / s;
            } else if(rotation.m11 > rotation.m22) {
                float s = 2.f * std::sqrt(1.f + rotation.m11 - rotation.m00 - rotation.m22);
                w = (rotation.m02 - rotation.m20) / s;
                i = (rotation.m01 + rotation.m10) / s;
                j = 0.25f * s;
                k = (rotation.m12 + rotation.m21) / s;
            } else {
                float s = 2.f * std::sqrt(1.f + rotation.m22 - rotation.m00 - rotation.m11);
                w = (rotation.m10 - rotation.m01) / s;
                i = (rotation.m02 + rotation.m20) / s;
                j = (rotation.m12 + rotation.m21) / s;
                k = 0.25f * s;
            }
        }

        float m = magnitudeImpl(i, j, k, w);
        i = i/m;
        j = j/m;
        k = k/m;
        w = w/m;
    }

    float &Quaternion::operator[](int i) {
        return idx[i];
    }

    float const &Quaternion::operator[](int i) const {
        return idx[i];
    }

    Quaternion &Quaternion::operator*=(Quaternion const &other) {
        float result[] = {
            w * other.i + i * other.w + j * other.k - k * other.j,
            w * other.j + j * other.w + k * other.i - i * other.k,
            w * other.k + k * other.w + i * other.j - j * other.i,
            w * other.w - i * other.i - j * other.j - k * other.k
        };

        std::memcpy(idx, result, sizeof(result));

        return *this;
    }

    Quaternion operator*(Quaternion const &lhs, Quaternion const &rhs) {
        return Quaternion{ lhs } *= rhs;
    }

    bool operator==(Quaternion const& lhs, Quaternion const& rhs) {
        return &lhs == &rhs || std::abs(rhs.i - lhs.i) < epsilon && std::abs(rhs.j - lhs.j) < epsilon && std::abs(rhs.k - lhs.k) < epsilon && std::abs(rhs.w - lhs.w) < epsilon;
    }

    bool operator!=(Quaternion const& lhs, Quaternion const& rhs) {
        return !(lhs == rhs);
    }

    float magnitude(Quaternion const &q) {
        return magnitudeImpl(q.i, q.j, q.k, q.w);
    }

    Quaternion normalise(Quaternion const &q) {
        float m = magnitudeImpl(q.i, q.j, q.k, q.w);

        return {q.i / m, q.j / m, q.k / m, q.w / m };
    }

    std::ostream &operator<<(std::ostream &os, Quaternion const &q) {
        return os << q.i << ", " << q.j << ", " << q.k << ", " << q.w;
    }
}