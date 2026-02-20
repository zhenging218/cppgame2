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

        Vector3 const *getVertices() const override;
        std::size_t getVertexCount() const override;
        std::size_t const *getIndices() const override;
        std::size_t getIndexCount() const override;

        Triangle const &getTriangle() const;
    };
}

DECL_POLY_TYPE(cppengine::TrianglePrimitive, cppengine::Renderable)

#endif