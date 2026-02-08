#pragma once

#include <ostream>

namespace cppengine {
    class Vector2 {
    public:
        union {
            float idx[2];
            struct {
                float x, y;
            };
            struct {
                float u, v;
            };
        };

        constexpr inline Vector2(float x_, float y_) : x(x_), y(y_) {}
        constexpr inline Vector2() : x(0.f), y(0.f) {}

        Vector2& operator+=(Vector2 const& other);
        Vector2& operator-=(Vector2 const& other);

        Vector2& operator*=(float v);
        Vector2& operator/=(float v);

        float& operator[](int i);
        float const& operator[](int i) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator const float* () const { return idx; }
    };

    Vector2 operator+(Vector2 const& lhs, Vector2 const& rhs);
    Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs);
    Vector2 operator*(float v, Vector2 const& rhs);
    Vector2 operator*(Vector2 const& lhs, float v);
    Vector2 operator/(Vector2 const& lhs, float v);

    bool operator==(Vector2 const& lhs, Vector2 const& rhs);
    bool operator!=(Vector2 const& lhs, Vector2 const& rhs);

    float dot(Vector2 const& lhs, Vector2 const &rhs);
    float magnitude(Vector2 const& v);
    Vector2 normalise(Vector2 const& v);

    std::ostream& operator<<(std::ostream& os, Vector2 const& v);
}