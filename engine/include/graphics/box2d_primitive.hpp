#ifndef BOX_2D_PRIMITIVE_HPP
#define BOX_2D_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/box_2d.hpp"

namespace cppengine {
    class Box2DPrimitive : public Renderable {
    private:
        Box2D box2D;
    public:
        Box2DPrimitive() = default;
        explicit Box2DPrimitive(Box2D const &t);

        Box2D const &getBox2D() const;
    };
}

DECL_POLY_TYPE(cppengine::Box2DPrimitive, cppengine::Renderable)

#endif