#ifndef RAYLIB_GRAPHICS_CONTEXT_HPP
#define RAYLIB_GRAPHICS_CONTEXT_HPP

#include "integration/renderer_context.hpp"

namespace cppengine {
    class RaylibRendererContext : public RendererContext {
    private:

    public:
        void BeginDraw() override;

        void draw() override;

        void EndDraw() override;

        ObjectHandle<DrawContext> createDrawContext(ObjectHandle<Camera> camera) override;

        ~RaylibRendererContext() override = default;
    };
}

#endif