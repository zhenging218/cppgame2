#ifndef COMPONENT_ALLOCATOR_HPP
#define COMPONENT_ALLOCATOR_HPP

namespace cppengine {
  struct ComponentAllocator {
    virtual ~ComponentAllocator() = 0;
  };

  template <typename T>
  struct ComponentAllocatorImpl : ComponentAllocator {
    ObjectAllocator<T> allocator;

    template <typename ... Args>
    ObjectHandle<T> createHandle(Args &&...args);
  };
}

#endif