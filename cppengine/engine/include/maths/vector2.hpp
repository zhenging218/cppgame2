#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "reflection/type_descriptor.hpp"

#include <ostream>

namespace cppengine {
    class Vector2 {
    public:
        static constexpr inline std::size_t value_count = 2;
        union {
            float idx[value_count];
            struct {
                float x, y;
            };
            struct {
                float u, v;
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

        constexpr inline Vector2(float x_, float y_) : x(x_), y(y_) {}
        constexpr inline Vector2() : x(0.f), y(0.f) {}

        Vector2& operator+=(Vector2 const& other);
        Vector2& operator-=(Vector2 const& other);

        Vector2& operator*=(float v);
        Vector2& operator/=(float v);

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
}

#endif