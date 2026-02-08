#include "ecs/game_object.hpp"

#include "engine.hpp"

namespace cppengine {
    GameObject::GameObject() {

    }

    std::string const &GameObject::getName() const {
        return scene->getNameOfEntity(id);
    }

    void GameObject::setName(std::string const &name) {
        return scene->setNameOfEntity(id, name);
    }

    void GameObject::setName(std::string &&name) {
        return scene->setNameOfEntity(id, std::move(name));
    }

    ObjectHandle<Transform> GameObject::getTransform() const {
        return scene->getTransformOfEntity(id);
    }
}
