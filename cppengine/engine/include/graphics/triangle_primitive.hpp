#ifndef TRIANGLE_PRIMITIVE_HPP
#define TRIANGLE_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/triangle.hpp"

namespace cppengine {
    class TrianglePrimitive : public Renderable {
    public:
        [[nodiscard]] std::string_view getModelName() const override;
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::TrianglePrimitive, cppengine::Renderable)


#endif