#include "engine.hpp"

namespace cppengine {
    SceneState &operator++(SceneState &s) {
        switch (s) {
            case SceneState::INITIALISE:
                s = SceneState::LOAD;
                break;
            case SceneState::LOAD:
                s = SceneState::UPDATE;
                break;
            case SceneState::UPDATE:
                s = SceneState::UNLOAD;
                break;
            case SceneState::UNLOAD:
                s = SceneState::LOAD;
                break;
        }

        return s;
    }

    SceneState operator++(SceneState &s, int) {
        SceneState prev = s;
        ++s;
        return prev;
    }
}