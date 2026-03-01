#ifndef TEST_LEVEL_HPP
#define TEST_LEVEL_HPP
#include "ecs/scene_setup.hpp"

namespace cppgame {
    using namespace cppengine;
    
    class TestLevel : public SceneSetup {
    private:

    public:
        void setup(ObjectHandle<Scene> scene) override;
    };
}

#endif
