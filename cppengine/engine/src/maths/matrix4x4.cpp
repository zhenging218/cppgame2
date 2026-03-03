#include "maths/matrix4x4.hpp"
#include "maths/vector4.hpp"
#include "maths/quaternion.hpp"
#include "maths/math_helper.hpp"

#include <limits>
#include <cstdlib>
#include <cstring>

namespace cppengine {
    using namespace MathHelper;

    namespace {
        static constexpr float epsilon = std::numeric_limits<float>::epsilon();
    }

    constexpr const Matrix4x4 Matrix4x4::identity{
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };

    Matrix4x4::Matrix4x4(Quaternion const &rotation) {
        float xx = rotation.i * rotation.i;
        float xy = rotation.i * rotation.j;
        float xz = rotation.i * rotation.k;
        float xw = rotation.i * rotation.w;

        float yy = rotation.j * rotation.j;
        float yz = rotation.j * rotation.k;
        float yw = rotation.j * rotation.w;

        float zz = rotation.k * rotation.k;
        float zw = rotation.k * rotation.w;

        m00 = 1 - 2 * (yy + zz);
        m01 = 2 * (xy + zw);
        m02 = 2 * (xz + yw);
        m03 = 0;

        m10 = 2 * (xy - zw);
        m11 = 1 - 2 * (xx + zz);
        m12 = 2 * (yz - xw);
        m13 = 0;

        m20 = 2 * (xz - yw);
        m21 = 2 * (yz + xw);
        m22 = 1 - 2 * (xx + yy);
        m23 = 0;

        m30 = 0;
        m31 = 0;
        m32 = 0;
        m33 = 1;
    }

    Matrix4x4 &Matrix4x4::operator+=(Matrix4x4 const &other) {
        m00 += other.m00;
        m01 += other.m01;
        m02 += other.m02;
        m03 += other.m03;

        m10 += other.m10;
        m11 += other.m11;
        m12 += other.m12;
        m13 += other.m13;

        m20 += other.m20;
        m21 += other.m21;
        m22 += other.m22;
        m23 += other.m23;

        m30 += other.m30;
        m31 += other.m31;
        m32 += other.m32;
        m33 += other.m33;

        return *this;
    }

    Matrix4x4 &Matrix4x4::operator-=(Matrix4x4 const &other) {
        m00 -= other.m00;
        m01 -= other.m01;
        m02 -= other.m02;
        m03 -= other.m03;

        m10 -= other.m10;
        m11 -= other.m11;
        m12 -= other.m12;
        m13 -= other.m13;

        m20 -= other.m20;
        m21 -= other.m21;
        m22 -= other.m22;
        m23 -= other.m23;

        m30 -= other.m30;
        m31 -= other.m31;
        m32 -= other.m32;
        m33 -= other.m33;

        return *this;
    }

    Matrix4x4 &Matrix4x4::operator*=(Matrix4x4 const &other) {
        float result[] = {
            m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
            m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
            m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
            m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,

            m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
            m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
            m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
            m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,

            m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
            m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
            m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
            m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,

            m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
            m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
            m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
            m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
        };

        std::memcpy(idx, result, sizeof(result));

        return *this;
    }

    Matrix4x4 &Matrix4x4::operator*=(float v) {
        m00 *= v;
        m01 *= v;
        m02 *= v;
        m03 *= v;

        m10 *= v;
        m11 *= v;
        m12 *= v;
        m13 *= v;

        m20 *= v;
        m21 *= v;
        m22 *= v;
        m23 *= v;

        m30 *= v;
        m31 *= v;
        m32 *= v;
        m33 *= v;

        return *this;
    }

    Matrix4x4 &Matrix4x4::operator/=(float v) {
        m00 /= v;
        m01 /= v;
        m02 /= v;
        m03 /= v;

        m10 /= v;
        m11 /= v;
        m12 /= v;
        m13 /= v;

        m20 /= v;
        m21 /= v;
        m22 /= v;
        m23 /= v;

        m30 /= v;
        m31 /= v;
        m32 /= v;
        m33 /= v;

        return *this;
    }

    float &Matrix4x4::operator()(int row, int col) {
        return idx[row * 4 + col];
    }

    float const &Matrix4x4::operator()(int row, int col) const {
        return idx[row * 4 + col];
    }

    Matrix4x4 operator+(Matrix4x4 const &lhs, Matrix4x4 const &rhs) {
        return Matrix4x4{ lhs } += rhs;
    }

    Matrix4x4 operator-(Matrix4x4 const &lhs, Matrix4x4 const &rhs) {
        return Matrix4x4{ lhs } -= rhs;
    }

    Matrix4x4 operator*(Matrix4x4 const &lhs, Matrix4x4 const &rhs) {
        return Matrix4x4{ lhs } *= rhs;
    }

    Matrix4x4 operator*(Matrix4x4 const &lhs, float v) {
        return Matrix4x4{ lhs } *= v;
    }

    Matrix4x4 operator*(float v, Matrix4x4 const &rhs) {
        return Matrix4x4{ rhs } *= v;
    }

    Matrix4x4 operator/(Matrix4x4 const &lhs, float v) {
        return Matrix4x4{ lhs } /= v;
    }

    Vector4 operator*(Matrix4x4 const &lhs, Vector4 const &rhs) {
        return Vector4 {
            lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z + lhs.m03 * rhs.w,
            lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z + lhs.m13 * rhs.w,
            lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z + lhs.m23 * rhs.w,
            lhs.m30 * rhs.x + lhs.m31 * rhs.y + lhs.m32 * rhs.z + lhs.m33 * rhs.w,
        };
    }

