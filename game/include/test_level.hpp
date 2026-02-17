#ifndef TEST_LEVEL_HPP
#define TEST_LEVEL_HPP
#include "ecs/scene_setup.hpp"

namespace cppgame {
    class TestLevel : public cppengine::SceneSetup {
    private:

    public:
        void setup(cppengine::ObjectHandle<cppengine::Scene> scene) override;
    };
}

#endif
