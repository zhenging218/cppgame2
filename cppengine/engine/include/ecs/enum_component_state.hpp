//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_ENUM_COMPONENT_STATE_HPP
#define CPPGAME_ENUM_COMPONENT_STATE_HPP

namespace cppengine {
    enum class ComponentState {
        INITIALISING,
        ACTIVE,
        DISPOSING,
        DISPOSED
    };

    ComponentState operator++(ComponentState &state, int);
    ComponentState &operator++(ComponentState &state);
}

#endif //CPPGAME_ENUM_COMPONENT_STATE_HPP
