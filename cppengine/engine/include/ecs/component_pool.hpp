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
        using delegate_type = void (*)(Component &);

        virtual void init() = 0;
        virtual void update(std::uint64_t cycle) = 0;
        virtual void dispose() = 0;

        [[nodiscard]] virtual delegate_type getInitialiser() const = 0;
        [[nodiscard]] virtual delegate_type getDisposer() const = 0;

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
        void update([[maybe_unused]] std::uint64_t cycle) override;
        void dispose() override;

        [[nodiscard]] delegate_type getInitialiser() const override;
        [[nodiscard]] delegate_type getDisposer() const override;

        template <typename ... Args>
        ObjectHandle<T> createComponent(Args &&... args);

        ~ComponentPoolImpl() override = default;
    };

}

#endif //COMPONENT_POOL_HPP
