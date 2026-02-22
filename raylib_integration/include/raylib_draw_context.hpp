#ifndef RAYLIB_DRAW_CONTEXT_2D_HPP
#define RAYLIB_DRAW_CONTEXT_2D_HPP
#include <functional>

#include "raylib.h"
#include "graphics/draw_context.hpp"
#include "maths/rectangle_2d.hpp"
#include "maths/transform.hpp"

namespace cppengine {

    class RaylibDrawContext : public DrawContext {
    private:
        std::vector<std::function<void()>> commands;
        Rectangle2D viewport;
        Matrix4x4 transform;
    public:
        RaylibDrawContext(Rectangle2D const &viewport_, Matrix4x4 const &transform_);
        void begin() override;
        void renderTriangle(Triangle const &triangle, Matrix4x4 const &triangleTransform) override;
        void renderBox2D(Box2D const &box2D, Matrix4x4 const &box2DTransform) override;

        void render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<std::string, Uniform> const &uniforms, std::unordered_map<std::string,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &meshTransform) override;

        void beginBatch(ObjectHandle<ShaderHandle> shader) override;
        void endBatch(ObjectHandle<ShaderHandle> shader) override;

        void flush() override;
        ~RaylibDrawContext() override = default;
    };
}

#endif