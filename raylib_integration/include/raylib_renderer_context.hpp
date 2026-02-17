#ifndef RAYLIB_GRAPHICS_CONTEXT_HPP
#define RAYLIB_GRAPHICS_CONTEXT_HPP

#include "integration/renderer_context.hpp"

namespace cppengine {
    class RaylibRendererContext : public RendererContext {
    private:

    public:
        ObjectHandle<DrawContext> createDrawContext(CameraMode mode,
            Rectangle2D const &absoluteViewport, Transform const &transform) override;

        ~RaylibRendererContext() override = default;
    };
}

#endif