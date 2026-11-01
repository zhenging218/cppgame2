//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "memory/object_handle.hpp"

#include <unordered_map>
#include <functional>
#include <cstdint>

namespace cppengine {
    class Component;
    class ComponentPool;
    class TypeDescriptor;

    class ComponentManager {
    private:

        std::unordered_map<TypeDescriptor const *, ObjectHandle<ComponentPool>> componentPools;

    public:

        template <typename T, typename ... Args>
        ObjectHandle<T> createComponent(Args &&... args);

        ObjectHandle<ComponentPool> getComponentPool(TypeDescriptor const *descriptor);
        ObjectHandle<const ComponentPool> getComponentPool(TypeDescriptor const *descriptor) const;

        std::function<void(Component&)> getInitialiser(TypeDescriptor const *descriptor) const;
        std::function<void(Component&)> getDisposer(TypeDescriptor const *descriptor) const;

        void init();
        void update(std::uint64_t cycle);
        void dispose();
    };
}

#endif //COMPONENT_MANAGER_HPP
