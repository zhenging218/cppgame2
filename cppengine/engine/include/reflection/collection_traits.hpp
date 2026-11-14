//
// Created by Admin on 14/11/2026.
//

#ifndef CPPGAME_COLLECTION_TRAITS_HPP
#define CPPGAME_COLLECTION_TRAITS_HPP

#include "string_literal.hpp"
#include "reflection_traits.hpp"

#include <tuple>
#include <variant>

namespace cppengine {
    template <typename T, typename U>
    struct TypeTraits<std::pair<T, U>> {
        using type = std::pair<T, U>;
        using super_type = type;

        static constexpr std::size_t size = sizeof(type);
        static constexpr StringLiteral name = concatLiterals(StringLiteral{"std::pair"}, StringLiteral{"<"}, joinTypeNames(ArgumentList<T, U>{}), StringLiteral{">"});
        static constexpr  char const *getName() { return name.data(); }
        static constexpr bool defined_trait_v  = true;
        static constexpr bool pod_type_v = false;
        static constexpr bool container_type_v = false;
    };

    template <typename ... T>
    struct TypeTraits<std::tuple<T...>> {
        using type = std::tuple<T...>;
        using super_type = type;

        static constexpr std::size_t size = sizeof(type);
        static constexpr StringLiteral name = concatLiterals(StringLiteral{"std::tuple"}, StringLiteral{"<"}, joinTypeNames(ArgumentList<T...>{}), StringLiteral{">"});
        static constexpr  char const *getName() { return name.data(); }
        static constexpr bool defined_trait_v  = true;
        static constexpr bool pod_type_v = false;
        static constexpr bool container_type_v = false;
    };

    template <typename ... T>
    struct TypeTraits<std::variant<T...>> {
        using type = std::variant<T...>;
        using super_type = type;

        static constexpr std::size_t size = sizeof(type);
        static constexpr StringLiteral name = concatLiterals(StringLiteral{"std::variant"}, StringLiteral{"<"}, joinTypeNames(ArgumentList<T...>{}), StringLiteral{">"});
        static constexpr  char const *getName() { return name.data(); }
        static constexpr bool defined_trait_v  = true;
        static constexpr bool pod_type_v = false;
        static constexpr bool container_type_v = false;
    };
}

#endif //CPPGAME_COLLECTION_TRAITS_HPP
