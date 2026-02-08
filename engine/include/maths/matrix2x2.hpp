#pragma once

#include <ostream>

class Matrix2x2 {
public:
    union {
        float idx[4];
        struct {
            float m00, m01, 
                  m10, m11;
        };
    };

    static const Matrix2x2 identity;

    constexpr inline Matrix2x2(float m00_, float m01_, float m10_, float m11_) : m00(m00_), m01(m01_), m10(m10_), m11(m11_) {}
    constexpr inline Matrix2x2() : m00(0.f), m01(0.f), m10(0.f), m11(0.f) {}

    Matrix2x2& operator+=(Matrix2x2 const& other);
    Matrix2x2& operator-=(Matrix2x2 const& other);
    Matrix2x2& operator*=(Matrix2x2 const& other);
    Matrix2x2& operator*=(float v);
    Matrix2x2& operator/=(float v);

    float& operator()(int row, int col);
    float const& operator()(int row, int col) const;

    constexpr inline operator float* () { return idx; }
    constexpr inline operator const float* () const { return idx; }

};

Matrix2x2 operator+(Matrix2x2 const& lhs, Matrix2x2 const& rhs);
Matrix2x2 operator-(Matrix2x2 const& lhs, Matrix2x2 const& rhs);
Matrix2x2 operator*(Matrix2x2 const& lhs, Matrix2x2 const& rhs);
Matrix2x2 operator*(float v, Matrix2x2 const& rhs);
Matrix2x2 operator*(Matrix2x2 const& lhs, float v);
Matrix2x2 operator/(Matrix2x2 const& lhs, float v);

Vector2 operator*(Matrix2x2 const& lhs, Vector2 const& rhs);

bool operator==(Matrix2x2 const& lhs, Matrix2x2 const& rhs);
bool operator!=(Matrix2x2 const& lhs, Matrix2x2 const& rhs);

float determinant(Matrix2x2 const& m);
Matrix2x2 transpose(Matrix2x2 const& m);

std::ostream& operator<<(std::ostream& os, Matrix2x2 const& m);

