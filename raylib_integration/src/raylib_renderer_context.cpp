#include "engine.hpp"
#include "raylib_draw_context_2d.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<DrawContext> RaylibRendererContext::createDrawContext(ObjectHandle<Camera> camera) {
        return ObjectHandle(new RaylibDrawContext2D());
    }

    void RaylibRendererContext::BeginDraw() {}

    void RaylibRendererContext::draw() {}

    void RaylibRendererContext::EndDraw() {}
}