#ifndef COLOUR_HPP
#define COLOUR_HPP

namespace cppengine {
    struct Colour {
        union {
            struct {
                float r,g,b,a;
            };
        };

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