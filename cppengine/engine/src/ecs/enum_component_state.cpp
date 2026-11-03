//
// Created by Admin on 31/10/2026.
//

#include "ecs/enum_component_state.hpp"

namespace cppengine {
    ComponentState operator++(ComponentState &state, int) {
        auto oldState = state;
        ++state;
        return oldState;
    }

    ComponentState & operator++(ComponentState &state) {
        switch (state) {
            case ComponentState::INITIALISING:
                state = ComponentState::ACTIVE;
                break;
            case ComponentState::ACTIVE:
                state = ComponentState::DISPOSING;
                break;
            case ComponentState::DISPOSING:
                state = ComponentState::DISPOSED;
                break;
            case ComponentState::DISPOSED:
                break;
        }

        return state;
    }
}
