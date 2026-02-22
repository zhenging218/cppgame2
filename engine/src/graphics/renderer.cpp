#include <cmath>
#include <iostream>

#include "engine.hpp"
#include "../../../cmake-build-debug/_deps/raylib-src/src/raylib.h"

namespace {
    using renderable_entity_type = std::tuple<
        cppengine::ObjectHandle<cppengine::Transform>,
    cppengine::ObjectHandle<cppengine::Renderable>,
    cppengine::ObjectHandle<cppengine::Material>>;

    using renderable_item_type = std::tuple<
        cppengine::ObjectHandle<cppengine::Transform>,
    cppengine::ObjectHandle<cppengine::ModelHandle>,
    std::unordered_map<std::string, cppengine::Uniform>,
    std::unordered_map<std::string,
    cppengine::ObjectHandle<cppengine::TextureHandle>>>;

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
        auto position = transform.getPosition();
        auto rotation = transform.getRotation();
        auto scale_ = transform.getScale();

        auto zoom = (scale_.x + scale_.y) / 2;

        float halfWidth  = (viewport.width  / 2.0f) / zoom;
        float halfHeight = (viewport.height / 2.0f) / zoom;

        auto view = cppengine::inverse(translate(position) * rotate(rotation));

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

    std::map<cppengine::ShaderID, std::vector<renderable_item_type>> preprocessAndGroupByShaders(
        cppengine::ObjectHandle<cppengine::ModelContext> modelContext,
        cppengine::ObjectHandle<cppengine::TextureContext> texture_context,
        std::vector<renderable_entity_type> const &renderables
        ) {

        std::map<cppengine::ShaderID, std::vector<renderable_entity_type>> grouped;
        std::map<cppengine::ShaderID, std::vector<renderable_item_type>> result;

        for (auto const &renderable : renderables) {
            auto const & [t, r, m] = renderable;

            grouped[m->getShaderId()].push_back({t,r,m});
        }

        for (auto const &[id, group] : grouped) {
            for (auto const &[t, r, m] : group) {
                auto model = modelContext->getModel(r->getModelId());

                result[id].push_back({t, model, m->getUniforms(), {}});
            }
        }

        return result;
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

        std::sort(cameras.begin(), cameras.end(),
            [](auto const &lhs, auto const &rhs) {
                return std::get<ObjectHandle<Camera>>(lhs)->getMode() < std::get<ObjectHandle<Camera>>(rhs)->getMode();
            });

        auto renderables = preprocessAndGroupByShaders(
            context->getModelContext(),
            context->getTextureContext(),
            SceneManager::getInstance().getAllComponentSets<Transform, Renderable, Material>()
            );

        auto shaderContext= context->getShaderContext();

        context->beginDraw();

        for (auto const &[cameraTransform, camera] : cameras) {
            auto const &relativeViewport = camera->getViewport();
            auto absoluteViewport = getAbsoluteViewport(relativeViewport,
                Window::getInstance().getWidth(), Window::getInstance().getHeight());

            auto vp = getCameraVPMatrix(camera->getMode(), absoluteViewport, *cameraTransform);
            auto drawContext =
                context->createDrawContext(absoluteViewport, vp);

            drawContext->begin();

            for (auto const &batch : renderables) {
                auto shader = shaderContext->getShader(batch.first);
                drawContext->beginBatch(shader);

                for (auto const &[transform, model, uniforms, textures] : batch.second) {
                    // render
                    drawContext->render(shader, model, uniforms, textures, transform->getMatrix());
                }

                drawContext->endBatch(shader);
            }

            drawContext->flush();
        }

        context->endDraw();
    }

    ShaderID Renderer::loadShader(std::string const &name) {
        auto &instance = getInstance();
        return instance.context->getShaderContext()->loadShader(name);
    }

    Texture Renderer::loadTexture(std::string const &path) {
        return {};
    }

    Renderer &Renderer::getInstance() {
        static Renderer Renderer;
        return Renderer;
    }
}
