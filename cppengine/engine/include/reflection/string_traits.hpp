//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_STRING_TRAITS_HPP
#define CPPGAME_STRING_TRAITS_HPP

#include "string_literal.hpp"
#include "reflection_traits.hpp"

namespace cppengine {
    template <>
    struct TypeTraits<std::string> {
        using type = std::string;
        using super_type = type;

        static constexpr std::size_t size = sizeof(type);
        static constexpr StringLiteral name{"std::string"};
        static constexpr  char const *getName() { return name.data(); }
        static constexpr bool defined_trait_v  = true;
        static constexpr bool pod_type_v = false;
        static constexpr bool container_type_v = false;
    };
}

#endif //CPPGAME_STRING_TRAITS_HPP
