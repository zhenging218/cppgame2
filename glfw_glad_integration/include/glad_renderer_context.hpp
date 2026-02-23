#ifndef GLAD_RENDERER_CONTEXT_HPP
#define GLAD_RENDERER_CONTEXT_HPP
#include "graphics/model_context.hpp"
#include "graphics/renderer_context.hpp"

namespace cppengine {
    class GladRendererContext : public RendererContext {
    private:

    public:
        void beginDraw() override;

        ObjectHandle<DrawContext>
        createDrawContext(const Rectangle2D &absoluteViewport, const Matrix4x4 &transform) override;

        ObjectHandle<TextureContext> getTextureContext() const override;

        ObjectHandle<ModelContext> getModelContext() const override;

        ObjectHandle<ShaderContext> getShaderContext() const override;

        void endDraw() override;

        ~GladRendererContext() override;
    };
}

#endif
