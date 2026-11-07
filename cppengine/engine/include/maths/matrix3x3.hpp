#ifndef MATRIX3X3_HPP
#define MATRIX3X3_HPP

#include <ostream>

namespace cppengine {
    class Vector3;

    class Matrix3x3 {
        static constexpr inline std::size_t value_count = 9;
    public:
        union {
            float idx[value_count];
            struct {
                float m00, m01, m02,
                      m10, m11, m12,
                      m20, m21, m22;
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

        static const Matrix3x3 identity;

        constexpr inline Matrix3x3(float m00_, float m01_, float m02_, float m10_, float m11_, float m12_, float m20_, float m21_, float m22_) : idx{ m00_, m01_, m02_, m10_, m11_, m12_, m20_, m21_, m22_ } {}
        constexpr inline Matrix3x3() : idx{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,0.f } {}

        Matrix3x3& operator+=(Matrix3x3 const& other);
        Matrix3x3& operator-=(Matrix3x3 const& other);
        Matrix3x3& operator*=(Matrix3x3 const& other);
        Matrix3x3& operator*=(float v);
        Matrix3x3& operator/=(float v);

        float& operator()(int row, int col);
        float const& operator()(int row, int col) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator const float* () const { return idx; }
    };

    Matrix3x3 operator+(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator-(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator*(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    Matrix3x3 operator*(float v, Matrix3x3 const& rhs);
    Matrix3x3 operator*(Matrix3x3 const& lhs, float v);
    Matrix3x3 operator/(Matrix3x3 const& lhs, float v);

    Vector3 operator*(Matrix3x3 const& lhs, Vector3 const& rhs);

    bool operator==(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
    bool operator!=(Matrix3x3 const& lhs, Matrix3x3 const& rhs);

    float determinant(Matrix3x3 const& m);
    Matrix3x3 transpose(Matrix3x3 const& m);

}

#endif