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

        auto it = componentPoolMap.find(descriptor);

        if (it == componentPoolMap.end()) {
            auto [new_it, _] = componentPoolMap.emplace(descriptor, createHandle<ComponentPoolImpl<T>>());
            it = new_it;
            componentPools.push_back(it->second);
        }

        auto componentPool = static_handle_cast<ComponentPoolImpl<T>>(it->second);
        return componentPool->createComponent(std::forward<Args>(args)...);
    }
}

#endif //CPPGAME_COMPONENT_MANAGER_IMPL_HPP
