#include "engine.hpp"
#include "raylib_draw_context.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<DrawContext> RaylibRendererContext::createDrawContext() {
        return ObjectHandle(new RaylibDrawContext());
    }

    void RaylibRendererContext::BeginDraw() {}

    void RaylibRendererContext::draw() {}

    void RaylibRendererContext::EndDraw() {}
}