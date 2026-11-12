#ifndef QUATERNION_HPP
#define QUATERNION_HPP

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

        static const Quaternion identity;

        constexpr inline Quaternion(float i_, float j_, float k_, float w_) : i(i_), j(j_), k(k_), w(w_) {}
        constexpr inline Quaternion() : i(0.f), j(0.f), k(0.f), w(1.f) {}

        explicit Quaternion(Vector3 const& eulerAngles);
        explicit Quaternion(Matrix4x4 const& rotation);

        Quaternion& operator*=(Quaternion const& other);

        constexpr inline operator float* () { return idx; }
        constexpr inline operator float const * () const { return idx; }
    };

    Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs);

    bool operator==(Quaternion const& lhs, Quaternion const& rhs);
    bool operator!=(Quaternion const& lhs, Quaternion const& rhs);

    float magnitude(Quaternion const& q);
    Quaternion normalise(Quaternion const& q);
}

#endif