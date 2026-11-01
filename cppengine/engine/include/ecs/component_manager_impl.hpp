//
// Created by Admin on 1/11/2026.
//

#ifndef CPPGAME_COMPONENT_MANAGER_IMPL_HPP
#define CPPGAME_COMPONENT_MANAGER_IMPL_HPP

#include "ecs/component_manager.hpp"

namespace cppengine {
    template<typename T, typename... Args>
    ObjectHandle<T> ComponentManager::createComponent(Args &&... args) {
        const auto descriptor = TypeDescriptor::getTypeDescriptor<T>();

        auto it = std::ranges::find_if(componentPools, [descriptor](auto const &pool) {
            return pool.first == descriptor;
        });

        if (it == componentPools.end()) {
            auto [new_it, _] = componentPools.emplace(descriptor, createHandle<ComponentPoolImpl<T>>());
            it = new_it;
        }

        auto componentPool = static_handle_cast<ComponentPoolImpl<T>>(it->second);
        return componentPool->createComponent(std::forward<Args>(args)...);
    }
}

#endif //CPPGAME_COMPONENT_MANAGER_IMPL_HPP
