#pragma once

#include <ostream>

namespace cppengine {
    class Vector3;

    class Matrix3x3 {
        static constexpr inline std::size_t value_count = 9;
    public:
        union {
            float idx[value_count];
            struct {
                float m00, m01, m02,
                      m10, m11, m12,
                      m20, m21, m22;
            };
        };

        static const Matrix3x3 identity;

        constexpr inline Matrix3x3(float m00_, float m01_, float m02_, float m10_, float m11_, float m12_, float m20_, float m21_, float m22_) : idx{ m00_, m01_, m02_, m10_, m11_, m12_, m20_, m21_, m22_ } {}
        constexpr inline Matrix3x3() : idx{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,0.f } {}

        Matrix3x3& operator+=(Matrix3x3 const& other);
        Matrix3x3& operator-=(Matrix3x3 const& other);
        Matrix3x3& operator*=(Matrix3x3 const& other);
        Matrix3x3& operator*=(float v);
        Matrix3x3& operator/=(float v);

        float& operator()(int row, int col);
        float const& operator()(int row, int col) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator const float* () const { return idx; }
    };

    Matrix3x3 operator+(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator-(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator*(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator*(float v, Matrix3x3 const& rhs);
    Matrix3x3 operator*(Matrix3x3 const& lhs, float v);
    Matrix3x3 operator/(Matrix3x3 const& lhs, float v);

    Vector3 operator*(Matrix3x3 const& lhs, Vector3 const& rhs);

    bool operator==(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    bool operator!=(Matrix3x3 const& lhs, Matrix3x3 const& rhs);

    float determinant(Matrix3x3 const& m);
    Matrix3x3 transpose(Matrix3x3 const& m);

    std::ostream& operator<<(std::ostream& os, Matrix3x3 const& m);
}