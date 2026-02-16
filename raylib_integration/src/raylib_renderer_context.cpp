#include "engine.hpp"
#include "raylib_draw_context_2d.hpp"
#include "raylib_integration.hpp"

namespace cppengine {
    ObjectHandle<DrawContext> RaylibRendererContext::createDrawContext(ObjectHandle<Camera> camera) {
        ObjectHandle<Camera2D> camera2D = dynamic_handle_cast<Camera2D>(camera);
        // todo:
        return ObjectHandle(new RaylibDrawContext2D(::Camera2D()));
    }

    void RaylibRendererContext::BeginDraw() {}

    void RaylibRendererContext::draw() {}

    void RaylibRendererContext::EndDraw() {}
}