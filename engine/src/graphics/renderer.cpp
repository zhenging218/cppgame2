#include "engine.hpp"
#include "graphics/triangle_primitive.hpp"

namespace cppengine {
    Renderer::Renderer() {

    }

    void Renderer::initialise() {

    }

    void Renderer::shutdown() {

    }

    void Renderer::beginDraw() {

    }

    void Renderer::draw() {
        auto cameras = SceneManager::getInstance().getAllComponentSets<Transform, Camera>();

        for (auto const &[transform, camera] : cameras) {

            auto drawContext = context->createDrawContext(camera, transform);

            drawContext->begin();

            auto triangles = SceneManager::getInstance().getAllComponentSets<Transform, TrianglePrimitive>();
            for (auto const &[triangle_transform, triangle] : triangles) {
                drawContext->renderTriangle(triangle->getTriangle(), triangle_transform->getMatrix());
            }

            drawContext->flush();
        }
    }

    void Renderer::endDraw() {

    }

    Renderer &Renderer::getInstance() {
        static Renderer Renderer;
        return Renderer;
    }
}
