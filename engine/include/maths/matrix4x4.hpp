#pragma once

#include <ostream>

namespace cppengine {
    class Vector4;
    class Quaternion;

    class Matrix4x4 {
    public:
        static constexpr inline std::size_t value_count = 16;
        union {
            float idx[value_count];
            struct {
                float m00, m01, m02, m03,
                      m10, m11, m12, m13,
                      m20, m21, m22, m23,
                      m30, m31, m32, m33;
            };
        };

        static const Matrix4x4 identity;

        constexpr inline Matrix4x4(
            float m00_, float m01_, float m02_, float m03_,
            float m10_, float m11_, float m12_, float m13_,
            float m20_, float m21_, float m22_, float m23_,
            float m30_, float m31_, float m32_, float m33_
        ) : idx{
            m00_, m01_, m02_, m03_,
            m10_, m11_, m12_, m13_,
            m20_, m21_, m22_, m23_,
            m30_, m31_, m32_, m33_
        } {}

        constexpr inline Matrix4x4() : idx{
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        } {}

        explicit Matrix4x4(Quaternion const& rotation);

        Matrix4x4& operator+=(Matrix4x4 const& other);
        Matrix4x4& operator-=(Matrix4x4 const& other);
        Matrix4x4& operator*=(Matrix4x4 const& other);
        Matrix4x4& operator*=(float v);
        Matrix4x4& operator/=(float v);

        float& operator()(int row, int col);
        float const& operator()(int row, int col) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator const float* () const { return idx; }
    };

    Matrix4x4 operator+(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator-(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator*(float v, Matrix4x4 const& rhs);
    Matrix4x4 operator*(Matrix4x4 const& lhs, float v);
    Matrix4x4 operator/(Matrix4x4 const& lhs, float v);

    Vector4 operator*(Matrix4x4 const& lhs, Vector4 const& rhs);

    bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    bool operator!=(Matrix4x4 const& lhs, Matrix4x4 const& rhs);

    float determinant(Matrix4x4 const& m);
    Matrix4x4 transpose(Matrix4x4 const& m);

    std::ostream& operator<<(std::ostream& os, Matrix4x4 const& m);
}