//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_LINEAR_TRAITS_HPP
#define CPPGAME_LINEAR_TRAITS_HPP

#include "maths/vector2.hpp"
#include "maths/vector3.hpp"
#include "maths/vector4.hpp"
#include "maths/quaternion.hpp"

#include "maths/matrix2x2.hpp"
#include "maths/matrix3x3.hpp"
#include "maths/matrix4x4.hpp"

#include "reflection_traits.hpp"

#define DECL_LINEAR_TYPE(TYPE_NAME) \
    template <> \
    struct TypeTraits<TYPE_NAME> { \
        using type = TYPE_NAME; \
        using super_type = TYPE_NAME; \
        static constexpr std::size_t size = sizeof(TYPE_NAME); \
        static constexpr StringLiteral name{ #TYPE_NAME };\
        static constexpr char const *getName() { return name.data(); } \
        static constexpr bool defined_trait_v = false; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = false; \
    }

namespace cppengine {
    DECL_LINEAR_TYPE(Vector2);
    DECL_LINEAR_TYPE(Vector3);
    DECL_LINEAR_TYPE(Vector4);
    DECL_LINEAR_TYPE(Quaternion);

    DECL_LINEAR_TYPE(Matrix2x2);
    DECL_LINEAR_TYPE(Matrix3x3);
    DECL_LINEAR_TYPE(Matrix4x4);
}

#undef DECL_LINEAR_TYPE

#endif //CPPGAME_LINEAR_TRAITS_HPP
