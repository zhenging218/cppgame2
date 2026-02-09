#include "engine.hpp"
#include "ecs/game_object.hpp"

namespace cppengine {
    GameObject Component::getGameObject() const {
        auto id = scene->getEntityOfComponent(this);
        auto result = GameObject();
        result.id = id;
        result.scene = scene;
        return result;
    }

    Component::~Component() {

    }
}
