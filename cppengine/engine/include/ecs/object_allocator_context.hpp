#ifndef OBJECT_ALLOCATOR_CONTEXT_HPP
#define OBJECT_ALLOCATOR_CONTEXT_HPP

#include "component_allocator.hpp"

namespace cppengine {

    class TypeDescriptor;

    class ObjectAllocatorContext {
    private:
        using allocator_map_type = std::unordered_map<TypeDescriptor const *, ObjectHandle<ComponentAllocator>>;

        allocator_map_type allocators;
    public:

        template <typename T, typename ... Args>
        ObjectHandle<T> createHandle(Args &&... args);

    };
}

#endif