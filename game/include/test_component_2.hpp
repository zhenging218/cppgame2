#ifndef TEST_COMPONENT_2_HPP
#define TEST_COMPONENT_2_HPP

#include "ecs/component.hpp"

namespace cppgame {
    class TestComponent2 : public Component {
    private:
        ObjectHandle<Transform> transform;
    public:
        void init();
        void update();
    };
}

DECL_TYPE_DESCRIPTOR(cppgame::TestComponent2, cppengine::Component)

#endif