//
// Created by Admin on 2/11/2026.
//

#ifndef CPPGAME_SCENE_SETUP_IMPL_HPP
#define CPPGAME_SCENE_SETUP_IMPL_HPP

#include "ecs/ecs_concepts.hpp"
#include "ecs/scene_setup.hpp"

namespace cppengine {
    template<typename T, typename... Args> requires ComponentType<T>
    ComponentProxy<T> GameObjectProxy::addComponent(Args &&... args) const {
        return { id, sceneSetup->scene->setupComponent<T>(id, std::forward<Args>(args)...), sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    ComponentProxy<T> GameObjectProxy::getComponent() const {
        return { sceneSetup->scene->getComponent<T>(id), sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    ComponentProxy<T>::ComponentProxy(std::uint64_t owner_, ObjectHandle<T> component_, SceneSetup const *sceneSetup_)
        : owner(owner_), component(component_), sceneSetup(sceneSetup_) {

    }

    template<typename T> requires ComponentType<T>
    GameObjectProxy ComponentProxy<T>::getGameObject() const {
        const auto [id, name] = sceneSetup->scene->getEntity(owner);

        return { id, sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    T *ComponentProxy<T>::operator->() const {
        return &(*component);
    }
}

#endif //CPPGAME_SCENE_SETUP_IMPL_HPP
