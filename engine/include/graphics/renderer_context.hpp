#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "memory/object_handle.hpp"
#include "enum_camera_mode.hpp"
#include "texture_handle.hpp"
#include "maths/rectangle_2d.hpp"
#include "maths/transform.hpp"

namespace cppengine {
    class DrawContext;

    class RendererContext {
    public:
        virtual void beginDraw() = 0;

        virtual ObjectHandle<DrawContext> createDrawContext(
            CameraMode mode,Rectangle2D const &absoluteViewport, Transform const &transform) = 0;

        virtual void endDraw() = 0;

        virtual ~RendererContext() = 0;

        virtual TextureHandle loadTexture(std::string const &path) = 0;
    };

    inline RendererContext::~RendererContext() = default;
}

#endif