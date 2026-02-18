#include "engine.hpp"

namespace cppengine {
    TrianglePrimitive::TrianglePrimitive(Triangle const &t) : triangle(t) {

    }

    Triangle const &TrianglePrimitive::getTriangle() const {
        return triangle;
    }
}
