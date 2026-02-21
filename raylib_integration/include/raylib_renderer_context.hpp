#ifndef RAYLIB_GRAPHICS_CONTEXT_HPP
#define RAYLIB_GRAPHICS_CONTEXT_HPP

#include "graphics/enum_camera_mode.hpp"
#include "graphics/draw_context.hpp"
#include "graphics/renderer_context.hpp"

namespace cppengine {
    class RaylibRendererContext : public RendererContext {
    private:

        ObjectHandle<RaylibModelContext> modelContext;
        ObjectHandle<RaylibShaderContext> shaderContext;

    public:
        RaylibRendererContext();

        ObjectHandle<DrawContext> createDrawContext(Rectangle2D const &absoluteViewport, Matrix4x4 const &transform) override;

        ObjectHandle<ShaderContext> getShaderContext() const override;
        ObjectHandle<TextureContext> getTextureContext() const override;

        void beginDraw() override;
        void endDraw() override;

        ~RaylibRendererContext() override = default;
    };
}

#endif