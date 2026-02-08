#include "maths/matrix3x3.hpp"
#include "maths/vector3.hpp"
#include "maths/math_helper.hpp"

#include <limits>
#include <cstdlib>
#include <cstring>

namespace cppengine {
    namespace {
        static constexpr float epsilon = std::numeric_limits<float>::epsilon();
    }

    using namespace MathHelper;

    constexpr Matrix3x3 const Matrix3x3::identity{ 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f };

    Matrix3x3 &Matrix3x3::operator+=(Matrix3x3 const &other) {
        m00 += other.m00;
        m01 += other.m01;
        m02 += other.m02;
        m10 += other.m10;
        m11 += other.m11;
        m12 += other.m12;
        m20 += other.m20;
        m21 += other.m21;
        m22 += other.m22;

        return *this;
    }

    Matrix3x3 &Matrix3x3::operator-=(Matrix3x3 const &other) {
        m00 -= other.m00;
        m01 -= other.m01;
        m02 -= other.m02;
        m10 -= other.m10;
        m11 -= other.m11;
        m12 -= other.m12;
        m20 -= other.m20;
        m21 -= other.m21;
        m22 -= other.m22;

        return *this;
    }

    Matrix3x3 &Matrix3x3::operator*=(Matrix3x3 const &other) {
        float result[] = {
            m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
            m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
            m00 * other.m02 + m01 * other.m12 + m02 * other.m22,

            m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
            m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
            m10 * other.m02 + m11 * other.m12 + m12 * other.m22,

            m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
            m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
            m20 * other.m02 + m21 * other.m12 + m22 * other.m22
        };

        std::memcpy(idx, result, sizeof(result));

        return *this;
    }

    Matrix3x3 &Matrix3x3::operator*=(float v) {
        m00 *= v;
        m01 *= v;
        m02 *= v;
        m10 *= v;
        m11 *= v;
        m12 *= v;
        m20 *= v;
        m21 *= v;
        m22 *= v;

        return *this;
    }

    Matrix3x3 &Matrix3x3::operator/=(float v) {
        m00 /= v;
        m01 /= v;
        m02 /= v;
        m10 /= v;
        m11 /= v;
        m12 /= v;
        m20 /= v;
        m21 /= v;
        m22 /= v;

        return *this;
    }

    float &Matrix3x3::operator()(int row, int col) {
        return idx[row * 3 + col];
    }

    float const &Matrix3x3::operator()(int row, int col) const {
        return idx[row * 3 + col];
    }

    Matrix3x3 operator+(Matrix3x3 const &lhs, Matrix3x3 const &rhs) {
        return Matrix3x3{ lhs } += rhs;
    }

    Matrix3x3 operator-(Matrix3x3 const &lhs, Matrix3x3 const &rhs) {
        return Matrix3x3{ lhs } -= rhs;
    }

    Matrix3x3 operator*(Matrix3x3 const &lhs, Matrix3x3 const &rhs) {
        return Matrix3x3{ lhs } *= rhs;
    }

    Matrix3x3 operator*(Matrix3x3 const &lhs, float v) {
        return Matrix3x3{ lhs } *= v;
    }

    Matrix3x3 operator*(float v, Matrix3x3 const &rhs) {
        return Matrix3x3{ rhs } *= v;
    }

    Matrix3x3 operator/(Matrix3x3 const &lhs, float v) {
        return Matrix3x3{ lhs } /= v;
    }

    Vector3 operator*(Matrix3x3 const &lhs, Vector3 const &rhs) {
        return Vector3{
            lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z,
            lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z,
            lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z
        };
    }

    bool operator==(Matrix3x3 const& lhs, Matrix3x3 const& rhs) {
        return &lhs == &rhs ||
        std::abs(rhs.m00 - lhs.m00) < epsilon &&
        std::abs(rhs.m01 - lhs.m01) < epsilon &&
        std::abs(rhs.m02 - lhs.m02) < epsilon &&
        std::abs(rhs.m10 - lhs.m10) < epsilon &&
        std::abs(rhs.m11 - lhs.m11) < epsilon &&
        std::abs(rhs.m12 - lhs.m12) < epsilon &&
        std::abs(rhs.m20 - lhs.m20) < epsilon &&
        std::abs(rhs.m21 - lhs.m21) < epsilon &&
        std::abs(rhs.m22 - lhs.m22) < epsilon;
    }

    bool operator!=(Matrix3x3 const &lhs, Matrix3x3 const &rhs) {
        return !(lhs == rhs);
    }

    float determinant(Matrix3x3 const &m) {
        return MathHelper::determiant2D(m.m00, m.m11, m.m12, m.m21, m.m22)
        - MathHelper::determiant2D(m.m01, m.m10, m.m12, m.m20, m.m22)
        + MathHelper::determiant2D(m.m02, m.m10, m.m11, m.m20, m.m21);
    }

    Matrix3x3 transpose(Matrix3x3 const &m) {
        return Matrix3x3 {
            m.m00, m.m10, m.m20,
            m.m01, m.m11, m.m21,
            m.m12, m.m12, m.m22
        };
    }

    std::ostream &operator<<(std::ostream &os, Matrix3x3 const &m) {
        return os << m.m00 << ", " << m.m01 << ", " << m.m02 << ", "
                  << m.m10 << ", " << m.m11 << ", " << m.m12 << ", "
                  << m.m20 << ", " << m.m21 << ", " << m.m22 << ", ";
    }
}