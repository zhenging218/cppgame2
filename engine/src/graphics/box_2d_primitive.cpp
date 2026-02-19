#include "engine.hpp"

namespace cppengine {
    Box2DPrimitive::Box2DPrimitive(Box2D const &t) : box2D(t) {

    }

    Box2D const &Box2DPrimitive::getBox2D() const {
        return box2D;
    }
}
