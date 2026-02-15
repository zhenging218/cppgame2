#ifndef TRIANGLE_PRIMITIVE_HPP
#define TRIANGLE_PRIMITIVE_HPP
#include "primitive.hpp"
#include "maths/triangle.hpp"

namespace cppengine {
    class TrianglePrimitive : public Primitive {
    private:
        Triangle triangle;
    public:
        TrianglePrimitive() = default;

        vertex_array_type getVertices() const override;
        index_array_type getIndices() const override;

        std::size_t getValueCount() const override;
        std::size_t getIndexCount() const override;
        std::size_t getStride() const override;

        explicit TrianglePrimitive(Triangle const &t);
    };
}

#endif