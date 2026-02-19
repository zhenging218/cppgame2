#include <cstring>
#include <iostream>

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
        Vector4 vertices[Triangle::vertex_count] = {
            transform * Vector4(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z, 1),
            transform * Vector4(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z, 1),
            transform * Vector4(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z, 1)
        };

        std::size_t indices[Triangle::index_count];
        std::memcpy(indices, Triangle::indices, Triangle::index_count * sizeof(std::size_t));

        commands.emplace_back([vertices, indices]() {
            DrawTriangle(
                ::Vector2{vertices[indices[0]].x / vertices[indices[0]].w, vertices[indices[0]].y / vertices[indices[0]].w},
                ::Vector2{vertices[indices[1]].x / vertices[indices[1]].w, vertices[indices[1]].y / vertices[indices[1]].w},
                ::Vector2{vertices[indices[2]].x / vertices[indices[2]].w, vertices[indices[2]].y / vertices[indices[2]].w},
                ::RED // hardcode first, support colours later
            );
        });
    }

    void RaylibDrawContext2D::renderBox2D(Box2D const &box2D, Matrix4x4 const &transform) {
        Vector4 vertices[Box2D::vertex_count] = {
            transform * Vector4(box2D.vertices[0].x, box2D.vertices[0].y, box2D.vertices[0].z, 1),
            transform * Vector4(box2D.vertices[1].x, box2D.vertices[1].y, box2D.vertices[1].z, 1),
            transform * Vector4(box2D.vertices[2].x, box2D.vertices[2].y, box2D.vertices[2].z, 1),
            transform * Vector4(box2D.vertices[3].x, box2D.vertices[3].y, box2D.vertices[3].z, 1)
        };

        std::size_t indices[Box2D::index_count];
        std::memcpy(indices, Box2D::indices, Box2D::index_count * sizeof(std::size_t));

        commands.emplace_back([vertices, indices]() {
            DrawTriangle(
                ::Vector2{vertices[indices[0]].x / vertices[indices[0]].w, vertices[indices[0]].y / vertices[indices[0]].w},
                ::Vector2{vertices[indices[1]].x / vertices[indices[1]].w, vertices[indices[1]].y / vertices[indices[1]].w},
                ::Vector2{vertices[indices[2]].x / vertices[indices[2]].w, vertices[indices[2]].y / vertices[indices[2]].w},
                ::BLUE // hardcode first, support colours later
            );
            DrawTriangle(
            ::Vector2{vertices[indices[3]].x / vertices[indices[3]].w, vertices[indices[3]].y / vertices[indices[3]].w},
            ::Vector2{vertices[indices[4]].x / vertices[indices[4]].w, vertices[indices[4]].y / vertices[indices[4]].w},
            ::Vector2{vertices[indices[5]].x / vertices[indices[5]].w, vertices[indices[5]].y / vertices[indices[5]].w},
                ::BLUE // hardcode first, support colours later
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
        int i = 0;
        for (auto const &command : commands) {
            command();
        }
        commands.clear();

        ::EndMode2D();
        ::EndScissorMode();
    }
}
