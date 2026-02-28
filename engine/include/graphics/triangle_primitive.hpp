#ifndef TRIANGLE_PRIMITIVE_HPP
#define TRIANGLE_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/triangle.hpp"

namespace cppengine {
    class TrianglePrimitive : public Renderable {
    private:
        ModelID id;
    public:
        TrianglePrimitive();

        ModelID getModelId() const override;

        Triangle const &getTriangle() const;
    };
}

DECL_POLY_TYPE(cppengine::TrianglePrimitive, cppengine::Renderable)

#endif