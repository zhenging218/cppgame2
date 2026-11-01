//
// Created by Admin on 31/10/2026.
//

#include <ranges>
#include <utility>

#include "ecs/ecs.hpp"

namespace cppengine {

    Scene::Scene(ObjectHandle<TransformManager> transformManager_,ObjectHandle<ComponentManager> componentManager_, ObjectHandle<IdGenerator> idGenerator_,
                 ObjectHandle<CycleGenerator> cycleGenerator_)
        : cycleGenerator(std::move(cycleGenerator_)), idGenerator(std::move(idGenerator_)),
          transformManager(std::move(transformManager_)), componentManager(std::move(componentManager_)) {
        cycle = cycleGenerator->curr();
    }

    std::pair<std::uint64_t, std::string_view> Scene::createEntity() {
        return createEntity("entity");
    }

    std::pair<std::uint64_t, std::string_view> Scene::createEntity(std::string_view name) {
        auto [id, emplaced] = entities.emplace(idGenerator->next(), name);

        if (!emplaced) {
            throw R"(Somehow entity already exists)";
        }

        transforms.emplace(id->first, transformManager->createTransform());
        return { id->first, id->second };
    }

    std::pair<std::uint64_t, std::string_view> Scene::getEntity(std::uint64_t id) const {
        auto entity = std::ranges::find_if(entities, [id](auto const &e) { return e.first == id; });

        if (entity != entities.end()) {
            return { entity->first, entity->second };
        }

        return { idGenerator->unidentified(), "" };
    }

    void Scene::removeComponent(std::uint64_t entityId, TypeDescriptor const *descriptor) {
        auto &componentMap = components[descriptor];

        auto it = std::ranges::find_if(componentMap, [entityId](auto const &component) { return component.first == entityId; });


        if (it != componentMap.end()) {

            auto handle = it->second;

            handle->setState(ComponentState::DISPOSING);
            disposalQueue.emplace([this, descriptor, handle] {
                const auto disposer = componentManager->getDisposer(descriptor);
                disposer(*handle);
            });

            componentsOfEntities[entityId].erase(descriptor);
            componentMap.erase(entityId);
        }
    }

    void Scene::removeEntity(std::uint64_t entityId) {
        const auto [id, name] = getEntity(entityId);

        if (id != idGenerator->unidentified()) {
            if (auto const & componentsOfEntity = std::ranges::find_if(componentsOfEntities, [id](auto const &ce) { return ce.first == id; }); componentsOfEntity != componentsOfEntities.end()) {
                const auto componentsToRemove = componentsOfEntity->second;

                std::ranges::for_each(componentsToRemove, [this, entityId](auto const &descriptor) {
                    removeComponent(entityId, descriptor);
                });

                componentsOfEntity->second = {};

                disposalQueue.emplace([this, entityId] {

                    const auto [idCheck, _] = getEntity(entityId);

                    if (idCheck != idGenerator->unidentified()) {
                        // last mile component removal
                        if (auto const & leftoverComponentsOfEntity = std::ranges::find_if(componentsOfEntities, [entityId](auto const &ce) { return ce.first == entityId; }); leftoverComponentsOfEntity != componentsOfEntities.end()) {
                            while (!leftoverComponentsOfEntity->second.empty()) {
                                const auto leftoverComponentsToRemove = leftoverComponentsOfEntity->second;

                                std::ranges::for_each(leftoverComponentsToRemove, [this, entityId](auto const &descriptor) {
                                    auto &componentMap = components[descriptor];
                                    auto handle = componentMap[entityId];

                                    const auto disposer = componentManager->getDisposer(descriptor);
                                    handle->setState(ComponentState::DISPOSING);
                                    disposer(*handle);
                                });
                            }
                        }

                        componentsOfEntities.erase(entityId);
                        transforms.erase(entityId);
                        entities.erase(entityId);
                    }
                });
            }
        }
    }

    void Scene::init() {
        componentManager->init();
    }

    void Scene::update() {
        cycle = cycleGenerator->next();
        componentManager->update(cycle);

        auto snapshot = disposalQueue;
        disposalQueue = {};

        while (!snapshot.empty()) {
            auto command = snapshot.front();
            snapshot.pop();
            command();
        }
    }

    void Scene::dispose() {
        componentManager->dispose();
    }
}
