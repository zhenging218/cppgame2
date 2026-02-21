#include <cstring>
#include <iostream>

#include "engine.hpp"
#include "raylib_integration.hpp"

#include "raylib.h"

namespace {
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
    RaylibDrawContext::RaylibDrawContext(Rectangle2D const &viewport_, Matrix4x4 const &transform_)
    : viewport(viewport_), transform(transform_) {

    }

    void RaylibDrawContext::renderTriangle(Triangle const &triangle, Matrix4x4 const &triangleTransform) {
        Matrix4x4 mvpMatrix = transform * triangleTransform;

        Vector4 vertices[Triangle::vertex_count] = {
            mvpMatrix * Vector4(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z, 1),
            mvpMatrix * Vector4(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z, 1),
            mvpMatrix * Vector4(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z, 1)
        };

        std::size_t indices[Triangle::index_count];
        std::memcpy(indices, Triangle::indices, Triangle::index_count * sizeof(std::size_t));

        commands.emplace_back([this, vertices, indices]() {
            auto ndcToScreen = [this](Vector4 const &v) -> ::Vector2 {
                float x = v.x / v.w;
                float y = v.y / v.w;
                return ::Vector2{
                    (x + 1.0f) * 0.5f * viewport.width,
                    (y + 1.0f) * 0.5f * viewport.height
                };
            };

            DrawTriangle(
                ndcToScreen(vertices[indices[0]]),
                ndcToScreen(vertices[indices[1]]),
                ndcToScreen(vertices[indices[2]]),
                ::RED
            );
        });
    }

    void RaylibDrawContext::renderBox2D(Box2D const &box2D, Matrix4x4 const &box2DTransform) {
        Matrix4x4 mvpMatrix = transform * box2DTransform;

        Vector4 vertices[Box2D::vertex_count] = {
            mvpMatrix * Vector4(box2D.vertices[0].x, box2D.vertices[0].y, box2D.vertices[0].z, 1),
            mvpMatrix * Vector4(box2D.vertices[1].x, box2D.vertices[1].y, box2D.vertices[1].z, 1),
            mvpMatrix * Vector4(box2D.vertices[2].x, box2D.vertices[2].y, box2D.vertices[2].z, 1),
            mvpMatrix * Vector4(box2D.vertices[3].x, box2D.vertices[3].y, box2D.vertices[3].z, 1)
        };

        std::size_t indices[Box2D::index_count];
        std::memcpy(indices, Box2D::indices, Box2D::index_count * sizeof(std::size_t));

        commands.emplace_back([this, vertices, indices]() {
            auto ndcToScreen = [this](Vector4 const &v) -> ::Vector2 {
                float x = v.x / v.w;
                float y = v.y / v.w;
                return ::Vector2{
                    (x + 1.0f) * 0.5f * viewport.width,
                    (y + 1.0f) * 0.5f * viewport.height
                };
            };

            DrawTriangle(
                ndcToScreen(vertices[indices[0]]),
                ndcToScreen(vertices[indices[1]]),
                ndcToScreen(vertices[indices[2]]),
                ::BLUE
            );
            DrawTriangle(
                ndcToScreen(vertices[indices[3]]),
                ndcToScreen(vertices[indices[4]]),
                ndcToScreen(vertices[indices[5]]),
                ::BLUE
            );
        });
    }

    void RaylibDrawContext::render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
        std::unordered_map<char const *, Uniform> const &uniforms, std::unordered_map<char const *,
        ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &meshTransform) {

        commands.emplace_back([this, shader, model, uniforms, textures, meshTransform] {
            std::ranges::for_each(uniforms, [shader](auto const &uniform) {
                    auto const &uniformName= uniform.first;
                    auto const &uniformValue = uniform.second;

                    std::visit(UniformSetters {
                        [uniformName, shader](std::int32_t v)     { shader->setUniform(uniformName, v); },
                        [uniformName, shader](std::uint32_t v)    { shader->setUniform(uniformName, v); },
                        [uniformName, shader](float v)            { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Colour const &v)    { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Vector2 const &v)   { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Vector3 const &v)   { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Vector4 const &v)   { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Matrix2x2 const &v) { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Matrix3x3 const &v) { shader->setUniform(uniformName, v); },
                        [uniformName, shader](Matrix4x4 const &v) { shader->setUniform(uniformName, v); },
                    }, uniformValue);
                });

            std::ranges::for_each(textures, [shader](auto const &texture) {
                shader->setUniform(texture.first, texture.second);
            });

            ::DrawMesh(static_handle_cast<RaylibModelHandle>(model)->getMesh(),
                static_handle_cast<RaylibShaderHandle>(shader)->getMaterial(),
                reinterpretMatrix(transform * meshTransform));
        });
    }

    void RaylibDrawContext::beginBatch(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader]() { shader->bindShader(); });
    }

    void RaylibDrawContext::endBatch(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader]() { shader->unbindShader(); });
    }

    void RaylibDrawContext::begin() {
        // get absolute viewport
        ::BeginScissorMode(
            static_cast<int>(viewport.x),
            static_cast<int>(viewport.y),
            static_cast<int>(viewport.width),
            static_cast<int>(viewport.height)
        );
    }

    void RaylibDrawContext::flush() {
        for (auto &command : commands) {
            command();
        }
        commands.clear();

        ::EndScissorMode();
    }
}
