//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_POOL_HPP
#define COMPONENT_POOL_HPP

#include <cstdint>

#include "memory/object_allocator.hpp"
#include "ecs/ecs_concepts.hpp"

namespace cppengine {

    class ComponentPoolDelegate {
    private:
        void *delegate;
        void (*invoker)(void*, Component &);
    public:
        template <typename T> requires std::invocable<T, Component &>
        ComponentPoolDelegate(T &delegate_);

        void operator()(Component &component) const;
    };

    class ComponentPool {
    private:

    public:
        virtual void init(ComponentPoolDelegate delegate) = 0;
        virtual void update(ComponentPoolDelegate delegate) = 0;
        virtual void dispose(ComponentPoolDelegate delegate) = 0;

        virtual ~ComponentPool() = 0;
    };

    template <typename T> requires ComponentType<T>
    class ComponentPoolImpl : public ComponentPool {
    private:

        ObjectAllocator<T> allocator;
    public:

        ComponentPoolImpl(ComponentPoolImpl const &) = delete;
        ComponentPoolImpl(ComponentPoolImpl &&) noexcept = delete;
        ComponentPoolImpl &operator=(ComponentPoolImpl const &) = delete;
        ComponentPoolImpl &operator=(ComponentPoolImpl &&) noexcept = delete;

        virtual void init(ComponentPoolDelegate delegate) override;
        virtual void update(ComponentPoolDelegate delegate) override;
        virtual void dispose(ComponentPoolDelegate delegate) override;

        virtual ~ComponentPoolImpl() override = default;
    };

}

#endif //COMPONENT_POOL_HPP
