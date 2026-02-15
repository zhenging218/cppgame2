#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "memory/object_handle.hpp"

namespace cppengine {
    class DrawContext;

    class RendererContext {
    private:

    protected:
        virtual ObjectHandle<DrawContext> createDrawContext() = 0;

    public:
        virtual void BeginDraw() = 0;
        virtual void draw() = 0;
        virtual void EndDraw() = 0;
        virtual ~RendererContext() = 0;
    };

    inline RendererContext::~RendererContext() = default;
}

#endif