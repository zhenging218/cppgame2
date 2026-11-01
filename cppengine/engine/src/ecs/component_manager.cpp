//
// Created by Admin on 31/10/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    ObjectHandle<ComponentPool> ComponentManager::getComponentPool(TypeDescriptor const *descriptor) {
        auto pool = std::ranges::find_if(componentPools, [descriptor](auto const &pool) { return pool.first == descriptor; });

        if (pool != componentPools.end()) {
            return pool->second;
        }

        return nullptr;
    }

    ObjectHandle<const ComponentPool> ComponentManager::
    getComponentPool(TypeDescriptor const *descriptor) const {
        auto pool = std::ranges::find_if(componentPools, [descriptor](auto const &pool) { return pool.first == descriptor; });

        if (pool != componentPools.end()) {
            return const_handle_cast<const ComponentPool>(pool->second);
        }

        return nullptr;
    }

    std::function<void(Component &)> ComponentManager::getInitialiser(TypeDescriptor const *descriptor) const {
        auto pool = getComponentPool(descriptor);
        if (pool != nullptr) {
            return pool->getInitialiser();
        }

        return [](Component &) {};
    }

    std::function<void(Component &)> ComponentManager::getDisposer(TypeDescriptor const *descriptor) const {
        auto pool = getComponentPool(descriptor);
        if (pool != nullptr) {
            return pool->getDisposer();
        }

        return [](Component &) {};
    }

    void ComponentManager::init() {
        auto const snapshot = componentPools;
        std::ranges::for_each(snapshot, [](auto const &pool) { pool.second->init(); });
    }

    void ComponentManager::update(std::uint64_t cycle) {
        auto const snapshot = componentPools;
        std::ranges::for_each(snapshot, [cycle](auto const &pool) { pool.second->update(cycle); });
    }

    void ComponentManager::dispose() {
        auto const snapshot = componentPools;
        std::ranges::for_each(snapshot, [](auto const &pool) { pool.second->dispose(); });
    }
}
