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

    GameObjectProxy::GameObjectProxy(std::uint64_t id_, SceneSetup *sceneSetup_)
        : id(id_), sceneSetup(sceneSetup_) {

    }

    SceneSetup::SceneSetup(Scene *scene_) : scene(scene_) {

    }

    SceneSetup::~SceneSetup() = default;
}
