//
// Created by Admin on 31/10/2026.
//

#include <utility>

#include "ecs/ecs.hpp"

namespace cppengine {
    Scene::Scene(ObjectHandle<TransformManager> transformManager_,ObjectHandle<ComponentManager> componentManager_, ObjectHandle<IdGenerator> idGenerator_,
        ObjectHandle<CycleGenerator> cycleGenerator_)
        : cycleGenerator(std::move(cycleGenerator_)), idGenerator(std::move(idGenerator_)),
          transformManager(std::move(transformManager_)), componentManager(std::move(componentManager_)) {
        cycle = cycleGenerator->curr();
    }

    Scene::Scene(Scene &&other) noexcept
        : cycle(other.cycle), cycleGenerator(std::move(other.cycleGenerator)), idGenerator(std::move(other.idGenerator)),
          transformManager(std::move(other.transformManager)), componentManager(std::move(other.componentManager)),
          entities(std::move(other.entities)), transforms(std::move(other.transforms)),
          components(std::move(other.components)), disposalQueue(std::move(other.disposalQueue)) {

    }

    Scene & Scene::operator=(Scene &&other) noexcept {
        cycle = other.cycle;
        cycleGenerator = std::move(other.cycleGenerator);
        idGenerator = std::move(other.idGenerator);
        transformManager = std::move(other.transformManager);
        componentManager = std::move(other.componentManager);
        entities = std::move(other.entities);
        transforms = std::move(other.transforms);
        components = std::move(other.components);
        disposalQueue = std::move(other.disposalQueue);

        return *this;
    }

    std::pair<std::uint64_t, std::string_view> Scene::createEntity() {
        return createEntity("entity");
    }

    std::pair<std::uint64_t, std::string_view> Scene::createEntity(std::string_view name) {
        auto [id, emplaced] = entities.emplace(idGenerator->next(), name);

        if (!emplaced) {
            throw R"(Somehow entity already exists)";
        }

        return { id->first, id->second };
    }

    std::pair<std::uint64_t, std::string_view> Scene::getEntity(std::uint64_t id) const {
        auto entity = std::ranges::find_if(entities, [id](auto const &e) { return e.first == id; });

        if (entity != entities.end()) {
            return { entity->first, entity->second };
        }

        return { idGenerator->unidentified(), "" };
    }

    void Scene::init() {
    }

    void Scene::update() {
    }

    void Scene::dispose() {
    }
}
