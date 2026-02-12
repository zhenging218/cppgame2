#include "ecs/game_object.hpp"

#include "engine.hpp"

namespace cppengine {
    GameObject::GameObject(const std::uint64_t id_) : id(id_) {

    }

    GameObject::GameObject(const GameObject &other)
            : id{other.id} {
    }

    GameObject::GameObject(GameObject &&other) noexcept
        : id{other.id} {
    }

    GameObject & GameObject::operator=(GameObject const &other) {
        id = other.id;
        return *this;
    }

    std::string const &GameObject::getName() const {
        return SceneManager::getInstance().getNameOfEntity(id);
    }

    void GameObject::setName(std::string const &name) {
        return SceneManager::getInstance().setNameOfEntity(id, name);
    }

    void GameObject::setName(std::string &&name) {
        return SceneManager::getInstance().setNameOfEntity(id, std::move(name));
    }

    ObjectHandle<Transform> GameObject::getTransform() const {
        return SceneManager::getInstance().getTransformOfEntity(id);
    }
}
