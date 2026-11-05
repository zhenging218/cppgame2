#ifndef TRIANGLE_PRIMITIVE_HPP
#define TRIANGLE_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/triangle.hpp"

namespace cppengine {
    class TrianglePrimitive : public Renderable {
    public:
        TrianglePrimitive();

        std::string_view getModelName() const override;

        Triangle const &getTriangle() const;
    };
}

DECL_TYPE_DESCRIPTOR(cppengine::TrianglePrimitive, cppengine::Renderable)


#endif