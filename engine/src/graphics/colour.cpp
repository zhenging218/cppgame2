#include "engine.hpp"

namespace cppengine {
    Colour &Colour::operator+=(Colour const &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        a += other.a;

        return *this;
    }

    Colour &Colour::operator-=(Colour const &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        a -= other.a;

        return *this;
    }

    Colour &Colour::operator*=(const float v) {
        r *= v;
        g *= v;
        b *= v;
        a *= v;

        return *this;
    }

    Colour &Colour::operator/=(const float v) {
        r /= v;
        g /= v;
        b /= v;
        a /= v;

        return *this;
    }

    Colour operator+(Colour const &lhs, Colour const &rhs) {
        return Colour{lhs} += rhs;
    }

    Colour operator-(Colour const &lhs, Colour const &rhs) {
        return Colour{lhs} -= rhs;
    }

    Colour operator*(const float v, Colour const &rhs) {
        return Colour{rhs} *= v;
    }
}