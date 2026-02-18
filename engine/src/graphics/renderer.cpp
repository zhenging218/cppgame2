#include <iostream>

#include "engine.hpp"
#include "graphics/triangle_primitive.hpp"

namespace {
    cppengine::Rectangle2D getAbsoluteViewport(
        cppengine::Rectangle2D const &relativeViewport, int screenWidth, int screenHeight) {
        return {
            screenWidth * relativeViewport.x,
            screenHeight * relativeViewport.y,
            screenWidth * relativeViewport.width,
            screenHeight * relativeViewport.height
        };
    }
}

namespace cppengine {
    Renderer::Renderer() {

    }

    void Renderer::initialise() {
        context = createContext();
    }

    void Renderer::shutdown() {

    }

    void Renderer::draw() {
        auto cameras = SceneManager::getInstance().getAllComponentSets<Transform, Camera>();
        auto triangles = SceneManager::getInstance().getAllComponentSets<Transform, TrianglePrimitive>();

        context->beginDraw();

        for (auto const &[transform, camera] : cameras) {

            auto const &relativeViewport = camera->getViewport();
            auto absoluteViewport = getAbsoluteViewport(relativeViewport,
                Window::getInstance().getWidth(), Window::getInstance().getHeight());

            auto drawContext =
                context->createDrawContext(camera->getMode(), absoluteViewport, *transform);

            drawContext->begin();

            for (auto const &[triangle_transform, triangle] : triangles) {
                drawContext->renderTriangle(triangle->getTriangle(), triangle_transform->getMatrix());
            }

            drawContext->flush();
        }

        context->endDraw();
    }

    Renderer &Renderer::getInstance() {
        static Renderer Renderer;
        return Renderer;
    }
}
