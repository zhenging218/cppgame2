#include "engine.hpp"
#include "raylib_integration.hpp"
#include "../../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "graphics/triangle_primitive.hpp"

namespace cppengine {
    void RaylibDrawContext::renderTriangle(TrianglePrimitive const &triangle) {
        auto const * indices = triangle.getIndices();

        const std::size_t indexCount = triangle.getIndexCount();
        const std::size_t stride = triangle.getStride();

        ::Vector2 v[3];

        for (std::size_t i = 0; i < indexCount; ++i) {
            const std::size_t startVertex = indices[i] * stride;
            v[i] = ::Vector2{ triangle.getVertices()[startVertex + 0], triangle.getVertices()[startVertex + 1] };
        }

        DrawTriangle(v[0], v[1], v[2], ::Color(255, 0, 0, 255));
    }
}
