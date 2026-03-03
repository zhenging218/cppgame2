#include "engine.hpp"

namespace {
    using namespace cppengine;

    ModelID loadPrimitive() {
        Box2D box2D;
        return Renderer::loadModel(
            "BOX2D",
            box2D.vertices,
            box2D.getVertexCount(),
            box2D.getIndices(),
            box2D.getIndexCount());
    }
}

namespace cppengine {
    Box2DPrimitive::Box2DPrimitive() : id(loadPrimitive()) {

    }

    ModelID Box2DPrimitive::getModelId() const {
        return id;
    }
}