    bool operator==(Matrix4x4 const &lhs, Matrix4x4 const &rhs) {
        return &lhs == &rhs ||
        std::abs(rhs.m00 - lhs.m00) < epsilon &&
        std::abs(rhs.m01 - lhs.m01) < epsilon &&
        std::abs(rhs.m02 - lhs.m02) < epsilon &&
        std::abs(rhs.m03 - lhs.m03) < epsilon &&
        std::abs(rhs.m10 - lhs.m10) < epsilon &&
        std::abs(rhs.m11 - lhs.m11) < epsilon &&
        std::abs(rhs.m12 - lhs.m12) < epsilon &&
        std::abs(rhs.m13 - lhs.m13) < epsilon &&
        std::abs(rhs.m20 - lhs.m20) < epsilon &&
        std::abs(rhs.m21 - lhs.m21) < epsilon &&
        std::abs(rhs.m22 - lhs.m22) < epsilon &&
        std::abs(rhs.m23 - lhs.m23) < epsilon &&
        std::abs(rhs.m30 - lhs.m30) < epsilon &&
        std::abs(rhs.m31 - lhs.m31) < epsilon &&
        std::abs(rhs.m32 - lhs.m32) < epsilon &&
        std::abs(rhs.m33 - lhs.m33) < epsilon;
    }

    bool operator!=(Matrix4x4 const &lhs, Matrix4x4 const &rhs) {
        return !(lhs == rhs);
    }

    float determinant(Matrix4x4 const &m) {
        return determinant3D(m.m00, m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33)
             - determinant3D(m.m01, m.m10, m.m12, m.m13, m.m20, m.m22, m.m23, m.m30, m.m32, m.m33)
             + determinant3D(m.m02, m.m10, m.m11, m.m13, m.m20, m.m21, m.m23, m.m30, m.m31, m.m33)
             - determinant3D(m.m03, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22, m.m30, m.m31, m.m32);
    }

    Matrix4x4 transpose(Matrix4x4 const &m) {
        return Matrix4x4 {
            m.m00, m.m10, m.m20, m.m30,
            m.m01, m.m11, m.m21, m.m31,
            m.m02, m.m12, m.m22, m.m32,
            m.m03, m.m13, m.m23, m.m33
        };
    }

    Matrix4x4 inverse(Matrix4x4 const &m) {
        float det = determinant(m);
        float inv = 1.0f/ det;

        // Cofactor matrix (each entry is the signed 3x3 minor)
        Matrix4x4 cof;

        cof.m00 =  determinant3D(1.f, m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        cof.m01 = -determinant3D(1.f, m.m10, m.m12, m.m13, m.m20, m.m22, m.m23, m.m30, m.m32, m.m33);
        cof.m02 =  determinant3D(1.f, m.m10, m.m11, m.m13, m.m20, m.m21, m.m23, m.m30, m.m31, m.m33);
        cof.m03 = -determinant3D(1.f, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22, m.m30, m.m31, m.m32);

        cof.m10 = -determinant3D(1.f, m.m01, m.m02, m.m03, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
        cof.m11 =  determinant3D(1.f, m.m00, m.m02, m.m03, m.m20, m.m22, m.m23, m.m30, m.m32, m.m33);
        cof.m12 = -determinant3D(1.f, m.m00, m.m01, m.m03, m.m20, m.m21, m.m23, m.m30, m.m31, m.m33);
        cof.m13 =  determinant3D(1.f, m.m00, m.m01, m.m02, m.m20, m.m21, m.m22, m.m30, m.m31, m.m32);

        cof.m20 =  determinant3D(1.f, m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m31, m.m32, m.m33);
        cof.m21 = -determinant3D(1.f, m.m00, m.m02, m.m03, m.m10, m.m12, m.m13, m.m30, m.m32, m.m33);
        cof.m22 =  determinant3D(1.f, m.m00, m.m01, m.m03, m.m10, m.m11, m.m13, m.m30, m.m31, m.m33);
        cof.m23 = -determinant3D(1.f, m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m30, m.m31, m.m32);

        cof.m30 = -determinant3D(1.f, m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m21, m.m22, m.m23);
        cof.m31 =  determinant3D(1.f, m.m00, m.m02, m.m03, m.m10, m.m12, m.m13, m.m20, m.m22, m.m23);
        cof.m32 = -determinant3D(1.f, m.m00, m.m01, m.m03, m.m10, m.m11, m.m13, m.m20, m.m21, m.m23);
        cof.m33 =  determinant3D(1.f, m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22);

        return transpose(cof) * inv;
    }

    std::ostream &operator<<(std::ostream &os, Matrix4x4 const &m) {
        return os << m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << m.m03 << ", "
                  << m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << m.m13 << ", "
                  << m.m20 << ", " << m.m21 << ", " << m.m22 << ", " << m.m23 << ", "
                  << m.m30 << ", " << m.m31 << ", " << m.m32 << ", " << m.m33;
    }

    Matrix4x4 translate(Vector3 const &t) {
        return Matrix4x4{
            1.f, 0.f, 0.f, t.x,
            0.f, 1.f, 0.f, t.y,
            0.f, 0.f, 1.f, t.z,
            0.f, 0.f, 0.f, 1.f
        };
    }

    Matrix4x4 rotate(Quaternion const &q) {
        return Matrix4x4(q);
    }

    Matrix4x4 scale(Vector3 const &s) {
        return Matrix4x4{
            s.x, 0.f, 0.f, 0.f,
            0.f, s.y, 0.f, 0.f,
            0.f, 0.f, s.z, 0.f,
            0.f, 0.f, 0.f, 1.f
        };
    }
}