#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"

namespace cppengine {
    RaylibDrawContext2D::RaylibDrawContext2D(::Camera2D const &camera_) : camera(camera_) {

    }

    void RaylibDrawContext2D::renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) {
        Vector4 i = transform * Vector4(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z, 1);
        Vector4 j = transform * Vector4(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z, 1);
        Vector4 k = transform * Vector4(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z, 1);

        commands.emplace_back([&i, &j, &k]() {
            DrawTriangle(
                ::Vector2{i.x / i.w, i.y / i.w},
                ::Vector2{j.x / j.w, j.y / j.w},
                ::Vector2{k.x / k.w, k.y / k.w},
                Color(255, 0, 0) // hardcode first, support colours later
            );
        });
    }

    void RaylibDrawContext2D::begin() {
        ::BeginMode2D(camera);
    }

    void RaylibDrawContext2D::flush() {

        for (auto const &command : commands) {
            command();
        }

        ::EndMode2D();
    }
}
