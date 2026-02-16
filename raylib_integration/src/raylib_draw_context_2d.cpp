#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"

namespace cppengine {
    void RaylibDrawContext2D::renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) {
        Vector4 i = transform * Vector4(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z, 1);
        Vector4 j = transform * Vector4(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z, 1);
        Vector4 k = transform * Vector4(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z, 1);

        // todo: apply camera matrix to ijk during flush
    }

    void RaylibDrawContext2D::flush() {

    }
}
