#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "reflection/type_descriptor.hpp"

namespace cppengine {
    class Quaternion;

    class Vector3 {

    public:
        static constexpr inline std::size_t value_count = 3;

        union {
            float idx[value_count];
            struct {
                float x, y, z;
            };
            struct {
                float u, v, w;
            };
        };

        // range specification
        using value_type = float;
        using size_type = decltype(value_count);
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = value_type *;
        using const_pointer = value_type const *;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr iterator begin() noexcept { return idx; }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return idx; }
        [[nodiscard]] constexpr iterator end() noexcept { return idx + value_count; }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return idx + value_count; }

        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] constexpr pointer data() noexcept { return idx; }
        [[nodiscard]] constexpr const_pointer data() const noexcept { return idx; }

        [[nodiscard]] static constexpr size_type size() noexcept { return value_count; }
        [[nodiscard]] static constexpr bool empty() noexcept { return false; }

        [[nodiscard]] constexpr reference operator[](size_type i) noexcept { return idx[i]; }
        [[nodiscard]] constexpr const_reference operator[](size_type i) const noexcept { return idx[i]; }

        [[nodiscard]] constexpr reference front() noexcept { return idx[0]; }
        [[nodiscard]] constexpr const_reference front() const noexcept { return idx[0]; }
        [[nodiscard]] constexpr reference back() noexcept { return idx[value_count - 1]; }
        [[nodiscard]] constexpr const_reference back() const noexcept { return idx[value_count - 1]; }

        constexpr inline Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
        constexpr inline Vector3() : x(0.f), y(0.f), z(0.f) {}

        explicit Vector3(Quaternion const& rotation);

        Vector3& operator+=(Vector3 const& other);
        Vector3& operator-=(Vector3 const& other);

        Vector3& operator*=(float v);
        Vector3& operator/=(float v);

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
}

#endif