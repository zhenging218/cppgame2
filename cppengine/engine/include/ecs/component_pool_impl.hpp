//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_POOL_IMPL_HPP
#define COMPONENT_POOL_IMPL_HPP

#include "ecs/ecs_concepts.hpp"
#include "ecs/component_pool.hpp"

namespace cppengine {

    template<typename T> requires std::invocable<T, Component &>
    ComponentPoolDelegate::ComponentPoolDelegate(T &delegate_)
        : delegate(&delegate_), invoker([](void*d, Component &component) { std::invoke(static_cast<T*>(d), component); }) {
    }

    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::init(ComponentPoolDelegate delegate) {
        allocator.visit([&delegate](T &component) {
            if constexpr (InitialisableComponentType<T>) {

            }
        });
    }

    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::update(ComponentPoolDelegate delegate) {
        allocator.visit([&delegate](T &component) {
            if constexpr (UpdatableComponentType<T>) {

            }
        });
    }

    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::dispose(ComponentPoolDelegate delegate) {
        allocator.visit([&delegate](T &component) {
            if constexpr (DisposableComponentType<T>) {

            }
        });
    }
}

#endif //COMPONENT_POOL_IMPL_HPP
