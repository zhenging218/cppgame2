//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_RENDERER_TRAITS_HPP
#define CPPGAME_RENDERER_TRAITS_HPP

#include "graphics/colour.hpp"

#include "string_literal.hpp"
#include "reflection_traits.hpp"

#define DECL_RENDER_TYPE(TYPE_NAME) \
    template <> \
    struct TypeTraits<TYPE_NAME> { \
        using type = TYPE_NAME; \
        using super_type = TYPE_NAME; \
        static constexpr std::size_t size = sizeof(TYPE_NAME); \
        static constexpr StringLiteral name{ #TYPE_NAME };\
        static constexpr char const *getName() { return name.data(); } \
        static constexpr bool defined_trait_v = true; \
        static constexpr bool pod_type_v = false; \
        static constexpr bool container_type_v = false; \
    }

namespace cppengine {

    DECL_RENDER_TYPE(Colour);
}

#undef DECL_RENDER_TYPE

#endif //CPPGAME_RENDERER_TRAITS_HPP
