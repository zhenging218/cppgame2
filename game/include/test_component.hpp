#ifndef TEST_COMPONENT_HPP
#define TEST_COMPONENT_HPP
#include "ecs/component.hpp"

namespace cppgame {
    class TestComponent : public cppengine::Component {
    private:
        cppengine::ObjectHandle<cppengine::Transform> transform;
    public:
        void init();
        void update();
    };
}

DECL_POLY_TYPE(cppgame::TestComponent, cppengine::Component)

#endif