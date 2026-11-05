#include "engine.hpp"

namespace {
    using namespace cppengine;

    ModelID loadPrimitive() {
        Triangle triangle;
        return Renderer::loadModel(
            "TRIANGLE",
            triangle.vertices,
            triangle.getVertexCount(),
            triangle.getIndices(),
            triangle.getIndexCount());
    }
}

namespace cppengine {
    TrianglePrimitive::TrianglePrimitive() {
        loadPrimitive();
    }

    std::string_view TrianglePrimitive::getModelName() const {
        return "TRIANGLE";
    }
}
