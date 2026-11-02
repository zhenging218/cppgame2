//
// Created by Admin on 2/11/2026.
//

#ifndef CPPGAME_GAME_OBJECT_IMPL_HPP
#define CPPGAME_GAME_OBJECT_IMPL_HPP

namespace cppengine {

    template<typename T> requires ComponentType<T>
    ObjectHandle<T> GameObject::getComponent() const {
        return scene->getComponent<T>(id);
    }

    template<typename T, typename... Args> requires ComponentType<T>
    ObjectHandle<T> GameObject::addComponent(Args &&... args) const {
        return scene->addComponent<T>(id, std::forward<Args>(args)...);
    }

    template<typename T> requires ComponentType<T>
    void GameObject::removeComponent() const {
        scene->removeComponent<T>(id);
    }
}

#endif //CPPGAME_GAME_OBJECT_IMPL_HPP
