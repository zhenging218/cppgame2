#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include <ostream>

namespace cppengine {
    class Vector3;
    class Vector4;
    class Quaternion;

    class Matrix4x4 {
    public:
        static constexpr inline std::size_t value_count = 16;
        union {
            float idx[value_count];
            struct {
                float m00, m01, m02, m03,
                      m10, m11, m12, m13,
                      m20, m21, m22, m23,
                      m30, m31, m32, m33;
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

        static const Matrix4x4 identity;

        constexpr inline Matrix4x4(
            float m00_, float m01_, float m02_, float m03_,
            float m10_, float m11_, float m12_, float m13_,
            float m20_, float m21_, float m22_, float m23_,
            float m30_, float m31_, float m32_, float m33_
        ) : idx{
            m00_, m01_, m02_, m03_,
            m10_, m11_, m12_, m13_,
            m20_, m21_, m22_, m23_,
            m30_, m31_, m32_, m33_
        } {}

        constexpr inline Matrix4x4() : idx{
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        } {}

        explicit Matrix4x4(Quaternion const& rotation);

        Matrix4x4& operator+=(Matrix4x4 const& other);
        Matrix4x4& operator-=(Matrix4x4 const& other);
        Matrix4x4& operator*=(Matrix4x4 const& other);
        Matrix4x4& operator*=(float v);
        Matrix4x4& operator/=(float v);

        float& operator()(int row, int col);
        float const& operator()(int row, int col) const;

        constexpr inline operator float* () { return idx; }
        constexpr inline operator const float* () const { return idx; }
    };

    Matrix4x4 operator+(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator-(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    Matrix4x4 operator*(float v, Matrix4x4 const& rhs);
    Matrix4x4 operator*(Matrix4x4 const& lhs, float v);
    Matrix4x4 operator/(Matrix4x4 const& lhs, float v);

    Vector4 operator*(Matrix4x4 const& lhs, Vector4 const& rhs);

    bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
    bool operator!=(Matrix4x4 const& lhs, Matrix4x4 const& rhs);

    float determinant(Matrix4x4 const& m);
    Matrix4x4 transpose(Matrix4x4 const& m);
    Matrix4x4 inverse(Matrix4x4 const &m);

    Matrix4x4 translate(Vector3 const &t);
    Matrix4x4 rotate(Quaternion const &q);
    Matrix4x4 scale(Vector3 const &s);

}

#endif