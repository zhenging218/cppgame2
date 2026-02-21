#ifndef RAYLIB_DRAW_CONTEXT_2D_HPP
#define RAYLIB_DRAW_CONTEXT_2D_HPP
#include <functional>

#include "raylib.h"
#include "graphics/draw_context.hpp"
#include "maths/rectangle_2d.hpp"
#include "maths/transform.hpp"

namespace cppengine {

    class RaylibDrawContext2D : public DrawContext {
    private:
        std::vector<std::function<void()>> commands;
        Rectangle2D viewport;
        ::Camera2D camera;
    public:
        RaylibDrawContext2D(Rectangle2D const &viewport_, Transform const &transform);
        void begin() override;
        void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) override;
        void renderBox2D(Box2D const &box2D, Matrix4x4 const &transform) override;

        void render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<char const *, Uniform> const &uniforms, std::unordered_map<char const *,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) override;

        void beginBatch(ObjectHandle<ShaderHandle> shader) override;
        void endBatch(ObjectHandle<ShaderHandle> shader) override;

        void flush() override;
        ~RaylibDrawContext2D() override = default;
    };
}

#endif