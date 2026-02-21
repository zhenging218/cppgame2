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

    template<typename... Setter>
    struct UniformSetters : Setter... {
        using Setter::operator()...;
    };

    ::Matrix reinterpretMatrix(cppengine::Matrix4x4 const &m) {
        return ::Matrix{
            m.m00, m.m10, m.m20, m.m30,
            m.m01, m.m11, m.m21, m.m31,
            m.m02, m.m12, m.m22, m.m32,
            m.m03, m.m13, m.m23, m.m33
        };
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

    void RaylibDrawContext2D::render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
        std::unordered_map<char const *, Uniform> const &uniforms, std::unordered_map<char const *,
        ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) {

        commands.emplace_back([shader, model, uniforms, textures, transform] {
            std::ranges::for_each(uniforms, [shader](auto const &uniform) {
                    auto const &uniformName= uniform.first;
                    auto const &uniformValue = uniform.second;

                    std::visit(UniformSetters{
                        [&](std::int32_t v)     { shader->setUniform(uniformName, v); },
                        [&](std::uint32_t v)    { shader->setUniform(uniformName, v); },
                        [&](float v)            { shader->setUniform(uniformName, v); },
                        [&](Colour const &v)    { shader->setUniform(uniformName, v); },
                        [&](Vector2 const &v)   { shader->setUniform(uniformName, v); },
                        [&](Vector3 const &v)   { shader->setUniform(uniformName, v); },
                        [&](Vector4 const &v)   { shader->setUniform(uniformName, v); },
                        [&](Matrix2x2 const &v) { shader->setUniform(uniformName, v); },
                        [&](Matrix3x3 const &v) { shader->setUniform(uniformName, v); },
                        [&](Matrix4x4 const &v) { shader->setUniform(uniformName, v); },
                    }, uniformValue);
                });

            std::ranges::for_each(textures, [shader](auto const &texture) {
                shader->setUniform(texture.first, texture.second);
            });

            ::DrawMesh(static_handle_cast<RaylibModelHandle>(model)->getMesh(),
                static_handle_cast<RaylibShaderHandle>(shader)->getMaterial(),
                reinterpretMatrix(transform));
        });
    }

    void RaylibDrawContext2D::beginBatch(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader]() { shader->bindShader(); });
    }

    void RaylibDrawContext2D::endBatch(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader]() { shader->unbindShader(); });
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
        ::EndMode2D();
        ::EndScissorMode();
    }
}
