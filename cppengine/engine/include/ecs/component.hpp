//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_COMPONENT_HPP
#define CPPGAME_COMPONENT_HPP
#include "enum_component_state.hpp"

namespace cppengine {
    class Scene;

    class Component {
    private:
        friend class Scene;

        void setState(ComponentState newState);
    public:

        virtual ~Component() = 0;
    };
}

#endif //CPPGAME_COMPONENT_HPP
