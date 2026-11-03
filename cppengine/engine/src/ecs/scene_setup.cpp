//
// Created by Admin on 2/11/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    std::string_view GameObjectProxy::getName() const {
        const auto [id_, name] = sceneSetup->scene->getEntity(id);
        return name;
    }

    ObjectHandle<Transform> GameObjectProxy::getTransform() const {
        return sceneSetup->scene->getComponent<Transform>(id);
    }

    GameObjectProxy::GameObjectProxy(std::uint64_t id_, SceneSetup const *sceneSetup_)
        : id(id_), sceneSetup(sceneSetup_) {

    }

    void SceneSetup::setScene(Scene *scene_) {
        scene = scene_;
    }

    GameObjectProxy SceneSetup::createGameObject(std::string_view name) const {
        const auto [id_, name_] = scene->createEntity(name);

        return GameObjectProxy(id_, this);
    }

    GameObjectProxy SceneSetup::createGameObject() const {
        return createGameObject("gameObject");
    }

    SceneSetup::~SceneSetup() = default;
}
