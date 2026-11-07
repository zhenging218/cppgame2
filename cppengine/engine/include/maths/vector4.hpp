#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "reflection/type_descriptor.hpp"

namespace cppengine {
    class Vector4 {
    public:
        static constexpr inline std::size_t value_count = 4;
        union {
            float idx[value_count];
            struct {
                float x, y, z, w;
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

        constexpr inline Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
        constexpr inline Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

        Vector4& operator+=(Vector4 const& other);
        Vector4& operator-=(Vector4 const& other);
        Vector4& operator*=(float v);
        Vector4& operator/=(float v);

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
}

#endif