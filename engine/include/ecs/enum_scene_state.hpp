#ifndef ENUM_SCENE_STATE_HPP
#define ENUM_SCENE_STATE_HPP

namespace cppengine {
    enum class SceneState {
        INITIALISE,
        LOAD,
        UPDATE,
        UNLOAD
    };

    SceneState &operator++(SceneState &s);
    SceneState operator++(SceneState &s, int);
}

#endif