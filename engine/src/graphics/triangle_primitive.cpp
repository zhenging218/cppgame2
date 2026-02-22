#include "engine.hpp"

namespace cppengine {
    TrianglePrimitive::TrianglePrimitive(Triangle const &t) : triangle(t) {

    }

    ModelID TrianglePrimitive::getModelId() const {
        return ModelID::TRIANGLE;
    }

    Triangle const &TrianglePrimitive::getTriangle() const {
        return triangle;
    }

    Vector3 const *TrianglePrimitive::getVertices() const {
        return triangle.vertices;
    }

    std::size_t TrianglePrimitive::getVertexCount() const {
        return Triangle::vertex_count;
    }

    std::size_t const *TrianglePrimitive::getIndices() const {
        return triangle.getIndices();
    }

    std::size_t TrianglePrimitive::getIndexCount() const {
        return Triangle::index_count;
    }
}
