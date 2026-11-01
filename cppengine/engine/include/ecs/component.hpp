//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_COMPONENT_HPP
#define CPPGAME_COMPONENT_HPP
#include "enum_component_state.hpp"
#include "ecs_concepts.hpp"

#include <cstdint>

namespace cppengine {
    class Scene;

    class Component {
    private:
        friend class Scene;

        template <typename T> requires ComponentType<T>
        friend class ComponentPoolImpl;

        std::uint64_t stamp = 0;
        ComponentState state = ComponentState::INITIALISING;

        void setStamp(std::uint64_t newStamp);
        void setState(ComponentState newState);
    public:

        [[nodiscard]] ComponentState getState() const;
        [[nodiscard]] std::uint64_t getStamp() const;
        virtual ~Component() = 0;
    };
}

#endif //CPPGAME_COMPONENT_HPP
