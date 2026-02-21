#include "engine.hpp"
#include "raylib_draw_context_2d.hpp"
#include "raylib_integration.hpp"

#include <cmath>

namespace cppengine {
    RaylibRendererContext::RaylibRendererContext() : shaderContext(new RaylibShaderContext()) {

    }

    ObjectHandle<DrawContext> RaylibRendererContext::createDrawContext(
        CameraMode mode, Rectangle2D const &absoluteViewport, Transform const &transform) {
        // for now always assume camera is 2D
        return ObjectHandle(new RaylibDrawContext2D(absoluteViewport, transform));
    }

    void RaylibRendererContext::beginDraw() {
        ClearBackground(::BLACK);
    }

    ObjectHandle<ShaderContext> RaylibRendererContext::getShaderContext() const {
        return shaderContext;
    }

    ObjectHandle<TextureContext> RaylibRendererContext::getTextureContext() const {
        return nullptr;
    }

    void RaylibRendererContext::endDraw() {
    }
}
