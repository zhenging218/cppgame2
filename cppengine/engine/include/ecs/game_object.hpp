//
// Created by Admin on 2/11/2026.
//

#ifndef CPPGAME_GAME_OBJECT_HPP
#define CPPGAME_GAME_OBJECT_HPP

#include <cstdint>
#include <string>

#include "ecs_concepts.hpp"
#include "memory/object_handle.hpp"


namespace cppengine {
    class Transform;

    class GameObject {
    private:
        friend class Component;
        friend class Scene;

        std::uint64_t id;
        Scene *scene;

        GameObject(std::uint64_t id_, Scene * scene_);
    public:

        template <typename T> requires ComponentType<T>
        ObjectHandle<T> getComponent() const;

        template <typename T, typename ... Args> requires ComponentType<T>
        ObjectHandle<T> addComponent(Args &&... args) const;

        template <typename T> requires ComponentType<T>
        void removeComponent() const;

        [[nodiscard]] std::string_view getName() const;
        void setName(std::string_view name) const;

        [[nodiscard]] ObjectHandle<Transform> getTransform() const;
    };

}

#endif //CPPGAME_GAME_OBJECT_HPP
