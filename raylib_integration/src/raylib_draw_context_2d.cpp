#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"

namespace {
    ::Camera2D createCamera(cppengine::Rectangle2D const &viewport, cppengine::Transform const &transform) {
        auto position = transform.getPosition();
        auto scale = transform.getScale();
        auto rotation = cppengine::Vector3(transform.getRotation());

        ::Camera2D camera;

        camera.target = {position.x, position.y};
        camera.offset = { viewport.width / 2.0f, viewport.height / 2.0f };
        camera.zoom = (scale.x + scale.y) / 2;
        camera.rotation = rotation.z * (180.0f / PI);

        return camera;
    }
}

namespace cppengine {
    RaylibDrawContext2D::RaylibDrawContext2D(Rectangle2D const &viewport_, Transform const &transform)
    : viewport(viewport_), camera(createCamera(viewport_, transform)) {

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
        // get absolute viewport
        ::BeginScissorMode(
            static_cast<int>(viewport.x),
            static_cast<int>(viewport.y),
            static_cast<int>(viewport.width),
            static_cast<int>(viewport.height)
        );

        ::BeginMode2D(camera);
    }

    void RaylibDrawContext2D::flush() {

        for (auto const &command : commands) {
            command();
        }

        ::EndMode2D();
        ::EndScissorMode();
    }
}
