#pragma once

#include <ostream>
namespace cppengine {
    class Vector3;
    class Matrix4x4;

    class Quaternion {
    public:
        static constexpr inline std::size_t value_count = 4;
        union {
            float idx[value_count];
            struct {
                float i, j, k, w;
            };
        };

        static const Quaternion identity;

        constexpr inline Quaternion(float i_, float j_, float k_, float w_) : i(i_), j(j_), k(k_), w(w_) {}
        constexpr inline Quaternion() : i(0.f), j(0.f), k(0.f), w(1.f) {}

        explicit Quaternion(Vector3 const& eulerAngles);
        explicit Quaternion(Matrix4x4 const& rotation);

        Quaternion& operator*=(Quaternion const& other);

        float& operator[](int i);
        float const& operator[](int i) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator float const * () const { return idx; }
    };

    Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs);

    bool operator==(Quaternion const& lhs, Quaternion const& rhs);
    bool operator!=(Quaternion const& lhs, Quaternion const& rhs);

    float magnitude(Quaternion const& q);
    Quaternion normalise(Quaternion const& q);

    std::ostream& operator<<(std::ostream& os, Quaternion const& v);
}