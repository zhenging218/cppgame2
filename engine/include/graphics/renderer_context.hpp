#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "memory/object_handle.hpp"
#include "enum_camera_mode.hpp"
#include "shader_context.hpp"
#include "texture_context.hpp"
#include "texture.hpp"
#include "maths/rectangle_2d.hpp"
#include "maths/transform.hpp"

namespace cppengine {
    class DrawContext;

    class RendererContext {
    public:
        virtual void beginDraw() = 0;

        virtual ObjectHandle<DrawContext> createDrawContext(Rectangle2D const &absoluteViewport, Matrix4x4 const &transform) = 0;

        virtual ObjectHandle<TextureContext> getTextureContext() const = 0;
        virtual ObjectHandle<ShaderContext> getShaderContext() const = 0;

        virtual void endDraw() = 0;

        virtual ~RendererContext() = 0;
    };

    inline RendererContext::~RendererContext() = default;
}

#endif