#include "engine.hpp"

namespace cppengine {
    SceneState &operator++(SceneState &s) {
        switch (s) {
            case SceneState::STARTUP:
                s = SceneState::LOAD;
                break;
            case SceneState::LOAD:
                s = SceneState::INIT;
                break;
            case SceneState::INIT:
                s = SceneState::UPDATE;
                break;
            case SceneState::UPDATE:
                s = SceneState::TEARDOWN;
                break;
            case SceneState::TEARDOWN:
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