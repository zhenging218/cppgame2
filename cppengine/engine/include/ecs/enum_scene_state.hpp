#ifndef ENUM_SCENE_STATE_HPP
#define ENUM_SCENE_STATE_HPP

namespace cppengine {
    enum class SceneState {
        STARTUP,
        LOAD,
        INIT,
        UPDATE,
        TEARDOWN,
        UNLOAD
    };

    SceneState &operator++(SceneState &s);
    SceneState operator++(SceneState &s, int);
}

#endif