//
// Created by Admin on 7/11/2026.
//

#ifndef CPPGAME_DESERIALISER_IMPL_HPP
#define CPPGAME_DESERIALISER_IMPL_HPP

#include "introspection_traits.hpp"
#include "deserialiser.hpp"
#include "reflection/type_descriptor.hpp"

namespace cppengine {
    template<typename T>
    void Deserialiser::deserialise(T &dest) {
        if constexpr(NonTriviallyIntrospectableType<T> && !IterableSerialisableType<T> && !std::is_convertible_v<T, std::string_view>) {

        } else if constexpr (IterableSerialisableType<T> && !std::is_convertible_v<T, std::string_view>) {

        } else {

        }


    }
}

#endif //CPPGAME_DESERIALISER_IMPL_HPP
