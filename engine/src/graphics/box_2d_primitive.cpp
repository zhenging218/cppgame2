#include "engine.hpp"

namespace cppengine {
    Box2DPrimitive::Box2DPrimitive(Box2D const &t) : box2D(t) {

    }

    Box2D const &Box2DPrimitive::getBox2D() const {
        return box2D;
    }

    Vector3 const *Box2DPrimitive::getVertices() const {
        return box2D.vertices;
    }

    std::size_t Box2DPrimitive::getVertexCount() const {
        return Box2D::vertex_count;
    }

    std::size_t const *Box2DPrimitive::getIndices() const {
        return box2D.getIndices();
    }

    std::size_t Box2DPrimitive::getIndexCount() const {
        return Box2D::index_count;
    }
}
