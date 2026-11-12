//
// Created by Admin on 7/11/2026.
//

#ifndef CPPGAME_REFLECTION_TRAITS_HPP
#define CPPGAME_REFLECTION_TRAITS_HPP

#include <typeinfo>

namespace cppengine {
    template <typename ... Args>
    struct ArgumentList {};

    template <typename T>
    struct TypeTraits {
        using type = T;
        using super_type = T;
        static constexpr std::size_t size = sizeof(T);
        static constexpr char const *getName() { return typeid(T).name(); }
        static constexpr bool pod_type_v = false;
        static constexpr bool defined_trait_v = false;
    };

    template <typename T>
    struct TypeMemberTraits {
        static constexpr bool members_defined_v = false;
        using members = ArgumentList<>;
    };
}

#endif //CPPGAME_REFLECTION_TRAITS_HPP
