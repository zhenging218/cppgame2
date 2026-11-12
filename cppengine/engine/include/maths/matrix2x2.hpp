#ifndef MATRIX2X2_HPP
#define MATRIX2X2_HPP

#include <ostream>

namespace cppengine {
    class Matrix2x2 {
        static constexpr inline std::size_t value_count = 4;
    public:
        union {
            float idx[value_count];
            struct {
                float m00, m01,
                      m10, m11;
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

}

#endif