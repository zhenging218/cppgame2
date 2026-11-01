//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "memory/object_handle.hpp"

#include <vector>
#include <unordered_map>
#include <cstdint>

namespace cppengine {
    class Component;
    class ComponentPool;
    class TypeDescriptor;

    class ComponentManager {
    private:

        std::vector<ObjectHandle<ComponentPool>> componentPools;
        std::unordered_map<TypeDescriptor const *, ObjectHandle<ComponentPool>> componentPoolMap;

    public:
        using delegate_type = void(*)(Component &);

        template <typename T, typename ... Args>
        ObjectHandle<T> createComponent(Args &&... args);

        ObjectHandle<ComponentPool> getComponentPool(TypeDescriptor const *descriptor);
        ObjectHandle<const ComponentPool> getComponentPool(TypeDescriptor const *descriptor) const;

        delegate_type getInitialiser(TypeDescriptor const *descriptor) const;
        delegate_type getDisposer(TypeDescriptor const *descriptor) const;

        void init();
        void update(std::uint64_t cycle);
        void dispose();
    };
}

#endif //COMPONENT_MANAGER_HPP
