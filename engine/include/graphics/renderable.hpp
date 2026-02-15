#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "ecs/component.hpp"

namespace cppengine {
    class DrawContext;

    class Renderable : public Component {
    private:

    public:
        // takes in a DrawContext, which represent the current draw batch
        // DrawContext will expose interface to draw primitives or complex model meshes.
        virtual void render(DrawContext &context) const = 0;
    };
}

#endif