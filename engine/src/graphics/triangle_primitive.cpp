#include "graphics/triangle_primitive.hpp"

#include "engine.hpp"

namespace {
    constexpr cppengine::TrianglePrimitive::index_value_type indices[] = { 0, 1, 2 };
    constexpr std::size_t stride = cppengine::Triangle::vertex_type::value_count;
    constexpr std::size_t value_count = cppengine::Triangle::vertex_count * stride;
}

namespace cppengine {
    TrianglePrimitive::TrianglePrimitive(Triangle const &t) : triangle(t) {

    }

    Primitive::vertex_array_type TrianglePrimitive::getVertices() const {
        return MathHelper::StructToArrayConverter<Vector3, vertex_value_type>::convert(triangle.vertices);
    }

    Primitive::index_array_type TrianglePrimitive::getIndices() const {
        return indices;
    }

    std::size_t TrianglePrimitive::getIndexCount() const {
        return Triangle::vertex_count;
    }

    std::size_t TrianglePrimitive::getValueCount() const {
        return value_count;
    }

    std::size_t TrianglePrimitive::getStride() const {
        return stride;
    }
}
