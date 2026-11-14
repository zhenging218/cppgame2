#ifndef COLOUR_HPP
#define COLOUR_HPP

namespace cppengine {
    struct Colour {
        static constexpr std::size_t value_count = 4;

        union {
            float values[value_count];
            struct {
                float r,g,b,a;
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

        [[nodiscard]] constexpr iterator begin() noexcept { return values; }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return values; }
        [[nodiscard]] constexpr iterator end() noexcept { return values + value_count; }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return values + value_count; }

        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] constexpr pointer data() noexcept { return values; }
        [[nodiscard]] constexpr const_pointer data() const noexcept { return values; }

        [[nodiscard]] static constexpr size_type size() noexcept { return value_count; }
        [[nodiscard]] static constexpr bool empty() noexcept { return false; }

        [[nodiscard]] constexpr reference operator[](size_type i) noexcept { return values[i]; }
        [[nodiscard]] constexpr const_reference operator[](size_type i) const noexcept { return values[i]; }

        [[nodiscard]] constexpr reference front() noexcept { return values[0]; }
        [[nodiscard]] constexpr const_reference front() const noexcept { return values[0]; }
        [[nodiscard]] constexpr reference back() noexcept { return values[value_count - 1]; }
        [[nodiscard]] constexpr const_reference back() const noexcept { return values[value_count - 1]; }

        constexpr inline Colour(const float r_, const float g_, const float b_, const float a_)
            : r(r_), g(g_), b(b_), a(a_) {}

        constexpr inline Colour() : Colour(0.f, 0.f, 0.f, 0.f) {}

        Colour &operator+=(Colour const &other);
        Colour &operator-=(Colour const &other);
        Colour &operator*=(const float v);
        Colour &operator/=(const float v);
    };

    Colour operator+(Colour const &lhs, Colour const &rhs);
    Colour operator-(Colour const &lhs, Colour const &rhs);
    Colour operator*(const float v, Colour const &rhs);

    bool operator==(Colour const &lhs, Colour const &rhs);
}

#endif