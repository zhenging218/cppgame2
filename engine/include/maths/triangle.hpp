#pragma once

#include "maths/vector3.hpp"
#include "maths/math_helper.hpp"

struct Triangle {
    using vertex_type = Vector3;
    using value_type = typename std::remove_reference<decltype(*(& std::declval<vertex_type&>()[0]))>::type;
    static constexpr std::size_t vertex_count = 3;

    vertex_type vertices[3];

    constexpr inline Triangle(vertex_type const& v0, vertex_type const& v1, vertex_type const& v2) noexcept : vertices{ v0, v1, v2 } {}
    constexpr inline Triangle() : Triangle(vertex_type{}, vertex_type{}, vertex_type{}) {}

    constexpr operator value_type*() noexcept { return MathHelper::StructToArrayConverter<Triangle, value_type>::convert(*this); };
    constexpr operator const value_type* () const noexcept { return MathHelper::StructToArrayConverter<Triangle, value_type>::convert(*this); }

    vertex_type& operator[](int i);
    vertex_type const& operator[](int i) const;

    std::size_t constexpr inline getVertexCount() const noexcept { return vertex_count; }

    friend bool operator==(Triangle const& lhs, Triangle const& rhs);
};

std::ostream& operator<<(std::ostream& os, Triangle const& t);