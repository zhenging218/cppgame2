//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_POOL_IMPL_HPP
#define COMPONENT_POOL_IMPL_HPP

#include "ecs/ecs_concepts.hpp"
#include "ecs/component_pool.hpp"

namespace cppengine {
    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::init() {
        auto initialiser = getInitialiser();
        allocator.visit([&initialiser](T &component) {
            initialiser(component);
        });
    }

    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::update(std::uint64_t cycle) {
        allocator.visit([cycle](T &component) {
            if (component.getStamp() < cycle && component.getState() == ComponentState::ACTIVE) {
                if constexpr (UpdatableComponentType<T>) {
                    component.update();
                }
            }
        });
    }

    template <typename T> requires ComponentType<T>
    void ComponentPoolImpl<T>::dispose() {
        auto disposer = getDisposer();
        allocator.visit([&disposer](T &component) {
            disposer(component);
        });
    }

    template<typename T> requires ComponentType<T>
    std::function<void(Component &)> ComponentPoolImpl<T>::getInitialiser() const {
        return [](Component &component) {
            if (component.getState() == ComponentState::INITIALISING) {
                if constexpr (InitialisableComponentType<T>) {
                    static_cast<T&>(component).init();
                }

                if (component.getState() == ComponentState::INITIALISING) {
                    component.setState(ComponentState::ACTIVE);
                }
            }
        };
    }

    template<typename T> requires ComponentType<T>
    std::function<void(Component &)> ComponentPoolImpl<T>::getDisposer() const {
        return [](Component &component) {
            if (component.getState() == ComponentState::INITIALISING) {
                component.setState(ComponentState::DISPOSED);
            } else if (component.getState() != ComponentState::DISPOSED) {
                component.setState(ComponentState::DISPOSING);
                if constexpr (DisposableComponentType<T>) {
                    static_cast<T&>(component).dispose();
                }

                if (component.getState() == ComponentState::DISPOSING) {
                    component.setState(ComponentState::DISPOSED);
                }
            }
        };
    }

    template<typename T> requires ComponentType<T>
    template<typename ... Args>
    ObjectHandle<T> ComponentPoolImpl<T>::createComponent(Args &&...args) {
        return allocator.createHandle(std::forward<Args>(args)...);
    }
}

#endif //COMPONENT_POOL_IMPL_HPP
