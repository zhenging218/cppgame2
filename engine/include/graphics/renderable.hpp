#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "ecs/component.hpp"

namespace cppengine {
    class DrawContext;

    class Renderable : public Component {
    private:

    protected:

    public:
        virtual ModelID getModelId() const = 0;

        ~Renderable() override = 0;
    };

    inline Renderable::~Renderable() = default;
}

#endif