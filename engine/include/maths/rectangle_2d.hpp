#ifndef RECTANGLE_2D_HPP
#define RECTANGLE_2D_HPP

namespace cppengine {
    struct Rectangle2D {
        float x, y, width, height;

        constexpr Rectangle2D() = default;
        constexpr Rectangle2D(const float x_, const float y_, const float width_, const float height_)
            : x(x_), y(y_), width(width_), height(height_) {}

        friend bool operator==(Rectangle2D const &lhs, Rectangle2D const &rhs);
        friend std::ostream &operator<<(std::ostream os, Rectangle2D const &r2d);
    };
}

#endif