#ifndef SCENE_SETUP_HPP
#define SCENE_SETUP_HPP
#include "memory/object_handle.hpp"

namespace cppengine {
    class Scene;

    class SceneSetup {
    public:
        virtual void setup(ObjectHandle<Scene> scene) = 0;
        virtual ~SceneSetup() = default;
    };
}

#endif