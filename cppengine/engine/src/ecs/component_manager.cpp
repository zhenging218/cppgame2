//
// Created by Admin on 31/10/2026.
//

#include "ecs/ecs.hpp"

namespace cppengine {
    ObjectHandle<ComponentPool> ComponentManager::getComponentPool(TypeDescriptor const *descriptor) {
        auto pool = componentPoolMap.find(descriptor);

        if (pool != componentPoolMap.end()) {
            return pool->second;
        }

        return nullptr;
    }

    ObjectHandle<const ComponentPool> ComponentManager::
    getComponentPool(TypeDescriptor const *descriptor) const {
        if (const auto pool = componentPoolMap.find(descriptor); pool != componentPoolMap.end()) {
            return const_handle_cast<const ComponentPool>(pool->second);
        }

        return nullptr;
    }

    ComponentManager::delegate_type ComponentManager::getInitialiser(TypeDescriptor const *descriptor) const {
        if (const auto pool = getComponentPool(descriptor); pool != nullptr) {
            return pool->getInitialiser();
        }

        return [](Component &) {};
    }

    ComponentManager::delegate_type ComponentManager::getDisposer(TypeDescriptor const *descriptor) const {
        auto pool = getComponentPool(descriptor);
        if (pool != nullptr) {
            return pool->getDisposer();
        }

        return [](Component &) {};
    }

    void ComponentManager::init() {
        for (std::size_t i = 0; i < componentPools.size(); ++i) {
            componentPools[i]->init();
        }
    }

    void ComponentManager::update(std::uint64_t cycle) {
        for (std::size_t i = 0; i < componentPools.size(); ++i) {
            componentPools[i]->update(cycle);
        }
    }

    void ComponentManager::dispose() {
        for (std::size_t i = 0; i < componentPools.size(); ++i) {
            componentPools[i]->dispose();
        }
    }
}
