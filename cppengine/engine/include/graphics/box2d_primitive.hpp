#ifndef BOX_2D_PRIMITIVE_HPP
#define BOX_2D_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/box_2d.hpp"

namespace cppengine {
    class Box2DPrimitive : public Renderable {
    public:
        [[nodiscard]] std::string_view getModelName() const override;
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::Box2DPrimitive, cppengine::Renderable)

#endif