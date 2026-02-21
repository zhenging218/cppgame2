#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include <cstdint>
#include <variant>

#include "colour.hpp"
#include "texture.hpp"
#include "maths/matrix2x2.hpp"
#include "maths/matrix3x3.hpp"
#include "maths/matrix4x4.hpp"
#include "maths/vector2.hpp"
#include "maths/vector3.hpp"
#include "maths/vector4.hpp"

namespace cppengine {
    using Uniform = std::variant<
        std::int32_t,
        std::uint32_t,
        float,
        Colour,
        Vector2,
        Vector3,
        Vector4,
        Matrix2x2,
        Matrix3x3,
        Matrix4x4>;
}

#endif