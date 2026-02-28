#include <cmath>
#include <iostream>

#include "engine.hpp"

namespace {
    using namespace cppengine;
    
    using renderable_entity_type = std::tuple<
        ObjectHandle<Transform>,
    ObjectHandle<Renderable>,
    ObjectHandle<Material>>;

    using renderable_item_type = std::tuple<
        ObjectHandle<Transform>,
    ObjectHandle<ModelHandle>,
    std::unordered_map<std::string, Uniform>,
    std::unordered_map<std::string,
    ObjectHandle<TextureHandle>>>;

    Rectangle2D getAbsoluteViewport(
        Rectangle2D const &relativeViewport, const int frameBufferWidth, const int frameBufferHeight) {
        return {
            frameBufferWidth * relativeViewport.x,
            frameBufferHeight * relativeViewport.y,
            frameBufferWidth * relativeViewport.width,
            frameBufferHeight * relativeViewport.height
        };
    }

    Matrix4x4 buildOrthographicProjection(float left, float right, float bottom, float top, float near, float far) {
        return Matrix4x4{
            2.0f/(right-left),  0,                  0,                  -(right+left)/(right-left),
            0,                  2.0f/(top-bottom),  0,                  -(top+bottom)/(top-bottom),
            0,                  0,                  -2.0f/(far-near),   -(far+near)/(far-near),
            0,                  0,                  0,                  1
        };
    }

    Matrix4x4 buildPerspectiveProjection(float fovY, float aspect, float near, float far) {
        float tanHalfFov = std::tan(fovY / 2.0f);
        return Matrix4x4{
            1.0f/(aspect*tanHalfFov),  0,                  0,                              0,
            0,                          1.0f/tanHalfFov,    0,                              0,
            0,                          0,                  -(far+near)/(far-near),         -2.0f*far*near/(far-near),
            0,                          0,                  -1,                             0
        };
    }

    Matrix4x4 getCameraVPMatrixMode2D(Rectangle2D const &viewport,
        Transform &transform) {
        auto position = transform.getPosition();
        auto rotation = transform.getRotation();
        auto scale_ = transform.getScale();

        auto zoom = (scale_.x + scale_.y) / 2;

        float halfWidth  = (viewport.width  / 2.0f) / zoom;
        float halfHeight = (viewport.height / 2.0f) / zoom;

        auto view = inverse(translate(position) * rotate(rotation));

        Matrix4x4 projection = buildOrthographicProjection(
                -halfWidth,   // left
                 halfWidth,   // right
                -halfHeight,  // bottom
                 halfHeight,  // top
                -1.0f,
                 1.0f
        );

        return projection * view;
    }

    Matrix4x4 getCameraVPMatrix(CameraMode mode, Rectangle2D const &viewport, Transform &transform) {
        switch (mode) {
            case CameraMode::MODE_2D:
                return getCameraVPMatrixMode2D(viewport, transform);
            case CameraMode::MODE_3D_PERSPECTIVE:
                break;
            case CameraMode::MODE_3D_ORTHOGRAPHIC:
                break;
            case CameraMode::MODE_UI:
                break;
        }
        return {};
    }

    std::map<ShaderID, std::vector<renderable_item_type>> preprocessAndGroupByShaders(
        ObjectHandle<ModelContext> modelContext,
        ObjectHandle<TextureContext> texture_context,
        std::vector<renderable_entity_type> const &renderables
        ) {

        std::map<ShaderID, std::vector<renderable_entity_type>> grouped;
        std::map<ShaderID, std::vector<renderable_item_type>> result;

        for (auto const &renderable : renderables) {
            auto const & [t, r, m] = renderable;

            grouped[m->getShaderId()].emplace_back(t,r,m);
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
    Renderer::Renderer() = default;

    void Renderer::initialise() {
        context = createContext();
    }

    void Renderer::shutdown() {

    }

    void Renderer::draw() {

        auto cameras = SceneManager::getInstance().getAllComponentSets<Transform, Camera>();

        std::ranges::sort(cameras,
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

        auto [width, height] = context->getFrameBufferSize();

        for (auto const &[cameraTransform, camera] : cameras) {
            auto const &relativeViewport = camera->getViewport();
            auto absoluteViewport = getAbsoluteViewport(relativeViewport,
               width, height);

            auto vp = getCameraVPMatrix(camera->getMode(), absoluteViewport, *cameraTransform);
            auto drawContext =
                context->createDrawContext(absoluteViewport, vp);

            drawContext->begin();

            for (auto const &batch : renderables) {
                auto shader = shaderContext->getShader(batch.first);
                drawContext->bindShader(shader);

                for (auto const &[transform, model, uniforms, textures] : batch.second) {
                    // render
                    drawContext->bindModel(model);
                    drawContext->render(shader, model, uniforms, textures, transform->getMatrix());
                    drawContext->unbindModel(model);
                }

                drawContext->unbindShader(shader);
            }

            drawContext->flush();
        }

        context->endDraw();
    }

    ModelID Renderer::getModel(std::string const &name) {
        auto &instance = getInstance();
        return instance.context->getModelContext()->getModel(name);
    }

    ShaderID Renderer::getShader(std::string const &name) {
        auto &instance = getInstance();
        return instance.context->getShaderContext()->getShader(name);
    }

    ModelID Renderer::loadModel(std::string const &name, Vector3 const *vertices, std::size_t vertex_count, std::size_t const *indices, std::size_t index_count) {
        auto &instance = getInstance();
        return instance.context->getModelContext()->loadModel(name, vertices, indices, vertex_count, index_count);
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
