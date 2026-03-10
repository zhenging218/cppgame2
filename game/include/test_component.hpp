#ifndef TEST_COMPONENT_HPP
#define TEST_COMPONENT_HPP
#include "ecs/component.hpp"

namespace cppgame {
    using namespace cppengine;
    class TestComponent : public Component {
    private:
        ObjectHandle<Transform> transform;
    public:
        void init();
        void update();
    };
}

DECL_TYPE_DESCRIPTOR(cppgame::TestComponent, cppengine::Component)


#endif