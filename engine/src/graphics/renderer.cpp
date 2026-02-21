#include <iostream>

#include "engine.hpp"

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
        auto box2Ds = SceneManager::getInstance().getAllComponentSets<Transform, Box2DPrimitive>();

        // todo: switch to get all renderables after support is implemented
        // auto renderables = SceneManager::getInstance().getAllComponentSets<Transform, Renderable>();

        std::sort(cameras.begin(), cameras.end(),
            [](auto const &lhs, auto const &rhs) {
                return std::get<ObjectHandle<Camera>>(lhs)->getMode() < std::get<ObjectHandle<Camera>>(rhs)->getMode();
            });

        // todo: group renderables by material shader id
        //       mutate items into another structure that keeps
        //       (model_handle, uniforms_map, texture_handle_map, transform_mat4x4);

        context->beginDraw();

        for (auto const &[transform, camera] : cameras) {

            auto const &relativeViewport = camera->getViewport();
            auto absoluteViewport = getAbsoluteViewport(relativeViewport,
                Window::getInstance().getWidth(), Window::getInstance().getHeight());

            auto drawContext =
                context->createDrawContext(camera->getMode(), absoluteViewport, *transform);

            drawContext->begin();

            // todo: switch to shader batch rendering:
            //       for each grouped render structure:
            //          call drawContext->beginBatch(current_shader);
            //          for every renderable in the batch, call drawContext->render(...);
            //          call drawContext->endBatch(current_shader);

            for (auto const &[triangle_transform, triangle] : triangles) {
                drawContext->renderTriangle(triangle->getTriangle(), triangle_transform->getMatrix());
            }

            for (auto const &[box2d_transform, box2d] : box2Ds) {
                drawContext->renderBox2D(box2d->getBox2D(), box2d_transform->getMatrix());
            }

            drawContext->flush();
        }

        context->endDraw();
    }

    ShaderID Renderer::loadShader(char const *name, char const *vertexShaderPath, char const *fragmentShaderPath) {
        auto &instance = getInstance();
        return instance.context->getShaderContext()->loadShader(name, vertexShaderPath, fragmentShaderPath);
    }

    Renderer &Renderer::getInstance() {
        static Renderer Renderer;
        return Renderer;
    }
}
