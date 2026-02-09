#include "ecs/scene.hpp"

#include "engine.hpp"

namespace cppengine {
    Scene::Scene() : nextId(1) {}

    Scene::Scene(Scene &&other) noexcept
            : nextId(other.nextId),
              entities(std::move(other.entities)),
              transforms(std::move(other.transforms)),
              ecs(std::move(other.ecs)),
              components(std::move(other.components)) {
    }

    Scene & Scene::operator=(Scene &&other) noexcept {
        std::swap(nextId, other.nextId);
        std::swap(entities, other.entities);
        std::swap(transforms, other.transforms);
        std::swap(ecs, other.ecs);
        std::swap(components, other.components);
        return *this;
    }

    std::string const & Scene::getNameOfEntity(uint64_t id) const {
        return entities.at(id);
    }

    void Scene::setNameOfEntity(std::uint64_t id, std::string const &name) {
        if (entities.contains(id)) {
            entities[id] = name;
        }
    }

    void Scene::setNameOfEntity(std::uint64_t id, std::string &&name) {
        if (entities.contains(id)) {
            entities[id] = std::move(name);
        }
    }

    std::uint64_t Scene::getEntityOfComponent(Component const *component) const {
        auto result = std::ranges::find_if(ecs, [&component](auto const &value) {
            return value.second.contains(component->descriptor);
        });

        if (result != ecs.end()) {
            return result->first;
        }

        return 0;
    }


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

    ObjectHandle<Transform> Scene::getTransformOfEntity(std::uint64_t id) const {
        return transforms.at(id);
    }
}
