#include "game.hpp"
#include "graphics/triangle_primitive.hpp"

namespace cppgame {
    void TestLevel::setup(cppengine::ObjectHandle<cppengine::Scene> scene) {
        auto camera = scene->createEntity();
        scene->addComponent<cppengine::Camera2D>(camera);

        auto triangle = scene->createEntity();
        auto triangle_primitive = scene->addComponent<cppengine::TrianglePrimitive>(triangle);
        scene->addComponent<TestComponent>(triangle);
        auto triangle_go = triangle_primitive->getGameObject();
        triangle_go.getTransform()->setScale({100, 100, 1});

        auto box2d = scene->createEntity();
        auto box2d_primitive = scene->addComponent<cppengine::Box2DPrimitive>(box2d);
        auto box2d_go = box2d_primitive->getGameObject();
        auto box2d_transform = box2d_go.getTransform();
        box2d_transform->setPosition({200, 200, 1});
        box2d_transform->setScale({100, 100, 1});

    }
}
