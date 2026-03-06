#include "ecs/scene.hpp"

#include "engine.hpp"

namespace cppengine {
    Scene::Scene(ObjectHandle<ObjectAllocatorContext> allocators_) : allocators(allocators_), nextId(1) {}

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
        if (component != nullptr) {
            auto entityMap = components.find(component->descriptor);

            if (entityMap != components.end()) {
                auto result = std::ranges::find_if(entityMap->second, [component](auto const &value) {
                    return reinterpret_cast<void const *>(&*value.second) == reinterpret_cast<void const *>(component);
                });

                if (result != entityMap->second.end()) {
                    return result->first;
                }
            }
        }

        return 0;
    }

    std::uint64_t Scene::getEntityOfTransform(ObjectHandle<Transform> transform) const {
        if (transform != nullptr) {
            for (auto const &[id, t] : transforms) {
                if (t == transform) {
                    return id;
                }
            }
        }
        return 0;
    }

    std::uint64_t Scene::createEntity() {
        auto id = nextId++;
        entities[id] = "entity";
        transforms[id] = allocators->createHandle<Transform>();
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
        std::ranges::for_each(componentsToDelete, [this, &id](auto const &descriptor) {
            auto &entityMap = components.at(descriptor);
            descriptor->dispose(entityMap.at(id));
            entityMap.erase(id);
        });

        ecs.erase(id);

        entities.erase(id);
    }

    ObjectHandle<Transform> Scene::getTransformOfEntity(std::uint64_t id) const {
        return transforms.at(id);
    }

    std::vector<ObjectHandle<Component>> Scene::getAllComponents() const {
        std::vector<ObjectHandle<Component>> results;

        std::size_t total = 0;
        for (auto const &[descriptor, componentInstances] : components) {
            total += componentInstances.size();
        }

        results.reserve(total);

        for (auto const &[descriptor, componentInstances] : components) {
            std::ranges::transform(componentInstances, std::back_inserter(results), [](auto const &instance) {
                return instance.second;
            });
        }

        return results;
    }

    void Scene::init() {
        std::ranges::for_each(components, [](auto const &list) {
            list.first->init(list.second);
        });
    }

    void Scene::update() {
        std::ranges::for_each(components, [](auto const &list) {
            list.first->update(list.second);
        });
    }

    void Scene::dispose() {
        std::ranges::for_each(components, [](auto const &list) {
            list.first->dispose(list.second);
        });
    }
}
