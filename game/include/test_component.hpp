#ifndef TEST_COMPONENT_HPP
#define TEST_COMPONENT_HPP
#include "ecs/component.hpp"

namespace cppgame {
    class TestComponent : public cppengine::Component {
    private:
        cppengine::ObjectHandle<cppengine::Transform> transform;
    public:

        void init() override;
        void update() override;
        void teardown() override;
    };
}

#endif