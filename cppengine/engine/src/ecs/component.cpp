//
// Created by Admin on 31/10/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    std::uint64_t Component::getStamp() const {
        return stamp;
    }

    ComponentState Component::getState() const {
        return state;
    }

    std::uint64_t Component::getOwner() const {
        return owner;
    }

    void Component::setOwner(std::uint64_t newOwner) {
        owner = newOwner;
    }

    void Component::setStamp(std::uint64_t newStamp) {
        stamp = newStamp;
    }

    void Component::setState(ComponentState newState) {
        state = newState;
    }

    Scene *Component::getScene() const {
        return scene;
    }

    void Component::setScene(Scene *newScene) {
        scene = newScene;
    }

    GameObject Component::createGameObject() const {
        const auto [id_, name] = scene->createEntity();

        return {id_, scene};
    }

    GameObject Component::getGameObject() const {
        return {owner, scene};
    }

    void Component::destroyGameObject(GameObject const &gameObject) const {
        scene->removeEntity(gameObject.id);
    }

    Component::~Component() = default;
}
