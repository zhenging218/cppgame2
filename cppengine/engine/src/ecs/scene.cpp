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

    void Scene::setEntityName(std::uint64_t entityId, std::string_view newName) {
        auto it = entities.find(entityId);

        if (it != entities.end()) {
            it->second = newName;
        }
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
        if (const auto entity = entities.find(id); entity != entities.end()) {
            return { entity->first, entity->second };
        }

        return { idGenerator->unidentified(), "" };
    }

    void Scene::removeComponent(std::uint64_t entityId, TypeDescriptor const *descriptor) {
        auto &componentMap = components[descriptor];

        if (auto it = componentMap.find(entityId); it != componentMap.end()) {

            auto handle = it->second;

            switch (handle->getState()) {
                case ComponentState::INITIALISING: {
                        handle->setState(ComponentState::DISPOSED);
                        disposalQueue.emplace([h = std::move(handle)] {

                        });

                        componentsOfEntities[entityId].erase(descriptor);
                        componentMap.erase(entityId);
                    }
                    break;
                case ComponentState::ACTIVE: {
                        handle->setState(ComponentState::DISPOSING);
                        disposalQueue.emplace([this, descriptor, h = std::move(handle)] {
                            const auto disposer = componentManager->getDisposer(descriptor);
                            disposer(*h);
                        });

                        componentsOfEntities[entityId].erase(descriptor);
                        componentMap.erase(entityId);
                    }
                    break;
                default:
                    break;
            }

        }
    }

    void Scene::commitDisposals() {
        std::queue<std::function<void()>> snapshot;
        std::swap(snapshot, disposalQueue);

        while (!snapshot.empty()) {
            auto command = std::move(snapshot.front());
            snapshot.pop();
            command();
        }
    }

    void Scene::removeEntity(std::uint64_t entityId) {
        const auto [id, name] = getEntity(entityId);

        if (id != idGenerator->unidentified()) {
            if (auto const & componentsOfEntity = componentsOfEntities.find(entityId); componentsOfEntity != componentsOfEntities.end()) {
                const auto componentsToRemove = componentsOfEntity->second;

                std::ranges::for_each(componentsToRemove, [this, entityId](auto const &descriptor) {
                    removeComponent(entityId, descriptor);
                });

                componentsOfEntity->second = {};
            }

            disposalQueue.emplace([this, entityId] {
                const auto [idCheck, _] = getEntity(entityId);

                if (idCheck != idGenerator->unidentified()) {
                    // last mile component removal
                    if (auto const & leftoverComponentsOfEntity = componentsOfEntities.find(entityId); leftoverComponentsOfEntity != componentsOfEntities.end()) {
                        auto &componentsOfEntity = leftoverComponentsOfEntity->second;
                        while (!componentsOfEntity.empty()) {
                            const auto leftoverComponentsToRemove = componentsOfEntity;
                            componentsOfEntity = {};

                            std::ranges::for_each(leftoverComponentsToRemove, [this, entityId](auto const &descriptor) {
                                auto componentMap = components.find(descriptor);

                                if (componentMap != components.end()) {
                                    auto &cm = componentMap->second;
                                    auto handle = cm.find(entityId);
                                    if (handle != cm.end()) {
                                        const auto disposer = componentManager->getDisposer(descriptor);
                                        disposer(*handle->second);
                                        cm.erase(entityId);
                                    }
                                }
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

    void Scene::init() {
        componentManager->init();
        commitDisposals();
    }

    void Scene::update() {
        cycle = cycleGenerator->next();
        componentManager->update(cycle);
        commitDisposals();
    }

    void Scene::dispose() {
        commitDisposals();
        componentManager->dispose();
        components = {};
        componentsOfEntities = {};
        transforms = {};
        entities = {};
        disposalQueue = {};
    }
}
