#include "engine.hpp"

namespace {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
}

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

    bool operator==(Colour const &lhs, Colour const &rhs) {
        return &lhs == &rhs || std::abs(rhs.r - lhs.r) < epsilon && std::abs(rhs.g - lhs.g) < epsilon && std::abs(rhs.b - lhs.b) < epsilon && std::abs(rhs.a - lhs.a) < epsilon;
    }
}