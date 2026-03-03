#ifndef GLAD_DRAW_CONTEXT_HPP
#define GLAD_DRAW_CCONTEXT_HPP
#include <functional>
#include <unordered_map>
#include <vector>

#include "graphics/draw_context.hpp"
#include "graphics/shader_handle.hpp"
#include "graphics/texture_handle.hpp"
#include "maths/rectangle_2d.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    struct Rectangle2D;

    class GladDrawContext : public DrawContext {
    private:
        Rectangle2D viewport;
        Matrix4x4 vpMatrix;
        std::vector<std::function<void()>> commands;

    public:
        GladDrawContext(Rectangle2D const &viewport_, Matrix4x4 const &vpMatrix_);
        GladDrawContext(GladDrawContext const &) = delete;
        GladDrawContext &operator=(GladDrawContext const &) = delete;

        void begin() override;

        void bindShader(ObjectHandle<ShaderHandle> shader) override;
        void unbindShader(ObjectHandle<ShaderHandle> shader) override;

        void bindModel(ObjectHandle<ModelHandle> model) override;
        void unbindModel(ObjectHandle<ModelHandle> model) override;

        void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) override;
        void renderBox2D(Box2D const &box2D, Matrix4x4 const &transform) override;

        void render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<std::string, Uniform> const &uniforms, std::unordered_map<std::string,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) override;

        void flush() override;

        ~GladDrawContext() override;
    };

    inline GladDrawContext::~GladDrawContext() = default;
}

#endif
