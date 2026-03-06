#ifndef COMPONENT_ALLOCATOR_CONTEXT_IMPL_HPP
#define COMPONENT_ALLOCATOR_CONTEXT_IMPL_HPP

namespace cppengine {
    template<typename T, typename... Args>
    ObjectHandle<T> ObjectAllocatorContext::createHandle(Args &&... args) {
        auto const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
        auto allocator = allocators.find(descriptor);

        if (allocator == allocators.end()) {
            allocator = allocators.emplace(descriptor, ObjectHandle(new ComponentAllocatorImpl<T>())).first;
        }

        ObjectHandle<T> handle =
            static_handle_cast<ComponentAllocatorImpl<T>>(allocator->second)->createHandle(std::forward<Args>(args)...);

        return handle;
    }
}

#endif