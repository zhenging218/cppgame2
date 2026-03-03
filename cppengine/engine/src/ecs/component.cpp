#include "engine.hpp"

namespace cppengine {
    GameObject Component::getGameObject() const {
        auto id = SceneManager::getInstance().getEntityOfComponent(this);
        auto result = GameObject(id);
        return result;
    }

    void Component::destroyGameObject(GameObject const &gameObject) const {
        SceneManager::getInstance().destroyEntity(gameObject.id);
    }

    GameObject Component::createGameObject() const {
        auto id = SceneManager::getInstance().createEntity();
        auto result = GameObject(id);
        return result;
    }
}
