#ifndef BOX_2D_HPP
#define BOX_2D_HPP

#include "maths/vector3.hpp"
#include "maths/math_helper.hpp"

namespace cppengine {
    class Vector3;

    struct Box2D {
        using vertex_type = Vector3;
        using value_type = typename std::remove_reference<decltype(*(& std::declval<vertex_type&>()[0]))>::type;
        static constexpr std::size_t vertex_count = 4;
        static constexpr std::size_t index_count = 6;
        static constexpr std::size_t indices[index_count] = { 0, 3, 1, 1, 3, 2 };

        vertex_type vertices[vertex_count];

        constexpr inline Box2D(vertex_type const &v0, vertex_type const &v1, vertex_type const &v2, vertex_type const &v3) noexcept
            : vertices{ v0, v1, v2, v3 } {}

        constexpr inline Box2D() : Box2D(
        { -.5f, -.5f, 0.f },
        { .5f, -.5f, 0.f },
        { .5f,  .5f, 0.f },
        { -.5f,  .5f, 0.f }) {}

        constexpr operator value_type*() noexcept { return MathHelper::StructToArrayConverter<Box2D, value_type>::convert(*this); };
        constexpr operator const value_type* () const noexcept { return MathHelper::StructToArrayConverter<Box2D, value_type>::convert(*this); }

        vertex_type& operator[](int i);
        vertex_type const& operator[](int i) const;

        std::size_t constexpr inline getVertexCount() const noexcept { return vertex_count; }
        constexpr inline std::size_t const * getIndices() const noexcept { return indices; }

    };

    bool operator==(Box2D const& lhs, Box2D const& rhs);
    std::ostream& operator<<(std::ostream& os, Box2D const& t);
}

#endif