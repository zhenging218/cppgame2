#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "ecs/component.hpp"

namespace cppengine {
    class DrawContext;

    class Renderable : public Component {
    private:

    protected:
        ObjectHandle<Transform> transform;

    public:
        void init() override;
    };
}

#endif