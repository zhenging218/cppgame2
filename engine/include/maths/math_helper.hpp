#pragma once

#include <type_traits>

namespace MathHelper {
    inline float determiant2D(const float &v, 
    const float &a, const float &b, 
    const float &c, const float &d);

    inline float determinant3D(const float &v, 
        const float& a, const float& b, const float &c,
        const float& d, const float& e, const float &f,
        const float &g, const float &h, const float &i);

    template <typename T, typename U, bool check = std::is_standard_layout<T>::value>
    struct StructToArrayConverter {
        static constexpr bool convertible = check;
    };

    template <typename T, typename U>
    struct StructToArrayConverter<T, U, true> {
        static constexpr bool convertible = true;

        static constexpr U* convert(T* t) noexcept {
            return reinterpret_cast<U*>(t);
        }

        static constexpr U const * convert(T const * t) noexcept {
            return reinterpret_cast<U const *>(t);
        }

        static constexpr U* convert(T& t) noexcept {
            return convert(&t);
        }

        static constexpr U const* convert(T const& t) noexcept {
            return convert(&t);
        }
    };
}