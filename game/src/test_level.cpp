#include "game.hpp"
#include "graphics/triangle_primitive.hpp"

namespace cppgame {
    void TestLevel::setup(cppengine::ObjectHandle<cppengine::Scene> scene) {
        auto camera = scene->createEntity();
        scene->addComponent<cppengine::Camera2D>(camera);

        auto triangle = scene->createEntity();
        auto primitive = scene->addComponent<cppengine::TrianglePrimitive>(triangle);
        auto primitiveGo = primitive->getGameObject();
        primitiveGo.getTransform()->setScale({100, 100, 1});

    }
}
