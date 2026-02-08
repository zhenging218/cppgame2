#pragma once

#include <ostream>

class Quaternion;

class Vector3 {
public:
    union {
        float idx[3];
        struct {
            float x, y, z;
        };
        struct {
            float u, v, w;
        };
    };

    constexpr inline Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    constexpr inline Vector3() : x(0.f), y(0.f), z(0.f) {}

    explicit Vector3(Quaternion const& rotation);

    Vector3& operator+=(Vector3 const& other);
    Vector3& operator-=(Vector3 const& other);
    
    Vector3& operator*=(float v);
    Vector3& operator/=(float v);

    float& operator[](int i);
    float const& operator[](int i) const;

    constexpr inline operator float* () { return idx; }
    constexpr inline operator const float* () const { return idx; }
};

Vector3 operator+(Vector3 const& lhs, Vector3 const& rhs);
Vector3 operator-(Vector3 const& lhs, Vector3 const& rhs);
Vector3 operator*(float v, Vector3 const& rhs);
Vector3 operator*(Vector3 const& lhs, float v);
Vector3 operator/(Vector3 const& lhs, float v);

bool operator==(Vector3 const& lhs, Vector3 const& rhs);
bool operator!=(Vector3 const& lhs, Vector3 const& rhs);

float dot(Vector3 const& lhs, Vector3 const& rhs);
float magnitude(Vector3 const& v);
Vector3 normalise(Vector3 const& v);
Vector3 cross(Vector3 const& lhs, Vector3 const& rhs);

std::ostream& operator<<(std::ostream& os, Vector3 const& v);
