#include <cmath>
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

    cppengine::Matrix4x4 buildOrthographicProjection(float left, float right, float bottom, float top, float near, float far) {
        return cppengine::Matrix4x4{
            2.0f/(right-left),  0,                  0,                  -(right+left)/(right-left),
            0,                  2.0f/(top-bottom),  0,                  -(top+bottom)/(top-bottom),
            0,                  0,                  -2.0f/(far-near),   -(far+near)/(far-near),
            0,                  0,                  0,                  1
        };
    }

    cppengine::Matrix4x4 buildPerspectiveProjection(float fovY, float aspect, float near, float far) {
        float tanHalfFov = std::tan(fovY / 2.0f);
        return cppengine::Matrix4x4{
            1.0f/(aspect*tanHalfFov),  0,                  0,                              0,
            0,                          1.0f/tanHalfFov,    0,                              0,
            0,                          0,                  -(far+near)/(far-near),         -2.0f*far*near/(far-near),
            0,                          0,                  -1,                             0
        };
    }

    cppengine::Matrix4x4 getCameraVPMatrixMode2D(cppengine::Rectangle2D const &viewport,
        cppengine::Transform &transform) {
        auto scale = transform.getScale();

        auto zoom = (scale.x + scale.y) / 2;

        float halfWidth  = (viewport.width  / 2.0f) / zoom;
        float halfHeight = (viewport.height / 2.0f) / zoom;

        auto view = cppengine::inverse(transform.getMatrix());

        cppengine::Matrix4x4 projection = buildOrthographicProjection(
                -halfWidth,   // left
                 halfWidth,   // right
                -halfHeight,  // bottom
                 halfHeight,  // top
                -1.0f,
                 1.0f
        );

        return projection * view;
    }

    cppengine::Matrix4x4 getCameraVPMatrix(cppengine::CameraMode mode, cppengine::Rectangle2D const &viewport, cppengine::Transform &transform) {
        switch (mode) {
            case cppengine::CameraMode::MODE_2D:
                return getCameraVPMatrixMode2D(viewport, transform);
            case cppengine::CameraMode::MODE_3D_PERSPECTIVE:
                break;
            case cppengine::CameraMode::MODE_3D_ORTHOGRAPHIC:
                break;
            case cppengine::CameraMode::MODE_UI:
                break;
        }
        return {};
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
                context->createDrawContext(absoluteViewport,
                    getCameraVPMatrix(camera->getMode(), absoluteViewport, *transform));

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
