#include "ecs/scene.hpp"

#include "engine.hpp"

namespace cppengine {
    Scene::Scene() : nextId(1) {}

    std::uint64_t Scene::createEntity() {
        auto id = nextId++;
        entities[id] = "entity";
        return id;
    }

    void Scene::destroyEntity(std::uint64_t id) {
        auto transform = transforms.at(id);
        transform->getParent()->removeChild(*transform);
        auto children = transform->getChildren();
        std::for_each(children.begin(), children.end(), [&transform](auto &child) {
            transform->removeChild(*child);
        });

        entities.erase(id);
    }
}
