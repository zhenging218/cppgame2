#include "engine.hpp"
#include "raylib_draw_context_2d.hpp"
#include "raylib_integration.hpp"

#include <cmath>

namespace cppengine {
    ObjectHandle<DrawContext> RaylibRendererContext::createDrawContext(ObjectHandle<Camera> camera, ObjectHandle<Transform> transform) {
        // for now always assume camera is 2D
        ObjectHandle<Camera2D> camera2D = dynamic_handle_cast<Camera2D>(camera);

        ::Camera2D cameraImpl;

        auto position = transform->getPosition();;
        auto scale = transform->getScale();
        auto rotation = Vector3(transform->getRotation());

        cameraImpl.target = {position.x, position.y};

        cameraImpl.offset = {
            static_cast<float>(Window::getInstance().getWidth()) / 2.0f,
            static_cast<float>(Window::getInstance().getHeight()) / 2.0f
        };

        cameraImpl.zoom = (scale.x + scale.y) / 2;

        cameraImpl.rotation = rotation.z * (180.0f / PI);


        return ObjectHandle(new RaylibDrawContext2D(cameraImpl));
    }

    void RaylibRendererContext::BeginDraw() {}

    void RaylibRendererContext::draw() {}

    void RaylibRendererContext::EndDraw() {}
}