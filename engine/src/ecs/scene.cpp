#include "ecs/scene.hpp"

#include "engine.hpp"

namespace cppengine {
    Scene::Scene() : nextId(1) {}

    std::uint64_t Scene::createEntity() {
        auto id = nextId++;
        entities[id] = "entity";
        transforms[id] = createHandle<Transform>();
        ecs[id] = {};
        return id;
    }

    void Scene::destroyEntity(std::uint64_t id) {
        auto transform = transforms.at(id);

        transform->getParent()->removeChild(*transform);

        auto children = transform->getChildren();

        std::ranges::for_each(children, [&transform](auto &child) {
            transform->removeChild(*child);
        });

        transforms.erase(id);

        auto const &componentsToDelete = ecs.at(id);
        std::ranges::for_each(componentsToDelete, [this, &id](auto const &type) {
            components.at(type).erase(id);
        });

        ecs.erase(id);

        entities.erase(id);
    }

    ObjectHandle<Transform> Scene::getTransform(std::uint64_t id) const {
        return transforms.at(id);
    }
}
