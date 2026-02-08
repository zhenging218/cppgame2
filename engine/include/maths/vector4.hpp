#pragma once

#include <ostream>

class Vector4 {
public:
    union {
        float idx[4];
        struct {
            float x, y, z, w;
        };
    };

    constexpr inline Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    constexpr inline Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

    Vector4& operator+=(Vector4 const& other);
    Vector4& operator-=(Vector4 const& other);
    Vector4& operator*=(float v);
    Vector4& operator/=(float v);

    float& operator[](int i);
    float const& operator[](int i) const;

    constexpr inline operator float* () { return idx; }
    constexpr inline operator const float* () const { return idx; }
};

Vector4 operator+(Vector4 const& lhs, Vector4 const& rhs);
Vector4 operator-(Vector4 const& lhs, Vector4 const& rhs);
Vector4 operator*(float v, Vector4 const& rhs);
Vector4 operator*(Vector4 const& lhs, float v);
Vector4 operator/(Vector4 const& lhs, float v);

bool operator==(Vector4 const& lhs, Vector4 const& rhs);
bool operator!=(Vector4 const& lhs, Vector4 const& rhs);

float dot(Vector4 const& lhs, Vector4 const& rhs);
float magnitude(Vector4 const& v);
Vector4 normalise(Vector4 const& v);

std::ostream& operator<<(std::ostream& os, Vector4 const& v);