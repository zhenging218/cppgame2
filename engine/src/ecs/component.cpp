#include "engine.hpp"

namespace cppengine {
    GameObject Component::getGameObject() const {
        auto id = SceneManager::getInstance().getEntityOfComponent(this);
        auto result = GameObject(id);
        return result;
    }

    GameObject Component::createGameObject() const {
        auto id = SceneManager::getInstance().createEntity();
        auto result = GameObject(id);
        return result;
    }
}
