#ifndef TRIANGLE_PRIMITIVE_HPP
#define TRIANGLE_PRIMITIVE_HPP
#include "renderable.hpp"
#include "maths/triangle.hpp"

namespace cppengine {
    class TrianglePrimitive : public Renderable {
    private:
        Triangle triangle;
    public:
        TrianglePrimitive() = default;
        explicit TrianglePrimitive(Triangle const &t);

        Triangle const &getTriangle() const;
    };
}

DECL_POLY_TYPE(cppengine::TrianglePrimitive, cppengine::Renderable)

#endif