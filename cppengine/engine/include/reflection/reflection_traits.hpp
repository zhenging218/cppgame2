//
// Created by Admin on 7/11/2026.
//

#ifndef CPPGAME_REFLECTION_TRAITS_HPP
#define CPPGAME_REFLECTION_TRAITS_HPP

#include "string_literal.hpp"

namespace cppengine {
    template <typename ... Args>
    struct ArgumentList {};

    template <typename T>
    struct TypeTraits {
        using type = T;
        using super_type = T;
        static constexpr std::size_t size = sizeof(T);
        static constexpr StringLiteral name{ "?" };
        static constexpr char const *getName() { return name.data(); }
        static constexpr bool pod_type_v = false;
        static constexpr bool container_type_v = false;
        static constexpr bool defined_trait_v = false;
    };

    template <typename T>
    struct TypeTraits<const T> : TypeTraits<T> {
    };

    template <typename T>
    struct TypeMemberTraits {
        static constexpr bool members_defined_v = false;
        using members = ArgumentList<>;
    };

    template <typename T>
    struct TypeMemberTraits<const T> : TypeMemberTraits<T> {
    };

    template <typename T> requires TypeTraits<T>::defined_trait_v
    auto const &getTypeName() {
        return TypeTraits<T>::name;
    }

    template <typename T>
    constexpr auto joinTypeNames(T) = delete;

    template <typename T, typename ... Args>
    constexpr auto joinTypeNames(ArgumentList<T, Args...>) {
        return concatLiterals(TypeTraits<T>::name, concatLiterals(StringLiteral{","}, TypeTraits<Args>::name)...);
    }

    template <>
    constexpr auto joinTypeNames<ArgumentList<>>(ArgumentList<> list) {
        return StringLiteral{""};
    }
}

#endif //CPPGAME_REFLECTION_TRAITS_HPP
