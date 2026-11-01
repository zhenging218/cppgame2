//
// Created by Admin on 31/10/2026.
//

#ifndef COMPONENT_POOL_HPP
#define COMPONENT_POOL_HPP

#include <cstdint>
#include <functional>

#include "memory/object_allocator.hpp"
#include "ecs/ecs_concepts.hpp"

namespace cppengine {

    class ComponentPool {
    private:

    public:
        virtual void init() = 0;
        virtual void update(std::uint64_t cycle) = 0;
        virtual void dispose() = 0;

        [[nodiscard]] virtual std::function<void(Component &)> getInitialiser() const = 0;
        [[nodiscard]] virtual std::function<void(Component &)> getDisposer() const = 0;

        virtual ~ComponentPool() = 0;
    };

    template <typename T> requires ComponentType<T>
    class ComponentPoolImpl : public ComponentPool {
    private:

        ObjectAllocator<T> allocator;
    public:

        ComponentPoolImpl() = default;
        ComponentPoolImpl(ComponentPoolImpl const &) = delete;
        ComponentPoolImpl(ComponentPoolImpl &&) noexcept = delete;
        ComponentPoolImpl &operator=(ComponentPoolImpl const &) = delete;
        ComponentPoolImpl &operator=(ComponentPoolImpl &&) noexcept = delete;

        void init() override;
        void update(std::uint64_t cycle) override;
        void dispose() override;

        [[nodiscard]] std::function<void(Component &)> getInitialiser() const override;
        [[nodiscard]] std::function<void(Component &)> getDisposer() const override;

        template <typename ... Args>
        ObjectHandle<T> createComponent(Args &&... args);

        ~ComponentPoolImpl() override = default;
    };

}

#endif //COMPONENT_POOL_HPP
