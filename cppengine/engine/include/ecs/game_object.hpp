#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <cstdint>
#include <utility>

#include "scene.hpp"
#include "scene_manager.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class GameObject {
    private:
        friend class Component;

        std::uint64_t id;
    public:
        GameObject(const std::uint64_t id_);

        GameObject(const GameObject &other);

        GameObject(GameObject &&other) noexcept;

        GameObject & operator=(GameObject const &other);

        template <typename T>
        ObjectHandle<T> getComponent() const {
            return SceneManager::getInstance().getComponent<T>(id);
        }

        template <typename T, typename ... Args>
        ObjectHandle<T> addComponent(Args &&...args) {
            return SceneManager::getInstance().addComponent<T>(id, std::forward<Args>(args)...);
        }

        template <typename T>
        void removeComponent() {
            SceneManager::getInstance().removeComponent<T>(id);
        }

        std::string const &getName() const;
        void setName(std::string const &name);
        void setName(std::string &&name);

        ObjectHandle<Transform> getTransform() const;
    };

}

#endif