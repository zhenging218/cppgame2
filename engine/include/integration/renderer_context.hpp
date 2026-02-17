#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "memory/object_handle.hpp"
#include "graphics/camera.hpp"
#include "maths/transform.hpp"

namespace cppengine {
    class DrawContext;

    class RendererContext {
    private:

    protected:


    public:
        virtual ObjectHandle<DrawContext> createDrawContext(ObjectHandle<Camera> camera, ObjectHandle<Transform> transform) = 0;
        virtual void BeginDraw() = 0;
        virtual void draw() = 0;
        virtual void EndDraw() = 0;
        virtual ~RendererContext() = 0;
    };

    inline RendererContext::~RendererContext() = default;
}

#endif