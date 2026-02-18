#ifndef COLOUR_HPP
#define COLOUR_HPP

namespace cppengine {
    struct Colour {
        union {
            int value;
            struct {
                char r,g,b,a;
            };
        };

        constexpr inline Colour() : value(0x000000FF) {}

        constexpr inline Colour(const char r_, const char g_, const char b_, const char a_)
            : r(r_), g(g_), b(b_), a(a_) {}

        Colour &operator+=(Colour const &other);
        Colour &operator-=(Colour const &other);
        Colour &operator*=(const float v);
        Colour &operator/=(const float v);
    };

    Colour operator+(Colour const &lhs, Colour const &rhs);
    Colour operator-(Colour const &lhs, Colour const &rhs);
    Colour operator*(const float v, Colour const &rhs);
}

#endif