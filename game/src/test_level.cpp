#include "game.hpp"
#include "graphics/triangle_primitive.hpp"

namespace cppgame {
    using namespace cppengine;

    void TestLevel::setup(ObjectHandle<Scene> scene) {
        auto camera = scene->createEntity();
        auto camera_camera2d = scene->addComponent<Camera2D>(camera);
        auto camera_go = camera_camera2d->getGameObject();
        auto camera_transform = camera_go.getTransform();
        camera_transform->setPosition({0,0,1});

        auto triangle = scene->createEntity();
        auto triangle_primitive = scene->addComponent<TrianglePrimitive>(triangle);
        scene->addComponent<TestComponent>(triangle);
        auto triangle_material = scene->addComponent<Material>(triangle);
        triangle_material->setShader(DEFAULT_SHADER_NAME);
        triangle_material->setUniform(ShaderLocation::SHADER_DIFFUSE_COLOUR_UNIFORM, Colour{1.f, 0.f, 0.f, 1.f});

        auto triangle_go = triangle_primitive->getGameObject();
        triangle_go.getTransform()->setScale({100, 100, 1});

        auto box2d = scene->createEntity();
        auto box2d_primitive = scene->addComponent<Box2DPrimitive>(box2d);
        auto box2d_material = scene->addComponent<Material>(box2d);
        box2d_material->setShader(DEFAULT_SHADER_NAME);
        box2d_material->setUniform(ShaderLocation::SHADER_DIFFUSE_COLOUR_UNIFORM, Colour{0.f, 0.f, 1.f, 1.f});
        auto box2d_go = box2d_primitive->getGameObject();
        auto box2d_transform = box2d_go.getTransform();
        box2d_transform->setPosition({200, 200, 1});
        box2d_transform->setScale({100, 100, 1});

    }
}
