#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <cstdint>
#include <utility>

#include "scene.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class GameObject {
    private:
        friend class Component;

        std::uint64_t id;
        ObjectHandle<Scene> scene;
    public:
        GameObject();

        GameObject(const GameObject &other);

        GameObject(GameObject &&other) noexcept;

        GameObject & operator=(GameObject const &other);

        template <typename T>
        ObjectHandle<T> getComponent() const {
            return scene->getComponent<T>(id);
        }

        template <typename T, typename ... Args>
        ObjectHandle<T> addComponent(Args &&...args) {
            return scene->addComponent<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        void removeComponent() {
            scene->removeComponent<T>(id);
        }

        std::string const &getName() const;
        void setName(std::string const &name);
        void setName(std::string &&name);

        ObjectHandle<Transform> getTransform() const;
    };

}

#endif