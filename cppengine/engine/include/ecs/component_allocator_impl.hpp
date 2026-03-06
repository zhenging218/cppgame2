#ifndef COMPONENT_ALLOCATOR_IMPL_HPP
#define COMPONENT_ALLOCATOR_IMPL_HPP

namespace cppengine {
    template<typename T>
    template<typename... Args>
    ObjectHandle<T> ComponentAllocatorImpl<T>::createHandle(Args &&... args) {
      return allocator.createHandle(std::forward<Args>(args)...);
    }

    inline ComponentAllocator::~ComponentAllocator() = default;
}

#endif