//
// Created by Admin on 2/11/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    GameObject::GameObject(std::uint64_t id_, Scene *scene_) : id(id_), scene(scene_) {

    }

    std::string_view GameObject::getName() const {
        auto const [entityId, name] = scene->getEntity(id);
        return name;
    }

    void GameObject::setName(std::string_view name) const {
        scene->setEntityName(id, name);
    }

    ObjectHandle<Transform> GameObject::getTransform() const {
        return scene->getComponent<Transform>(id);
    }
}
