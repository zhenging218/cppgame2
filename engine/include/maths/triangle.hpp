#pragma once

#include "maths/vector3.hpp"
#include "maths/math_helper.hpp"

namespace cppengine {
    struct Triangle {
        using vertex_type = Vector3;
        using value_type = typename std::remove_reference<decltype(*(& std::declval<vertex_type&>()[0]))>::type;
        static constexpr std::size_t vertex_count = 3;
        static constexpr std::size_t index_count = 3;
        static constexpr std::size_t indices[vertex_count] = { 0, 1, 2 };

        vertex_type vertices[vertex_count];

        constexpr inline Triangle(vertex_type const& v0, vertex_type const& v1, vertex_type const& v2) noexcept : vertices{ v0, v1, v2 } {}
        constexpr inline Triangle() : Triangle(
            {0.0f, -0.577f, 0.0f},
            {-0.5f, 0.289f, 0.0f},
            {0.5f, 0.289f, 0.0f}) {}

        constexpr operator value_type*() noexcept { return MathHelper::StructToArrayConverter<Triangle, value_type>::convert(*this); };
        constexpr operator const value_type* () const noexcept { return MathHelper::StructToArrayConverter<Triangle, value_type>::convert(*this); }

        vertex_type& operator[](int i);
        vertex_type const& operator[](int i) const;

        std::size_t constexpr inline getVertexCount() const noexcept { return vertex_count; }
        constexpr inline std::size_t const * getIndices() const noexcept { return indices; }

    };

    bool operator==(Triangle const& lhs, Triangle const& rhs);
    std::ostream& operator<<(std::ostream& os, Triangle const& t);
}