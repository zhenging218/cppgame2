//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_ECS_CONCEPTS_HPP
#define CPPGAME_ECS_CONCEPTS_HPP
#include <concepts>

namespace cppengine {
    class Transform;
    class Component;

    template <typename T>
    concept ComponentType = std::derived_from<T, Component>;

    template <typename T>
    concept TransformType = std::same_as<T, Transform>;

    template <typename T>
    concept InitialisableComponentType = ComponentType<T> && requires(T &t) { { t.init() } -> std::same_as<void>; };

    template <typename T>
    concept UpdatableComponentType = ComponentType<T> && requires(T &t) { { t.update() } -> std::same_as<void>; };

    template <typename T>
    concept DisposableComponentType = ComponentType<T> && requires(T &t) { { t.dispose() } -> std::same_as<void>; };
}

#endif //CPPGAME_ECS_CONCEPTS_HPP
