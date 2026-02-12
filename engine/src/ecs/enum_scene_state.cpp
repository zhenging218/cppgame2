#include "engine.hpp"

namespace cppengine {
    SceneState &operator++(SceneState &s) {
        switch (s) {
            case SceneState::INITIALISE:
                s = SceneState::SETUP;
                break;
            case SceneState::SETUP:
                s = SceneState::UPDATE;
                break;
            case SceneState::UPDATE:
                s = SceneState::TEARDOWN;
                break;
            case SceneState::TEARDOWN:
                s = SceneState::SETUP;
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