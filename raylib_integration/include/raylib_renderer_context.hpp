#ifndef RAYLIB_GRAPHICS_CONTEXT_HPP
#define RAYLIB_GRAPHICS_CONTEXT_HPP

#include "integration/renderer_context.hpp"

namespace cppengine {
    class RaylibRendererContext : public RendererContext {
    private:

    public:
        ObjectHandle<DrawContext> createDrawContext(CameraMode mode,
            Rectangle2D const &absoluteViewport, Transform const &transform) override;

        void beginDraw() override;
        void endDraw() override;
        TextureHandle loadTexture(std::string const &path) override;

        ~RaylibRendererContext() override = default;
    };
}

#endif